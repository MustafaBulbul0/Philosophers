#include "../philo.h"

static void	*thread_operations(void *all_structs);

static void	thinking_time(t_philo_table **table , t_thread *data)
{
	struct timeval end;

	printf("%ld %d is thinking\n", (end.tv_usec - data->start.tv_usec) / 1000, (*table)->philo_num);
	(*table)->thinking = 1;
}

static void	sleeping_time(t_philo_table **table, t_thread *data)
{
	struct timeval	end;

	pthread_mutex_lock(&(data->lock));
	usleep((data->sleep_time) * 1000);
	gettimeofday(&end, NULL);
	printf("%ld %d is sleeping\n", (end.tv_usec - data->start.tv_usec) / 1000, (*table)->philo_num);
	(*table)->meal_time += data->sleep_time;
	pthread_mutex_unlock(&(data->lock));
}

static void	eating_time(t_philo_table **table, t_thread *data)
{
	struct timeval	end;
	
	pthread_mutex_lock(&(data->lock));
	(*table)->thinking = 0;
	(*table)->meal_time = 0;
	usleep((data->eat_time) * 1000);
	gettimeofday(&end,NULL);
	printf("%ld %d has taken a fork\n", (end.tv_usec - data->start.tv_usec) / 1000, (*table)->philo_num);
	printf("%ld %d has taken a fork\n", (end.tv_usec - data->start.tv_usec) / 1000, (*table)->philo_num);
	printf("%ld %d is eating\n", (end.tv_usec - data->start.tv_usec) / 1000, (*table)->philo_num);
	pthread_mutex_unlock(&(data->lock));
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
	t_philo_table	*table;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	while (is_dead(&table, data))
	{
		pthread_mutex_lock(&(data->lock));

		pthread_mutex_unlock(&(data->lock));
	}
}

void	create_thread(int thread_count, t_thread *data, t_philo_table **table)
{
	pthread_t		thread[thread_count + 1];
	t_philo_table	*temp;
	t_structs		*all_structs;
	int				i;

	temp = (*table);
	all_structs = (t_structs *)malloc(sizeof(t_structs));
	all_structs->data = data;
	all_structs->table = (*table);
	pthread_mutex_init(&(data->lock), NULL);
	pthread_create(&thread[0], NULL, monitor, (void *)all_structs);
	i = 0;
	gettimeofday(&(data->start), NULL);
	while (++i < thread_count + 1)
	{
		all_structs->table = temp;
		pthread_create(&thread[i], NULL, thread_operations, (void *)all_structs);
		usleep(1000);
		temp = temp->next;
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
	t_philo_table	*table;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;

	while (1)
	{
		if (table->changed)
		{
			eating_time(&table, data);
			sleeping_time(&table, data);
			thinking_time(&table, data);
		}
	}
}
