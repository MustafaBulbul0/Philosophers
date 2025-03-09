#include "../philo.h"

static void	free_table(t_philo_table **table);
static void	free_thread(t_thread *data);

void	shut_program_err(t_philo_table **table, t_thread *data)
{
	if (data)
		free_thread(data);
	if (table)
		free_table(table);
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void	shut_program_scc(t_philo_table **table, t_thread *data)
{
	if (data)
		free_thread(data);
	if (table)
		free_table(table);
	exit(EXIT_SUCCESS);
}

static void	free_thread(t_thread *data)
{
	int i;

	if (data->mutex)
	{
		pthread_mutex_destroy(data->mutex);
		free(data->mutex);
	}
	if (data->ret_val)
	{
		i = 0;
		while (data->ret_val[i])
		{
			free(data->ret_val[i]);
			i++;
		}
		free(data->ret_val);
	}
	free(data);
}

void free_table(t_philo_table **table)
{
	t_philo_table *temp;
	t_philo_table *current;
	t_philo_table *head;

	if (!table || !*table)
		return;
	head = *table;
	current = head->next;

	while (current != head)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	free(head);
	*table = NULL;
	free(table);
	table = NULL;
}
