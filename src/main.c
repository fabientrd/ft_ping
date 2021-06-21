#include "../includes/ft_ping.h"

/*void check_ip(char *s, t_env *env){
	return ;
}*/

void init_env(t_env *env){
	env->v = 0;
	env->h = 0;
	env->err = '\0';
	env->ip = NULL;
}

int  fill_env(t_env *env, char **av){
	int i;
	int y;

	init_env(env);
	for (i = 1; av[i] != NULL; i++){
		if (av[i][0] == '-'){
			for (y = 1; av[i][y] != '\0'; y++){
				if (av[i][y] == 'v')
					env->v = 1;
				else if (av[i][y] == 'h')
					env->h = 1;
				else{
					env->err = av[i][y];
					return (1);
				}
			}
		}
		else{
//			check_ip(av[i], env);
		}
	}
	return (0);
}

int		main(int ac, char **av){
	t_env env;
	
	if (ac == 1){
		printf("ping: usage error: Destination address required\n");
		return (EXIT_FAILURE);
	}
	if (fill_env(&env, av)){
		printf("ping: invalid option -- '%c'\n\nUsage\n  ping [options] <destination>\n\nOptions:\n  <destination>	dns name or ip address\n  -v	verbose output\n  -h	print help and exit\n\nFor more details see ping(8)", env.err);
		return (EXIT_FAILURE);
	}
	else{
	
	}
	return (0);
}
