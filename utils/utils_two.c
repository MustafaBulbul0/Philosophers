#include "../philo.h"

static void	*thread_operations(void *all_structs);

void	thinking_time(t_philo_table **table)
{
	(*table)->thinking = 1;
}

void	sleeping_time(t_philo_table **table, t_thread *data)
{
	struct timeval	start;
	struct timeval	end;

	(*table)->num = 3;
	gettimeofday(&start, NULL);
	usleep(data->sleep_time);
	gettimeofday(&end, NULL);
	printf("%ld\n", end.tv_usec - start.tv_usec);
	(*table)->meal_time += data->sleep_time;
}
int	is_dead(t_philo_table **table, t_thread *data)
{
	if ((*table)->meal_time > data->death_time)
		return (0);
	(*table) = (*table)->next;
	while ((*table)->philo_num != 1)
	{
		if ((*table)->meal_time > data->death_time)
			return (0);
		(*table) = (*table)->next;
	}
	return (1);
}

void	*monitor(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	**table;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	while (is_dead(table, data))
	{
		pthread_mutex_lock(&(data->lock));

		pthread_mutex_unlock(&(data->lock));
	}
	pthread_mutex_destroy(&(data->lock));
}

void	creat_thread(int thread_count, t_thread *data, t_philo_table **table)
{
	pthread_t	thread[thread_count + 1];
	t_structs	*all_structs;
	int			i;

	all_structs = (t_structs *)malloc(sizeof(t_structs));
	all_structs->data = data;
	all_structs->table = table;
	pthread_mutex_init(&(data->lock), NULL);
	pthread_create(&thread[0], NULL, monitor, (void *)all_structs);
	i = -1;
	while (++i < thread_count)
	{
		(*table)->philo_num = i + 1;
		pthread_create(&thread[i], NULL, thread_operations, (void *)all_structs);
		usleep(100);
		(*table) = (*table)->next;
	}
	i = -1;
	while (++i < thread_count)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&(data->lock));
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



}
