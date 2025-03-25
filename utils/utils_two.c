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
			printf("%lld %d died", time, death_philo);
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

void lock_forks(t_philo_table *table)
{
    t_philo_table *left_fork;
    t_philo_table *right_fork;

    if (table->philo_num < table->next->philo_num)
    {
        left_fork = table;
        right_fork = table->next;
    }
    else
    {
        left_fork = table->next;
        right_fork = table;
    }

    pthread_mutex_lock(&(left_fork->fork));
    pthread_mutex_lock(&(right_fork->fork));
}

void unlock_forks(t_philo_table *table)
{
    t_philo_table *left_fork;
    t_philo_table *right_fork;

    if (table->philo_num < table->next->philo_num)
    {
        left_fork = table;
        right_fork = table->next;
    }
    else
    {
        left_fork = table->next;
        right_fork = table;
    }
    pthread_mutex_unlock(&(right_fork->fork));
    pthread_mutex_unlock(&(left_fork->fork));
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
			lock_forks(table);
			eating_time(&table, data);
			unlock_forks(table);
			sleeping_time(&table, data);
			thinking_time(&table, data);
	}
	return (NULL);
}
