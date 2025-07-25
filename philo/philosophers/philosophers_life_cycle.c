#include "./../philo.h"

static void	thinking_time(t_philo_table **table, t_thread *data)
{
	usleep(1000);
	gettimeofday(&((*table)->thinking_start), NULL);
	pthread_mutex_lock(&data->lock);
	get_time(data, (*table)->philo_num, "is thinking");
	pthread_mutex_unlock(&data->lock);
}

static void	sleeping_time(t_philo_table **table, t_thread *data)
{
	pthread_mutex_lock(&data->lock);
	get_time(data, (*table)->philo_num, "is sleeping");
	(*table)->meal_time += data->sleep_time;
	if (data->sleep_time >= data->death_time)
	{
		usleep(data->death_time * 1000);
		get_time(data, (*table)->philo_num, "died");
		data->stop = 1;
		pthread_mutex_unlock(&data->lock);
		return ;
	}
	pthread_mutex_unlock(&data->lock);
	usleep((data->sleep_time) * 1000);
}

static void	eating_time(t_philo_table **table, t_thread *data)
{
	long long		time;

	gettimeofday(&((*table)->thinking_end), NULL);
	pthread_mutex_lock(&data->lock);
	if ((*table)->total_meal != 0)
	{
		time = time_diff((*table)->thinking_start, (*table)->thinking_end);
		(*table)->meal_time += time;
	}
	if ((*table)->meal_time > data->death_time)
	{
		data->stop = 1;
		time = time_diff(data->start, (*table)->thinking_end);
		pthread_mutex_unlock(&data->lock);
		printf("%lld %d died\n", time, (*table)->philo_num);
		return ;
	}
	if (ft_eating(table, data))
		return ;
	(*table)->meal_time = 0;
	(*table)->total_meal++;
	pthread_mutex_unlock(&data->lock);
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
	while (check_if_stopped(data) == 0)
	{
		lock_unlock_forks(table, 1);
		if (check_if_stopped(data) == 0)
			eating_time(&table, data);
		total_meal_control(table, data);
		lock_unlock_forks(table, 0);
		if (check_if_stopped(data) == 0)
			sleeping_time(&table, data);
		if (check_if_stopped(data) == 0)
			thinking_time(&table, data);
	}
	free(all_structs);
	return (NULL);
}
