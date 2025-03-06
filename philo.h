#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_thread
{
	pthread_t		thread1;
	void			**ret_val;
	pthread_mutex_t	*mutex;
}	t_thread;

typedef struct	s_data
{
	int	philo_num;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	meals_num;

}	t_data;

void	shut_prgram_err(t_thread *thread, t_data *data);
void	shut_prgram_scc(t_thread *thread, t_data *data);
int		arg_checker(char **argv);
void	init_data(t_data *data, int argc, char **argv);
int		ft_atoi(char *chNum);

#endif
