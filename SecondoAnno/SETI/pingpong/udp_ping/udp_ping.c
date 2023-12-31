/*
 * udp_ping.c: esempio di implementazione del processo "ping" con
 *             socket di tipo DGRAM.
 *
 * versione 9.0
 *
 * Programma sviluppato a supporto del laboratorio di
 * Sistemi di Elaborazione e Trasmissione del corso di laurea
 * in Informatica classe L-31 presso l'Universita` degli Studi di
 * Genova, anno accademico 2022/2023.
 *
 * Copyright (C) 2013-2014 by Giovanni Chiola <chiolag@acm.org>
 * Copyright (C) 2015-2016 by Giovanni Lagorio <giovanni.lagorio@unige.it>
 * Copyright (C) 2017-2022 by Giovanni Chiola <chiolag@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

///Per compilare (dalla cartella superiore):
///	 gcc -Wall tcp_ping/udp_ping.c pingpong_lib/statistics.c pingpong_lib/fail.c
#include "../pingpong_lib/pingpong.h"

/*
* This function sends and waits for a reply on a socket.
* char message[]: message to send
* size_t msg_size: message length
*/
double do_ping(size_t msg_size, int msg_no, char message[msg_size], int ping_socket, double timeout)
{
	//contatore pacchetti persi
	int lost_count = 0;
	
	//numero errore in ricezione
	int recv_errno;

	//buffer di risposta
	char answer_buffer[msg_size];

	//dimensione byte ricevuti e inviati 
	ssize_t recv_bytes = -1, sent_bytes;
	struct timespec send_time, recv_time;
	
	//RTT espresso in millisecondi
	double roundtrip_time_ms;

	//
	int re_try = 0;


    /*** write msg_no at the beginning of the message buffer ***/

	//dal man: fprintf() and vfprintf() write output to the given output stream.
	//
	//Sostanzialmente concatena il secondo parametro dietro al primo.
	sprintf(message, "%d\n", msg_no);


	do {
		debug(" ... sending message %d\n", msg_no);

		/*** Store the current time in send_time ***/

		//dal man: The functions clock_gettime() ... retrieve the time of the specified clock clockid
		//Nota: CLOCK_TYPE è definito nel file pingpong.h
		clock_gettime(CLOCK_TYPE, &send_time);


		/*** Send the message through the socket (non blocking mode) ***/

		//invia i dati e in caso di errore termina l'esecuzione
		sent_bytes = send(ping_socket, message, msg_size, 0);
		if(sent_bytes != msg_size)
			fail_errno("Errore nell'invio dei dati");
		

		/*** Receive answer through the socket (non blocking mode, with timeout) ***/
	
		//PREMESSA: Dato che il timeout è espresso in double in millisecondi, moltiplicalo per 100 per avere i microsecondi.
		//es: timeout = UDP_TIMEOUT = 3000.0 --> timeout*100 = 3000000 microsecondi.
		//Questa conversione è necessaria in quanto la funzione usleep ha come parametro un int che rappresenta
		//i microsecondi.
		//
		//Grazie a questo ciclo, per [timeout/100] secondi proviamo a leggere la risposta del server, dopodiche
		//esce dal ciclo.
		//La variabile costante RIDUZIONE serve per ridurre i microsecondi rimasti progressivamente, in modo tale
		//da "far avanzare" il cronometro dei [timeout/100] secondi.
		//Più il numero è alto, piu la ricezione sarà lenta ma con migliori prestazioni.
		int millisecLeft = (int)timeout*100;
		const int RIDUZIONE = 50; //ogni RIDUZIONE millisecondi, riprova

		while(recv_bytes < 0 && millisecLeft > 0) {
			recv_bytes = recv(ping_socket, answer_buffer, sizeof(answer_buffer), 0);
			usleep(RIDUZIONE); //aspetta RIDUZIONE millisecondi
			millisecLeft -= RIDUZIONE; //decrementa il timer

			//ricomincia il ciclo fino a quando o non hai una risposta o non è scaduto il tempo.
		}
		

		/*** Store the current time in recv_time ***/
		clock_gettime(CLOCK_TYPE, &recv_time);
		

		roundtrip_time_ms = timespec_delta2milliseconds(&recv_time, &send_time);

		while ( recv_bytes < 0 && (recv_errno == EAGAIN || recv_errno == EWOULDBLOCK) && roundtrip_time_ms < timeout ) {
			recv_bytes = recv(ping_socket, answer_buffer, sizeof(answer_buffer), 0);
			recv_errno = errno;

			if ( recv_bytes < 0 && errno != EAGAIN && errno != EWOULDBLOCK )
				fail_errno("UDP ping could not recv from UDP socket");
					
			if (clock_gettime(CLOCK_TYPE, &recv_time))
				fail_errno("Cannot get receive-time");

			roundtrip_time_ms = timespec_delta2milliseconds(&recv_time, &send_time);
			sscanf(answer_buffer,"%ld %ld, %ld %ld\n", &(recv_time.tv_sec), &(recv_time.tv_nsec), &(send_time.tv_sec), &(send_time.tv_nsec));
			roundtrip_time_ms -= timespec_delta2milliseconds(&send_time, &recv_time);
		}
		
		if (recv_bytes < sent_bytes) {	/*time-out elapsed: packet was lost */
			lost_count++;
			if (recv_bytes < 0)
				recv_bytes = 0;
			printf("\n ... received %zd bytes instead of %zd (lost count = %d); re-trying ...\n", recv_bytes, sent_bytes, lost_count);
			if (++re_try > MAXUDPRESEND) {
				printf(" ... giving-up!\n");
				fail("too many lost datagrams");
			}
			printf(" ... re-trying ...\n");
		}
	} while (sent_bytes != recv_bytes);

	return roundtrip_time_ms;
}


