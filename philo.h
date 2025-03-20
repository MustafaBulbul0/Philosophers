#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#include <sys/time.h>

typedef struct	s_thread
{
	pthread_mutex_t	lock;

	int	philo_num;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	meals_num;
}	t_thread;

typedef	struct s_philo_table
{
	int						philo_num;
	int						num;		//3 uyur 2 yemek yemeli 1 yemek yiyemez çatalı yok
	int						before_num;
	int						thinking;	//0 hayır , 1 evet
	int						meal_time;	//yemek yemediği süre
	struct s_philo_table	*next;
}	t_philo_table;

typedef struct s_structs
{
	t_thread		*data;
	t_philo_table	**table;
}	t_structs;

void	shut_program_err(t_philo_table **table, t_thread *data);
void	shut_program_scc(t_philo_table **table, t_thread *data);
int		arg_checker(char **argv);
void	init_data(t_thread *data, int argc, char **argv);
int		ft_atoi(char *chNum);
void	sit_table(t_philo_table **table, t_thread *data);
void	creat_thread(int thread_count, t_thread *data, t_philo_table **table);

#endif
