/*
 * Micro-bash v2.2
 *
 * Programma sviluppato a supporto del laboratorio di Sistemi di
 * Elaborazione e Trasmissione dell'Informazione del corso di laurea
 * in Informatica presso l'Università degli Studi di Genova, a.a. 2022/2023.
 *
 * Copyright (C) 2020-2022 by Giovanni Lagorio <giovanni.lagorio@unige.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdint.h>

//stampa il messaggio di errore ed esci
void fatal(const char * const msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

//stampa il messaggio di errore con ERRNO ed esci
void fatal_errno(const char * const msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

void* my_malloc(size_t size)
{
	void *rv = malloc(size);
	if (!rv)
		fatal_errno("my_malloc");
	return rv;
}

void* my_realloc(void *ptr, size_t size)
{
	void *rv = realloc(ptr, size);
	if (!rv)
		fatal_errno("my_realloc");
	return rv;
}

char* my_strdup(char *ptr)
{
	char *rv = strdup(ptr);
	if (!rv)
		fatal_errno("my_strdup");
	return rv;
}

#define malloc I_really_should_not_be_using_a_bare_malloc
#define realloc I_really_should_not_be_using_a_bare_realloc
#define strdup I_really_should_not_be_using_a_bare_strdup

static const int NO_REDIR = -1;

typedef enum { CHECK_OK = 0, CHECK_FAILED = -1 } check_t;

static const char *const CD = "cd";

typedef struct {
	// numero argomenti
	int n_args;

	// in an execv*-compatible format; i.e., args[n_args]=0
	char **args; 
	
	// 0 if no output-redirection is present
	char* out_pathname; 
	
	// 0 if no input-redirection is present
	char* in_pathname; 
} command_t;

typedef struct {
	//Numero comandi
	int n_commands;

	//Lista di puntatori di comandi
	command_t **commands;
} line_t;

void free_command(command_t* const c)
{
	/* sanity-check: if c is not null, then it is either empty (in case of parsing error)
		or its args are properly NULL-terminated */
	assert(c==0 || c->n_args==0 || (c->n_args > 0 && c->args[c->n_args] == 0)); 
	/*** TO BE DONE START ***/
	
	for(int i = 0; i<c->n_args; ++i)
		free(c->args[i]);
		
	free(c->args);
	free(c->in_pathname);
	free(c->out_pathname);
	free(c);

	/*** TO BE DONE END ***/
}

void free_line(line_t* const l)
{
	assert(l==0 || l->n_commands>=0); /* sanity-check */
	/*** TO BE DONE START ***/

	for(int i = 0; i<l->n_commands; ++i)
		free_command(l->commands[i]);

	free(l->commands);
	free(l);
	/*** TO BE DONE END ***/
}

#ifdef DEBUG
void print_command(const command_t * const c)
{
	if (!c) {
		printf("Command == NULL\n");
		return;
	}
	printf("[ ");
	for(int a=0; a<c->n_args; ++a)
		printf("%s ", c->args[a]);
	assert(c->args[c->n_args] == 0);
	printf("] ");
	printf("in: %s out: %s\n", c->in_pathname, c->out_pathname);
}

void print_line(const line_t * const l)
{
	if (!l) {
		printf("Line == NULL\n");
		return;
	}
	printf("Line has %d command(s):\n", l->n_commands);
	for(int a=0; a<l->n_commands; ++a)
		print_command(l->commands[a]);
}
#endif

command_t* parse_cmd(char* const cmdstr)
{
	static const char *const BLANKS = " \t";
	command_t* const result = my_malloc(sizeof(*result));
	memset(result, 0, sizeof(*result));
	char *saveptr, *tmp;
	tmp = strtok_r(cmdstr, BLANKS, &saveptr); //string token read
	while (tmp) {
		result->args = my_realloc(result->args, (result->n_args + 2)*sizeof(char *));
		if (*tmp=='<') {
			if (result->in_pathname) {
				fprintf(stderr, "Parsing error: cannot have more than one input redirection\n");
				goto fail;
			}
			if (!tmp[1]) {
				fprintf(stderr, "Parsing error: no path specified for input redirection\n");
				goto fail;
			}
			result->in_pathname = my_strdup(tmp+1);
		} else if (*tmp == '>') {
			if (result->out_pathname) {
				fprintf(stderr, "Parsing error: cannot have more than one output redirection\n");
				goto fail;
			}
			if (!tmp[1]) {
				fprintf(stderr, "Parsing error: no path specified for output redirection\n");
				goto fail;
			}
			result->out_pathname = my_strdup(tmp+1);
		} else {
			if (*tmp=='$') {
				/* Make tmp point to the value of the corresponding environment variable, 
					if any, or the empty string otherwise */
				/*** TO BE DONE START ***/

				//utilizza come argomento &tmp[1] per saltare il primo carattere 
				//di tmp (che è "$" e fa fallire la getenv)
				tmp = getenv(&tmp[1]);
				if(tmp == NULL)
					//Variabile d'ambiente non trovata
					//espansione con stringa vuota ("")
					tmp = "";
				
				/*** TO BE DONE END ***/
			}
			result->args[result->n_args++] = my_strdup(tmp);
			result->args[result->n_args] = 0;
		}
		tmp = strtok_r(0, BLANKS, &saveptr);
	}
	if (result->n_args)
		return result;
	fprintf(stderr, "Parsing error: empty command\n");
fail:
	free_command(result);
	return 0;
}

