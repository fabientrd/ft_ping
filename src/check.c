#include "../includes/ft_ping.h"

int loop = 1;

void  handler(){
	loop = 0;
	return ;
}

int init_ping(t_env *env){
	int sock;

	printf("PING %s (%s) %d(%d) bytes of data.\n", env->dest, env->addrstr, env->s, env->s + 28);
	signal(SIGINT, handler);
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sock < 0)
		return (1);
	send_ping(sock, env);
	return (0);
}

int		lookup_dest(t_env *env){
	int i;
	char addrstr[100];
	struct addrinfo hints, *res, *result;
	void *ptr;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = PF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags |= AI_CANONNAME;
	i = getaddrinfo(env->dest, NULL, &hints, &result);
	if (i != 0){
		printf("ping: %s: Name or service not known\n", env->dest);
		return (1);
	}
	for (res = result; res != NULL; res = res->ai_next){
		inet_ntop(res->ai_family, res->ai_addr->sa_data, addrstr, 100);
		switch (res->ai_family){
			case AF_INET:
				ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
				break ;
			case AF_INET6:
				ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
				break ;
        }
		inet_ntop (res->ai_family, ptr, addrstr, 100);
		if (res->ai_family == PF_INET)
			env->addrstr = ft_strdup(addrstr);
		else if (res->ai_family == PF_INET6)
			env->addrstr6 = ft_strdup(addrstr);
		printf ("IPv%d address: %s (%s)\n", res->ai_family == PF_INET6 ? 6 : 4,
              addrstr, res->ai_canonname);
//		if (ptr)  BUG WITH ASIGNATION OF ADDRSTR
//			break ;
	}
	printf("hints.ai_family = %d\n", result->ai_family);
	printf("env->addrstr = %s\n", env->addrstr);
	printf("env->addrstr6 = %s\n", env->addrstr6);
	if (init_ping(env)){
		printf("A problem ocurred during the initialization of the socket\n");
		return (1);
	}
	freeaddrinfo(result);
	return (0);
}
