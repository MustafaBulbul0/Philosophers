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

	int				philo_num;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meals_num;
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

void			shut_program_scc(t_philo_table **table, t_thread *data);
void			init_data(t_thread *data, int argc, char **argv);
int				sit_table(t_philo_table **table, t_thread *data);
void			create_thread(int thread_count, t_thread *data, t_philo_table **table);
void			*thread_operations(void *all_structs);
int				is_full(t_philo_table *table, t_thread *data);
void			get_time(t_thread *data, int philo, char *text);
void			total_meal_control(t_philo_table *table, t_thread *data);
t_philo_table	*turn_back(t_philo_table *table);

#endif