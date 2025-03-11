#include "../philo.h"

static void	*thread_operations(void *all_structs);

void	creat_thread(int thread_count, t_thread *data, t_philo_table **table)
{
	pthread_t	thread[thread_count];
	t_structs	*all_structs;
	int			i;

	all_structs = (t_structs *)malloc(sizeof(t_structs));
	all_structs->data = data;
	all_structs->table = table;
	i = -1;
	while (++i < thread_count)
		pthread_create(&thread[i], NULL, thread_operations, (void *)all_structs);
	i = -1;
	while (++i < thread_count)
		pthread_join(thread[i], NULL);
	free(all_structs);
	all_structs = NULL;
}

static void	*thread_operations(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	**table;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	pthread_mutex_init(&(data->lock), NULL);



	pthread_mutex_destroy(&(data->lock));
}
