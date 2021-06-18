#ifndef FT_PING_H
# define FT_PING_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <signal.h>


typedef struct	s_env{
	int v;
	int h;
	char err;
	char *ip;
}				t_env;

# endif
