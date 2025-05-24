#include "./../philo.h"

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

t_philo_table	*turn_back(t_philo_table *table)
{
	t_philo_table	*temp;
	int				philo;

	philo = table->philo_num - 1;
	temp = table;
	while (temp->philo_num != philo)
		temp = temp->next;
	return (temp);
}

int	time_diff(struct timeval start, struct timeval end)
{
	int	time;

	time = (end.tv_sec - start.tv_sec) * 1000;
	time += (end.tv_usec - start.tv_usec) / 1000;
	return (time);
}

int	philo_control(t_thread *data)
{
	if (data->num_philo == 1)
	{
		printf("0 1 has taken a fork\n");
		printf("%d 1 died\n", data->death_time);
		return (1);
	}
	return (0);
}
