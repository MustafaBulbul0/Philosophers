#include "./../philo.h"

void	init_data(t_thread *data, char **argv, int argc)
{
	data->num_philo = ft_atoi(argv[1]);
	data->death_time = ft_atoi(argv[2]);
	data->eat_time = ft_atoi(argv[3]);
	data->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meal = ft_atoi(argv[5]);
	else
		data->num_meal = -1;
	data->stop = 0;
	data->return_val = 1;
}

static void	init_table(t_philo_table *table,
	t_thread *data, t_philo_table *tail)
{
	int				num;
	t_philo_table	*temp;

	num = 1;
	tail->next = table;
	temp = table;
	while (num <= data->num_philo)
	{
		temp->philo_num = num;
		temp->meal_time = 0;
		temp->total_meal = 0;
		temp = temp->next;
		num++;
	}
}

int	sit_table(t_philo_table **table, t_thread *data)
{
	int				i;
	t_philo_table	*new_node;
	t_philo_table	*head;
	t_philo_table	*tail;

	head = (t_philo_table *)malloc(sizeof(t_philo_table));
	if (!head)
		return (0);
	pthread_mutex_init(&(head->fork), NULL);
	head->next = NULL;
	tail = head;
	i = 0;
	while (++i < data->num_philo)
	{
		new_node = (t_philo_table *)malloc(sizeof(t_philo_table));
		if (!new_node)
			return (0);
		pthread_mutex_init(&(new_node->fork), NULL);
		new_node->next = NULL;
		tail->next = new_node;
		tail = new_node;
	}
	init_table(head, data, tail);
	*table = head;
	return (1);
}