int prepare_udp_socket(char *pong_addr, char *pong_port)
{
	struct addrinfo gai_hints, *pong_addrinfo = NULL;
	int ping_socket;
	int gai_rv; //GetAddressInfo_ReturnValue

    /*** Specify the UDP sockets' options ***/
	memset(&gai_hints, 0, sizeof gai_hints);

	//dal man di getaddrinfo() (https://man7.org/linux/man-pages/man3/getaddrinfo.3.html):
	gai_hints.ai_family = AF_INET;
	gai_hints.ai_socktype = SOCK_DGRAM;
	gai_hints.ai_protocol = 0;
	gai_hints.ai_flags = 0;

	if ((ping_socket = socket(gai_hints.ai_family, gai_hints.ai_socktype, gai_hints.ai_protocol)) == -1)
		fail_errno("UDP Ping could not get socket");

    /*** change ping_socket behavior to NONBLOCKing using fcntl() ***/

	//cambia il socket in non bloccante:
	int result = fcntl(ping_socket, F_SETFL, O_NONBLOCK);
	if(result)
		fail_errno("Errore nel fcntl set");


    /*** call getaddrinfo() in order to get Pong Server address in binary form ***/
	gai_rv = getaddrinfo(pong_addr, pong_port, &gai_hints, &pong_addrinfo);
	
	//getaddrinfo ritorna 0 se tutto è andato bene, altrimenti un codice di errore;
	//controllo:
	if(gai_rv)
		fail_errno("Errore nel getaddrinfo");


#ifdef DEBUG
	char ipv4str[INET_ADDRSTRLEN];
	const char * const cp = inet_ntop(AF_INET, &(((struct sockaddr_in *)(pong_addrinfo-> ai_addr))->sin_addr), ipv4str, INET_ADDRSTRLEN);
	if (cp == NULL)
		printf(" ... inet_ntop() error!\n");
	else
		printf(" ... about to connect socket %d to IP address %s, port %hu\n",
				ping_socket, cp, ntohs(((struct sockaddr_in *)(pong_addrinfo->ai_addr))->sin_port));
#endif

    /*** connect the ping_socket UDP socket with the server ***/
	int connectValue = connect(ping_socket, pong_addrinfo->ai_addr, pong_addrinfo->ai_addrlen);	
	if(connectValue)
		fail_errno("Errore nel connect");

	freeaddrinfo(pong_addrinfo);
	return ping_socket;
}

