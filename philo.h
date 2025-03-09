#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_thread
{
	pthread_t		thread1;
	void			**ret_val;
	pthread_mutex_t	*mutex;

	int	philo_num;
	int	death_time;
	int	eat_time;
	int	sleep_time;
	int	meals_num;
}	t_thread;

typedef	struct s_philo_table
{
	int						philo_num;
	int						num;		//2 yemek yemeli 1 yemek yiyemez çatalı yok
	int						before_num;
	int						meal_time;	//kaç keredir yemek yemiyor
	struct s_philo_table	*next;
}	t_philo_table;

void	shut_program_err(t_philo_table **table, t_thread *data);
void	shut_program_scc(t_philo_table **table, t_thread *data);
int		arg_checker(char **argv);
void	init_data(t_thread *data, int argc, char **argv);
int		ft_atoi(char *chNum);
void	sit_table(t_philo_table **table, t_thread *data);
void	who_do_what(t_philo_table **table, t_thread *data);

#endif
