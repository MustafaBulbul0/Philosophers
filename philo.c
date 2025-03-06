#include "philo.h"

int	arg_checker(char **argv);

int main(int argc, char **argv)
{
	t_data	*data;

	if (argc < 5 || argc > 6)
		return (1);
	if (arg_checker(argv))
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	init_data(data, argc, argv);

	shut_prgram_scc(NULL, data);
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
			if (!(argv[i][j] > '0' && argv[i][j] < '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
