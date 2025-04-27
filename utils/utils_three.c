#include "./../philo.h"

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
