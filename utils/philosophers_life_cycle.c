#include "./../philo.h"

static void	thinking_time(t_philo_table **table, t_thread *data)
{
	usleep(1000);
	gettimeofday(&((*table)->thinking_start), NULL);
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
	long long		time;

	gettimeofday(&((*table)->thinking_end), NULL);
	time = time_diff((*table)->thinking_start, (*table)->thinking_end);
	if ((*table)->total_meal != 0)
		(*table)->meal_time += time;
	(*table)->meal_time += data->eat_time;
	if ((*table)->meal_time > data->death_time)
	{
		data->stop = 1;
		time = time_diff(data->start, (*table)->thinking_end);
		printf("%lld %d died\n", time, (*table)->philo_num);
		return ;
	}
	(*table)->meal_time = 0;
	(*table)->total_meal++;
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "is eating");
	usleep((data->eat_time) * 1000);
}

static void	lock_unlock_forks(t_philo_table *table, int lock)
{
	t_philo_table	*left_fork;
	t_philo_table	*right_fork;

	if (table->philo_num % 2 == 1)
	{
		right_fork = table;
		left_fork = table->next;
	}
	else
	{
		left_fork = table;
		right_fork = turn_back(table);
	}
	if (lock == 1)
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
		if (data->stop == 0)
			eating_time(&table, data);
		total_meal_control(table, data);
		lock_unlock_forks(table, 0);
		if (data->stop == 0)
			sleeping_time(&table, data);
		if (data->stop == 0)
			thinking_time(&table, data);
		if (data->stop)
			break ;
	}
	return (NULL);
}
