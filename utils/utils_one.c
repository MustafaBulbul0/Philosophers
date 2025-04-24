#include "./../philo.h"

static int	ft_atoi(char *chNum)
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

static void	init_table(t_philo_table *table, t_thread *data, t_philo_table *tail)
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

void	get_time(t_thread *data, int philo, char *text)
{
	struct timeval	end;
	long long		time;

	pthread_mutex_lock(&(data->lock));
	gettimeofday(&end, NULL);
	time = time_diff(data->start, end);
	if (data->stop == 0)
		printf("%lld %d %s\n", time, philo, text);
	pthread_mutex_unlock(&(data->lock));
}
