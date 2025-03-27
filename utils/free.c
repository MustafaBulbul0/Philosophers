#include "../philo.h"

static void free_table(t_philo_table **table);

void shut_program_err(t_philo_table **table, t_thread *data)
{
	if (data)
		free(data);
	if (table && *table)
		free_table(table);
	write(2, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void shut_program_scc(t_philo_table **table, t_thread *data)
{
	if (data)
		free(data);
	if (table && *table)
		free_table(table);
	exit(EXIT_SUCCESS);
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
	*table = NULL; // bunu bırak (doğru)
	// free(table); (BU SATIRI KALDIR!)
}