int main(int argc, char *argv[])
{
	struct addrinfo gai_hints, *server_addrinfo; //getaddressinfo_hinst
	int ping_socket; 

	//socket del udp ottenuto tramite tcp.
	int ask_socket;

	//message size e numero ripetizioni
	int msg_size, norep;

	//GetAddressInfo_ReturnValue
	int gai_rv; 

	char ipstr[INET_ADDRSTRLEN];
	struct sockaddr_in *ipv4;
	char request[40], answer[10];
	ssize_t nr;

	//porta server tcp
	int pong_port;

	if (argc < 4)
		fail("Incorrect parameters provided. Use: udp_ping PONG_ADDR PONG_PORT MESSAGE_SIZE [NO_REPEAT]\n");
	for (nr = 4, norep = REPEATS; nr < argc; nr++)
		if (*argv[nr] >= '1' && *argv[nr] <= '9')
			sscanf(argv[nr], "%d", &norep);
	if (norep < MINREPEATS)
		norep = MINREPEATS;
	else if (norep > MAXREPEATS)
		norep = MAXREPEATS;
	if (sscanf(argv[3], "%d", &msg_size) != 1 || msg_size < MINSIZE || msg_size > MAXUDPSIZE)
		fail("Wrong message size");

    /*** Specify TCP socket options ***/
	memset(&gai_hints, 0, sizeof gai_hints);

	//dal man di getaddrinfo() (https://man7.org/linux/man-pages/man3/getaddrinfo.3.html):
	gai_hints.ai_family = AF_INET;
	gai_hints.ai_socktype = SOCK_STREAM;
	gai_hints.ai_protocol = 0;
	gai_hints.ai_flags = 0;


    /*** call getaddrinfo() in order to get Pong Server address in binary form ***/
	gai_rv = getaddrinfo(argv[1], argv[2], &gai_hints, &server_addrinfo);
	if(gai_rv != 0)
		fail_errno("Errore nel getaddrinfo");


    /*** Print address of the Pong server before trying to connect ***/
	ipv4 = (struct sockaddr_in *)server_addrinfo->ai_addr;
	printf("UDP Ping trying to connect to server %s (%s) on TCP port %s\n", argv[1], inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, INET_ADDRSTRLEN), argv[2]);


    /*** create a new TCP socket and connect it with the server ***/
	ask_socket = socket(AF_INET, SOCK_STREAM, 0);

	//connettiti al server
	int connectValue = connect(ask_socket, server_addrinfo->ai_addr, server_addrinfo->ai_addrlen);	
	if(connectValue != 0)
		fail_errno("Errore nel connect");


	freeaddrinfo(server_addrinfo);
	printf(" ... connected to Pong server: asking for %d repetitions of %d _bytes UDP messages\n", norep, msg_size);
	sprintf(request, "UDP %d %d\n", msg_size, norep);

    /*** Write the request on the TCP socket ***/
	int writeRes = write(ask_socket, request, strlen(request));
	if(writeRes > msg_size)
		fail_errno("Errore nella write");


	nr = read(ask_socket, answer, sizeof(answer));
	if (nr < 0)
		fail_errno("UDP Ping could not receive answer from Pong server");
	if (nr==sizeof(answer))
		--nr;
	answer[nr] = 0;

    /*** Check if the answer is OK, and fail if it is not ***/
	//strcmp compara due stringhe e ritorna 1 se sono uguali, 0 se diverse
	if(!strcmp(answer, "OK"))
		fail_errno("Errore nella risposta dal server");


    /*** else ***/
	sscanf(answer + 3, "%d\n", &pong_port);
	printf(" ... Pong server agreed to ping-pong using port %d :-)\n", pong_port);
	sprintf(answer, "%d", pong_port);
	shutdown(ask_socket, SHUT_RDWR);
	close(ask_socket);

	ping_socket = prepare_udp_socket(argv[1], answer);

	char message[msg_size];
	memset(&message, 0, (size_t)msg_size);
	double ping_times[norep];
	struct timespec zero, resolution;
	int repeat;
	for (repeat = 0; repeat < norep; repeat++) {
		ping_times[repeat] = do_ping((size_t)msg_size, repeat + 1, message, ping_socket, UDP_TIMEOUT);
		printf("Round trip time was %6.3lf milliseconds in repetition %d\n", ping_times[repeat], repeat + 1);
	}
	memset((void *)(&zero), 0, sizeof(struct timespec));
	if (clock_getres(CLOCK_TYPE, &resolution) != 0)
		fail_errno("UDP Ping could not get timer resolution");
	print_statistics(stdout, "UDP Ping: ", norep, ping_times, msg_size, timespec_delta2milliseconds(&resolution, &zero));


	close(ping_socket);
	exit(EXIT_SUCCESS);
}
