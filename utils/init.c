#include "../philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_num = ft_atoi(argv[5]);
}
