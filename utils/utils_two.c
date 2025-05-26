#include "../philo.h"

static int	getting_started(t_philo_table **table, t_thread *data);

int	ft_eating(t_philo_table **table, t_thread *data)
{
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "is eating");
	if (((*table)->meal_time + data->eat_time) >= data->death_time)
	{
		usleep((data->death_time - (*table)->meal_time) * 1000);
		get_time(data, (*table)->philo_num, "died");
		data->stop = 1;
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	if ((*table)->total_meal == 0)
	{
		if (getting_started(table, data))
			return (1);
	}
	return (0);
}

static int	getting_started(t_philo_table **table, t_thread *data)
{
	long long	time;

	gettimeofday(&data->end, NULL);
	time = time_diff(data->start, data->end);
	if ((time + data->eat_time) >= data->death_time)
	{
		if (data->death_time > time)
			usleep((data->death_time - time) * 1000);
		get_time(data, (*table)->philo_num, "died");
		data->stop = 1;
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	return (0);
}
