#include "../philo.h"

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
	return (0);
}
