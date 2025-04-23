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