line_t* parse_line(char * const line)
{
	static const char * const PIPE = "|";
	char *cmd, *saveptr;
	cmd = strtok_r(line, PIPE, &saveptr); //string token read
	if (!cmd)
		return 0;
	line_t *result = my_malloc(sizeof(*result));
	memset(result, 0, sizeof(*result));
	while (cmd) {
		command_t * const c = parse_cmd(cmd);
		if (!c) {
			free_line(result);
			return 0;
		}
		result->commands = my_realloc(result->commands, (result->n_commands + 1)*sizeof(command_t *));
		result->commands[result->n_commands++] = c;
		cmd = strtok_r(0, PIPE, &saveptr);
	}
	return result;
}

check_t check_redirections(const line_t* const l)
{
	assert(l);
	/* This function must check that:
	 * - Only the first command of a line can have input-redirection
	 * - Only the last command of a line can have output-redirection
	 * and return CHECK_OK if everything is ok, print a proper error
	 * message and return CHECK_FAILED otherwise
	 */
	/*** TO BE DONE START ***/

	//Con il seguente ciclo si eliminano i problemi dovuti a input e output.
	//I due if ammettono anche la possibilità che ci sia un solo comando con In e Out.
	//
	//Per ogni comando passato:
	for(int i = 0; i < l->n_commands; ++i){

		//se è il primo della lista, può avere input
		if((i != 0) && (l->commands[i]->in_pathname != 0)){
			perror("\nErrore: Solo il primo comando può redizionare l'input!\n");
			return CHECK_FAILED;
		}

		//se è l'ultimo della lista, può avere output
		if((i != l->n_commands-1) && (l->commands[i]->out_pathname != 0)){
			perror("\nErrore: Solo l'ultimo comando può redizionare l'output!\n");
			return CHECK_FAILED;
		}
	}

	//controlla se esiste il file std_in passato al primo comando:
	if(l->commands[0]->in_pathname)
		if(access(l->commands[0]->in_pathname, F_OK)){
			printf("\nErrore: File %s inesistente!\n", l->commands[0]->in_pathname);
			return CHECK_FAILED;
		}
			
	
	/*** TO BE DONE END ***/
	return CHECK_OK;
}

/*
DAL PDF:
...
Per semplicita', il comando cd puo' essere usato solo come primo e unico comando di una linea,
senza nessuna redirezione dell’I/O (nel caso l’utente cerchi di usare redirezioni o usi cd in pipe con altri comandi,
dovete segnalare un errore)
...
*/
check_t check_cd(const line_t* const l)
{
	assert(l);
	/* This function must check that if command "cd" is present in l, then such a command
	 * 1) must be the only command of the line
	 * 2) cannot have I/O redirections
	 * 3) must have only one argument
	 * and return CHECK_OK if everything is ok, print a proper error
	 * message and return CHECK_FAILED otherwise
	 */
	/*** TO BE DONE START ***/

	//controlla TUTTI i comandi cd
	for(int i = 0; i < l->n_commands; ++i)
		//strcmp ritorna 0 se le due stringhe parametro sono uguali
		if(!strcmp(l->commands[i]->args[0], CD)) {
			if(l->n_commands != 1){
				perror("\nErrore: Il comando cd non può essere utilizzato con altri comandi!\n");
				return CHECK_FAILED;
			}

			if(l->commands[0]->in_pathname != 0 || l->commands[0]->out_pathname != 0){
				perror("\nErrore: Il comando cd non può redizionare input/output!\n");
				return CHECK_FAILED;
			}

			//ricorda che la stringa è formata da 2 parametri:
			//0: "cd", 1: "/path/to/folder"
			if(l->commands[0]->n_args != 2){
				printf("\nErrore: Il comando cd prende UN SOLO argomento, non %i!\n", l->commands[0]->n_args-1);
				return CHECK_FAILED;
			}
		}
	
	
	/*** TO BE DONE END ***/
	return CHECK_OK;
}

