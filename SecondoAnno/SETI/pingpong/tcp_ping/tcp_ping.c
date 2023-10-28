/*
 * tcp_ping.c: esempio di implementazione del processo "ping" con
 *             socket di tipo STREAM.
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
///	 gcc -Wall tcp_ping/tcp_ping.c pingpong_lib/statistics.c pingpong_lib/fail.c
#include "../pingpong_lib/pingpong.h"

/*
 * This function sends and wait for a reply on a socket.
 * int msg_size: message length
 * int msg_no: message sequence number (written into the message)
 * char message[msg_size]: buffer to send
 * int tcp_socket: socket file descriptor
 */
double do_ping(size_t msg_size, int msg_no, char message[msg_size], int tcp_socket)
{
	char rec_buffer[msg_size]; //buffer di ricezione dei dati
	ssize_t recv_bytes, sent_bytes; //byte ricevuti e mandati
	size_t offset;
	struct timespec send_time, recv_time;
	double RTT_ms; //Round Trip Time (in MilliSec)

    /*** write msg_no at the beginning of the message buffer ***/
	
	//dal man: fprintf() and vfprintf() write output to the given output stream.
	//
	//Sostanzialmente concatena il secondo parametro dietro al primo.
	sprintf(message, "%d\n", msg_no);

    /*** Store the current time in send_time ***/
	
	//dal man: The functions clock_gettime() ... retrieve the time of the specified clock clockid
	//Nota: CLOCK_TYPE è definito nel file pingpong.h
	clock_gettime(CLOCK_TYPE, &send_time);

    /*** Send the message through the socket (blocking)  ***/
	//invia i dati e in caso di errore termina l'esecuzione
	sent_bytes = send(tcp_socket, message, msg_size, 0);
	if(sent_bytes != msg_size)
		fail_errno("Errore nell'invio dei dati");

    /*** Receive answer through the socket (blocking) ***/
	for (offset = 0; (offset + (recv_bytes = recv(tcp_socket, rec_buffer + offset, sent_bytes - offset, MSG_WAITALL))) < msg_size; offset += recv_bytes) {
		debug(" ... received %zd bytes back\n", recv_bytes);
		if (recv_bytes < 0)
			fail_errno("Error receiving data");
	}

    /*** Store the current time in recv_time ***/
	clock_gettime(CLOCK_TYPE, &recv_time);

	printf("tcp_ping received %zd bytes back\n", recv_bytes);

	RTT_ms = timespec_delta2milliseconds(&recv_time, &send_time);
        sscanf(rec_buffer,"%ld %ld, %ld %ld\n", &(recv_time.tv_sec), &(recv_time.tv_nsec),
                                                &(send_time.tv_sec), &(send_time.tv_nsec));
	RTT_ms -= timespec_delta2milliseconds(&send_time, &recv_time);
	return RTT_ms;
}

int main(int argc, char **argv)
{
	struct addrinfo gai_hints, *server_addrinfo;
	int msgsz, norep; //MessageSize and Number(of)Repetition
	int gai_rv; //GetAddressInfo_ReturnValue
	char ipstr[INET_ADDRSTRLEN];
	struct sockaddr_in *ipv4;
	int tcp_socket;
	char request[MAX_REQ], answer[MAX_ANSW];
	ssize_t nr;

	if (argc < 4)
		fail("Incorrect parameters provided. Use: tcp_ping PONG_ADDR PONG_PORT SIZE [NO_REP]\n");
	for (nr = 4, norep = REPEATS; nr < argc; nr++)
		if (*argv[nr] >= '1' && *argv[nr] <= '9')
			sscanf(argv[nr], "%d", &norep);
	if (norep < MINREPEATS)
		norep = MINREPEATS;
	else if (norep > MAXREPEATS)
		norep = MAXREPEATS;

    /*** Initialize hints in order to specify socket options ***/
	memset(&gai_hints, 0, sizeof gai_hints);

	//dal man di getaddrinfo() (https://man7.org/linux/man-pages/man3/getaddrinfo.3.html):
	gai_hints.ai_family = AF_INET;
	gai_hints.ai_socktype = SOCK_STREAM;
	gai_hints.ai_protocol = 0;
	gai_hints.ai_flags = 0;

    /*** call getaddrinfo() in order to get Pong Server address in binary form ***/
	gai_rv = getaddrinfo(argv[1], argv[2], &gai_hints, &server_addrinfo);
	
	//getaddrinfo ritorna 0 se tutto è andato bene, altrimenti un codice di errore;
	//controllo:
	if(gai_rv != 0)
		fail_errno("Errore nel getaddrinfo");

    /*** Print address of the Pong server before trying to connect ***/
	ipv4 = (struct sockaddr_in *)server_addrinfo->ai_addr;
	printf("TCP Ping trying to connect to server %s (%s) on port %s\n", argv[1], inet_ntop(AF_INET, &ipv4->sin_addr, ipstr, INET_ADDRSTRLEN), argv[2]);

    /*** create a new TCP socket and connect it with the server ***/
	tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

	//connettiti al server
	int connectValue = connect(tcp_socket, server_addrinfo->ai_addr, server_addrinfo->ai_addrlen);	
	if(connectValue != 0)
		fail_errno("Errore nel connect");


	freeaddrinfo(server_addrinfo);
	if (sscanf(argv[3], "%d", &msgsz) != 1)
		fail("Incorrect format of size parameter");
	if (msgsz < MINSIZE)
		msgsz = MINSIZE;
	else if (msgsz > MAXTCPSIZE)
		msgsz = MAXTCPSIZE;
	printf("\n... connected to Pong server: asking for %d repetitions of %d bytes TCP messages\n", norep, msgsz);
	sprintf(request, "TCP %d %d\n", msgsz, norep);

    /*** Write the request on socket ***/
	int writeRes = write(tcp_socket, request, strlen(request));
	if(writeRes > msgsz)
		fail_errno("Errore nella write");


	ssize_t readSize = read(tcp_socket, answer, sizeof(answer));
	if (readSize < 0)
		fail_errno("TCP Ping could not receive answer from Pong server");
		
    /*** Check if the answer is OK, and fail if it is not ***/
	//strcmp compara due stringhe e ritorna 1 se sono uguali, 0 se diverse
	if(!strcmp(answer, "OK"))
		fail_errno("Errore nella risposta dal server");

    /*** else ***/
	printf(" ... Pong server agreed :-)\n");

	double ping_times[norep];
	struct timespec zero, resolution;
	char message[msgsz];
	int rep;
	memset(message, 0, (size_t)msgsz);
	for(rep = 1; rep <= norep; ++rep) {
		double current_time = do_ping((size_t)msgsz, rep, message, tcp_socket);
		ping_times[rep - 1] = current_time;
		printf("Round trip time was %lg milliseconds in repetition %d\n", current_time, rep);
	}

	memset((void *)(&zero), 0, sizeof(struct timespec));
	if (clock_getres(CLOCK_TYPE, &resolution))
		fail_errno("TCP Ping could not get timer resolution");
	
	print_statistics(stdout, "TCP Ping: ", norep, ping_times, msgsz, timespec_delta2milliseconds(&resolution, &zero));

	shutdown(tcp_socket, SHUT_RDWR);
	close(tcp_socket);
	exit(EXIT_SUCCESS);
}

