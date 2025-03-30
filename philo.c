#include "philo.h"

int	arg_checker(char **argv);

int main(int argc, char **argv)
{
	t_thread		*data;
	t_philo_table	**table;

	if (argc < 5 || argc > 6)
		return (0);
	if (arg_checker(argv))
		return (0);
	data = (t_thread *)malloc(sizeof(t_thread));
	if (!data)
		return (0);
	init_data(data, argc, argv);
	table = (t_philo_table **)malloc(sizeof(t_philo_table *));
	if (!table)
	{
		free(data);
		return (0);
	}
	data->return_val = sit_table(table, data);
	if (data->return_val)
		create_thread(data->philo_num, data, table);
	shut_program_scc(table, data);
	return (0);
}

int	arg_checker(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
