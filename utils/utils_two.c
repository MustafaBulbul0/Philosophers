#include "../philo.h"

static int	is_dead(t_philo_table **table, t_thread *data)
{
	t_philo_table	**temp;

	temp = table;
	if ((*temp)->meal_time > data->death_time)
		return ((*temp)->philo_num);
	(*temp) = (*temp)->next;
	while ((*temp)->philo_num != 1)
	{
		if ((*temp)->meal_time > data->death_time)
			return ((*temp)->philo_num);
		(*temp) = (*temp)->next;
	}
	return (-1);
}

int	is_full(t_philo_table *table, t_thread *data)
{
	t_philo_table	*temp;

	temp = table;
	if (data->meals_num == -1)
		return (0);
	if (temp->total_meal < data->meals_num)
		return (0);
	temp = temp->next;
	while (temp->philo_num != 1)
	{
		if (temp->total_meal < data->meals_num - 1)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static void	*monitor(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	*table;
	int				philo_situation;
	long long		time;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	while (data->stop != 1)
	{
		philo_situation = is_dead(&(table), data);
		if (philo_situation != -1)
		{
			data->stop = 1;
			gettimeofday(&(data->end), NULL);
			time = (data->end.tv_sec - data->start.tv_sec) * 1000;
			time += (data->end.tv_usec - data->start.tv_usec) / 1000;
			printf("%lld %d died\n", time, philo_situation);
			break ;
		}
	}
	free(structs);
	return (NULL);
}

void	create_thread(int thread_count, t_thread *data, t_philo_table **table)
{
	pthread_t		thread[thread_count + 1];
	t_philo_table	*temp;
	t_structs		*all_structs;
	int				i;

	pthread_mutex_init(&(data->lock), NULL);
	temp = (*table);
	all_structs = (t_structs *)malloc(sizeof(t_structs));
	all_structs->data = data;
	all_structs->table = temp;
	gettimeofday(&(data->start), NULL);
	pthread_create(&thread[0], NULL, monitor, (void *)all_structs);
	i = 0;
	while (++i < thread_count + 1)
	{
		t_structs	*new_struct = (t_structs *)malloc(sizeof(t_structs));
		new_struct->data = data;
		new_struct->table = temp;
		pthread_create(&thread[i], NULL, thread_operations, (void *)new_struct);
		temp = temp->next;
	}
	i = -1;
	while (++i < thread_count)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&(data->lock));
}

void	total_meal_control(t_philo_table *table, t_thread *data)
{
	t_philo_table	*temp;
	int				i;

	i = 0;
	if (data->meals_num == -1)
		return ;
	temp = table;
	while (i < data->philo_num)
	{
		if (temp->total_meal < data->meals_num)
			return ;
		temp = temp->next;
		i++;
	}
	data->stop = 1;
}