void wait_for_children()
{
	/*  This function must wait for the termination of all child processes.
	 	If a child exits with an exit-status != 0, then you should print a 
	 	proper message containing its PID and exit-status.
	 	Similarly, if a child is killed by a signal, then you should print a 
		message specifying its PID, signal number and signal name.
	 */
	/*** TO BE DONE START ***/

	int stat;
	wait(&stat); 	//in questo modo verranno scritte informazioni di
					//terminazione su stat;
	
	if (WEXITSTATUS(stat))
		printf("-------Exit status: %d-------\n", WEXITSTATUS(stat));

	/*** TO BE DONE END ***/
}

void redirect(int from_fd, int to_fd)
{
	/* If from_fd != NO_REDIR, then the corresponding open file should be "moved" to to_fd.
	   That is, use dup/dup2/close to make to_fd equivalent to the original from_fd, and then close from_fd
	 */
	/*** TO BE DONE START ***/

	/*
		DAL MAN:
			The  dup(oldfd)  system call creates a copy of the file descriptor oldfd, 
			using the lowest-numbered unused file descriptor for the new descriptor.

			On  success, these system calls return the new file descriptor.  
			On error, -1 is returned, and errno is set appropriately.
	*/
	if(from_fd != NO_REDIR){
		if(dup2(from_fd, to_fd) == -1)
			fatal_errno("Errore nella dup");
		else
			close(from_fd);
	}

	/*** TO BE DONE END ***/
}

void run_child(const command_t* const c, int c_stdin, int c_stdout)
{
	/* This function must:
	 * 1) create a child process, then, in the child
		* 2) redirect c_stdin to STDIN_FILENO (=0)
		* 3) redirect c_stdout to STDOUT_FILENO (=1)
		* 4) execute the command specified in c->args[0] with the corresponding arguments c->args
		* (printing error messages in case of failure, obviously)
	 */
	/*** TO BE DONE START ***/
	
	pid_t pid;
	pid = fork(); //fork crea due processi figli

	if(pid < 0)
		fatal_errno("Errore nella fork");
	else if(pid == 0){
		//processo figlio

		//rendi c_stdin = 0 e c_stdout = 1.
		redirect(c_stdin, STDIN_FILENO);
		redirect(c_stdout, STDOUT_FILENO);

		//esegui il comando con execvp;
		//execvp ritorna -1 in caso di errore.
		if(execvp(c->args[0], c->args) == -1){
			if(errno == EACCES)
				fatal("Errore: file/comando non esistente e/o permessi mancanti");
			else if(errno == ENOENT)
				fatal("Errore: il comando/file non esiste");
			else if(errno == EIO)
				fatal("Errore: errore nell'I/O");
			else if(errno == ETXTBSY)
				fatal("Errore: risorsa già utilizzata da uno o più altri processi");
			else 
				//errore generico
				fatal_errno("Errore nell'esecuzione del comando");
		}

			
			
	}

	/*** TO BE DONE END ***/
}

void change_current_directory(char* newdir)
{
	/* Change the current working directory to newdir
	 * (printing an appropriate error message if the syscall fails)
	 */
	/*** TO BE DONE START ***/

	//Dal MAN:
	//On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
	if(chdir(newdir)){
		//controlla gli errori piu comuni. Altrimenti ritorna errore fatale
		if(errno == EACCES)
			printf("Errore: permessi mancanti per accedere a %s\n", newdir);
		else if(errno == ENOENT)
			printf("Errore: la cartella \"%s\" non esiste in questa directory\n", newdir);
		else if(errno == ENOTDIR)
			printf("Errore: %s non è una cartella\n", newdir);
		else 
			fatal_errno("Errore sconosciuto nel chdir");
	}	
		
	/*** TO BE DONE END ***/
}

void close_if_needed(int fd)
{
	if (fd==NO_REDIR)
		return; // nothing to do
	if (close(fd))
		perror("close in close_if_needed");
}

