#include "../philo.h"


void	init_data(t_thread *data, int argc, char **argv)
{
	data->philo_num = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->meals_num = ft_atoi(argv[5]);
	else
		data->meals_num = -1;
}

int	ft_atoi(char *chNum)
{
	int				i;
	int				k;
	long long int	j;

	i = 0;
	j = 0;
	k = 1;
	while ((chNum[i] < 14 && (chNum[i] > 8)) || chNum[i] == 32)
		i++;
	if (chNum[i] == 45 || chNum[i] == 43)
	{
		if (chNum[i] == 45)
			k = -1;
		i++;
	}
	while (chNum[i] >= '0' && chNum[i] <= '9')
	{
		j = j * 10 + (chNum[i] - '0');
		i++;
	}
	return (j * k);
}

void	sit_table(t_philo_table **table, t_thread *data)
{
	int			 i;
	t_philo_table *new_node;
	t_philo_table *head;
	t_philo_table *tail;

	head = (t_philo_table *)malloc(sizeof(t_philo_table));
	if (!head)
		shut_program_err(table, data);
	head->philo_num = 1;
	head->thinking = 1;
	head->meal_time = 0;
	head->next = NULL;
	tail = head;
	i = 1;
	while (i < data->philo_num)
	{
		new_node = (t_philo_table *)malloc(sizeof(t_philo_table));
		if (!new_node)
			shut_program_err(table, data);
		new_node->philo_num = i + 1;
		new_node->thinking = 1;
		new_node->meal_time = 0;
		new_node->next = NULL;
		tail->next = new_node;
		tail = new_node;
		i++;
	}
	tail->next = head;
	*table = head;
}
