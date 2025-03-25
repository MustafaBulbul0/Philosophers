#include "../philo.h"

static void	*thread_operations(void *all_structs);

static void	thinking_time(t_philo_table **table , t_thread *data)
{
	get_time(data, (*table)->philo_num, "is thinking");
}

static void	sleeping_time(t_philo_table **table, t_thread *data)
{
	struct timeval	end;

	get_time(data, (*table)->philo_num, "is sleeping");
	(*table)->meal_time += data->sleep_time;
	usleep((data->sleep_time) * 1000);
}

static void	eating_time(t_philo_table **table, t_thread *data)
{
	struct timeval	end;

	(*table)->meal_time = 0;
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "has taken a fork");
	get_time(data, (*table)->philo_num, "is eating");
	usleep((data->eat_time) * 1000);
}

int	is_dead(t_philo_table **table, t_thread *data)
{
	if ((*table)->meal_time > data->death_time)
		return ((*table)->philo_num);
	(*table) = (*table)->next;
	while ((*table)->philo_num != 1)
	{
		if ((*table)->meal_time > data->death_time)
			return ((*table)->philo_num);
		(*table) = (*table)->next;
	}
	return (-1);
}

void	*monitor(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	*table;
	int				death_philo;
	long long		time;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	while (1)
	{
		death_philo = is_dead(&(table), data);
		if (death_philo != -1)
		{
			gettimeofday(&(data->end), NULL);
			time = (data->end.tv_sec - data->start.tv_sec) * 1000;
			time += (data->end.tv_usec - data->start.tv_usec) / 1000;
			printf("%lld %d is died", time, death_philo);
			exit(EXIT_FAILURE);
		}
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
		usleep(100);
		temp = temp->next;
	}
	i = -1;
	while (++i < thread_count)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&(data->lock));
	free(all_structs);
	all_structs = NULL;
}

void	mutex_lock(t_philo_table *table, int lock_unlock)
{
	int	philo;
	t_philo_table *temp;

	temp = table;
	if (lock_unlock == 1)
	{
		pthread_mutex_lock(&(temp->fork));
		philo = temp->philo_num - 1;
		while (temp->philo_num == philo)
			temp = temp->next;
		pthread_mutex_lock(&(table->fork));
	}
	else if (lock_unlock == 2)
	{
		pthread_mutex_unlock(&(temp->fork));
		philo = temp->philo_num - 1;
		while (temp->philo_num == philo)
			temp = temp->next;
		pthread_mutex_unlock(&(table->fork));
	}
}

static void	*thread_operations(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	*table;
	int				odd_even;

	structs = (t_structs *)all_structs;
	data = structs->data;
	table = structs->table;
	pthread_mutex_init(&(table->fork), NULL);
	odd_even = 1;
	if (((table->philo_num / 2) * 2) == table->philo_num)
		odd_even = 2;
	while (1)
	{
		if (odd_even == 1)
		{
			pthread_mutex_lock(&(table->fork));
			pthread_mutex_lock(&(table->next->fork));
			eating_time(&table, data);
			sleeping_time(&table, data);
			pthread_mutex_unlock(&(table->fork));
			pthread_mutex_unlock(&(table->next->fork));
			thinking_time(&table, data);
		}
		else if (odd_even == 2)
		{
			mutex_lock(table, 1);
			eating_time(&table, data);
			sleeping_time(&table, data);
			mutex_lock(table, 2);
			thinking_time(&table, data);
		}
	}
}