void execute_line(const line_t* const l)
{
	if (strcmp(CD, l->commands[0]->args[0])==0) {
		assert(l->n_commands == 1 && l->commands[0]->n_args == 2);
		change_current_directory(l->commands[0]->args[1]);
		return;
	}
	int next_stdin = NO_REDIR;
	for(int a=0; a<l->n_commands; ++a) {
		int curr_stdin = next_stdin, curr_stdout = NO_REDIR;
		const command_t * const c = l->commands[a];
		if (c->in_pathname) {
			assert(a == 0);
			/* Open c->in_pathname and assign the file-descriptor to curr_stdin
			   (handling error cases) */
			/*** TO BE DONE START ***/
			
			/*
				DAL MAN:
					On success, open() return the new file descriptor (a nonnegative integer).
					On error, -1 is returned and errno is set to indicate the error.
					...
					O_RDONLY: Apre un file per la lettura. L'offset e' all'inizio del file.
			*/
			if((curr_stdin = open(c->in_pathname, O_RDONLY)) == -1)
				fatal_errno("Errore nella open (stdin)");

			/*** TO BE DONE END ***/
		}
		if (c->out_pathname) {
			assert(a == (l->n_commands-1));
			/* Open c->out_pathname and assign the file-descriptor to curr_stdout
			 * (handling error cases) */
			/*** TO BE DONE START ***/

			/*
				DAL MAN:
					On success, open() return the new file descriptor (a nonnegative integer).
					On error, -1 is returned and errno is set to indicate the error.
					...
					O_WRONLY: Apre un file per la scrittura. La posizione e' all'inizio del file
					O_CREAT: Se pathname non esiste viene creato.
					O_TRUNC: Un possibile file esistente verra' sovrascritto
			*/
			//il flag 0600 è dovuto a: https://github.com/pantheon-systems/fusedav/issues/204
			if((curr_stdout = open(c->out_pathname, O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
				fatal_errno("Errore nella open (stdout)");

			/*** TO BE DONE END ***/
		} else if (a != (l->n_commands - 1)) { /* unless we're processing the last command, we need to connect the current command and the next one with a pipe */
			int fds[2];
			/* Create a pipe in fds, and set FD_CLOEXEC in both file-descriptor flags */
			/*** TO BE DONE START ***/
			
			/*
				DAL MAN:
					pipe(int pipefd[2])  creates  a  pipe,  a  unidirectional  data  channel that can be used for interprocess communication. 
					The array pipefd is used to return two file descriptors referring to the ends of the pipe.
       				pipefd[0] refers to the read end of the pipe. 
					pipefd[1] refers to the write end of the pipe.
					...
					On success, zero is returned.  On error, -1 is returned, errno is set appropriately

				NOTA: utilizzando pipe2 si possono specificare dei flag.
					In particolare O_CLOEXEC imposta i due file descriptor come close-on-exec,
					proprio come farebbe fcntl(fd, FD_CLOEXEC).

				DAL MAN DI fcntl:
					If the FD_CLOEXEC bit is set, the file descriptor  will  automatically 
					be closed during a successful execve(2) (If the execve(2) fails, the
					file descriptor is left open).
					|
					Quindi, in caso di errore nella exec, liberare la memoria.
			*/
			if(pipe2(fds, O_CLOEXEC))
				fatal_errno("Errore nella pipe");

			/*** TO BE DONE END ***/
			curr_stdout = fds[1];
			next_stdin = fds[0];
		}
		run_child(c, curr_stdin, curr_stdout);
		close_if_needed(curr_stdin);
		close_if_needed(curr_stdout);
	}
	wait_for_children();
}

void execute(char * const line)
{
	line_t* const l = parse_line(line);
#ifdef DEBUG
	print_line(l);
#endif
	if (l) {
		if (check_redirections(l)==CHECK_OK && check_cd(l)==CHECK_OK)
			execute_line(l);
		free_line(l);
	}
}

int main()
{
	const char* const prompt_suffix = " $ ";
	const size_t prompt_suffix_len = strlen(prompt_suffix);
	for(;;) {
		char *pwd;
		/* Make pwd point to a string containing the current working directory.
		   The memory area must be allocated (directly or indirectly) via malloc.
		 */
		/*** TO BE DONE START ***/

		/*
			Dal MAN di getcwd:
			...On success, these functions return a pointer to a string containing the pathname of the cur‐
			rent working directory.

			On failure, these functions return NULL, and errno is set to indicate the error...
		*/
		static const int PATHDIM = 256;

		pwd = my_malloc(PATHDIM);
		if((getcwd(pwd, PATHDIM)) == NULL)
			fatal_errno("Errore nel getcwd");

		/*** TO BE DONE END ***/
		pwd = my_realloc(pwd, strlen(pwd) + prompt_suffix_len + 1);
		strcat(pwd, prompt_suffix);
		char * const line = readline(pwd);
		free(pwd);
		if (!line) break;
		execute(line);
		free(line);
	}
}

