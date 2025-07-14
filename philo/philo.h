#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_thread
{
	pthread_mutex_t	lock;
	struct timeval	start;
	struct timeval	end;

	int				num_philo;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				num_meal;
	int				stop;
	int				return_val;
}	t_thread;

typedef struct s_philo_table
{
	int						philo_num;
	int						meal_time;
	int						total_meal;
	struct timeval			thinking_start;
	struct timeval			thinking_end;
	pthread_mutex_t			fork;
	struct s_philo_table	*next;
}	t_philo_table;

typedef struct s_structs
{
	t_thread		*data;
	t_philo_table	*table;
}	t_structs;

void			init_data(t_thread *data, char **argv, int argc);
int				sit_table(t_philo_table **table, t_thread *data);
void			shut_program_scc(t_philo_table **table, t_thread *data);
void			get_time(t_thread *data, int philo, char *text);
t_philo_table	*turn_back(t_philo_table *table);
void			*thread_operations(void *all_structs);
void			total_meal_control(t_philo_table *table, t_thread *data);
void			creat_thread(t_thread *data, t_philo_table **table);
int				time_diff(struct timeval start, struct timeval end);
int				philo_control(t_thread *data);
int				ft_atoi(char *chNum);
int				ft_eating(t_philo_table **table, t_thread *data);

#endif