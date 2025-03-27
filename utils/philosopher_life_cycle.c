#include "../philo.h"

static void	thinking_time(t_philo_table **table , t_thread *data)
{
	get_time(data, (*table)->philo_num, "is thinking");
}

static void	sleeping_time(t_philo_table **table, t_thread *data)
{
	get_time(data, (*table)->philo_num, "is sleeping");
	(*table)->meal_time += data->sleep_time;
	usleep((data->sleep_time) * 1000);
}

static void	eating_time(t_philo_table **table, t_thread *data)
{
	(*table)->meal_time = 0;
	(*table)->total_meal++;
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "is eating");
	usleep((data->eat_time) * 1000);
}

static void lock_unlock_forks(t_philo_table *table, int lock)
{
    t_philo_table *left_fork;
    t_philo_table *right_fork;

    if (table->philo_num < table->next->philo_num)
    {
        left_fork = table;
        right_fork = table->next;
    }
    else
    {
        left_fork = table->next;
        right_fork = table;
    }
	if (lock ==1)
    {
		pthread_mutex_lock(&(left_fork->fork));
    	pthread_mutex_lock(&(right_fork->fork));
	}
	else
	{
		pthread_mutex_unlock(&(right_fork->fork));
    	pthread_mutex_unlock(&(left_fork->fork));
	}
}

void	*thread_operations(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	*table;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	while (1)
	{
			lock_unlock_forks(table, 1);
			eating_time(&table, data);
			lock_unlock_forks(table, 0);
			sleeping_time(&table, data);
			thinking_time(&table, data);
	}
	return (NULL);
}
