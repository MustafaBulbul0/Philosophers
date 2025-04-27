#include "./../philo.h"

static void	*monitor(void *all_structs);
t_structs	*new_struct_operation(t_thread *data, t_philo_table **table);

void	creat_thread(t_thread *data, t_philo_table **table)
{
	pthread_t		*thread;
	t_philo_table	*temp;
	t_structs		*all_structs;
	t_structs		*new_struct;
	int				i;

	thread = (pthread_t *)malloc(sizeof(pthread_t) * (data->num_philo + 1));
	pthread_mutex_init(&(data->lock), NULL);
	temp = *table;
	all_structs = (t_structs *)malloc(sizeof(t_structs));
	all_structs->data = data;
	all_structs->table = temp;
	gettimeofday(&(data->start), NULL);
	pthread_create(&thread[0], NULL, monitor, (void *)all_structs);
	i = 0;
	while (++i < data->num_philo + 1)
	{
		new_struct = new_struct_operation(data, &temp);
		pthread_create(&thread[i], NULL, thread_operations, (void *)new_struct);
		temp = temp->next;
	}
	i = -1;
	while (++i <= data->num_philo)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&(data->lock));
}

t_structs	*new_struct_operation(t_thread *data, t_philo_table **table)
{
	t_structs	*new_struct;

	new_struct = (t_structs *)malloc(sizeof(t_structs));
	new_struct->data = data;
	new_struct->table = (*table);
	return (new_struct);
}

static void	*monitor(void *all_structs)
{
	t_structs		*structs;
	t_thread		*data;
	t_philo_table	*temp;
	int				i;

	structs = (t_structs *)all_structs;
	data = structs->data;
	temp = structs->table;
	if (data->num_meal != -1 && data->stop == 0)
	{
		while (data->stop == 0)
		{
			i = 0;
			while (i <= data->num_philo && temp->total_meal >= data->num_meal)
			{
				temp = temp->next;
				if (i >= data->num_philo)
					data->stop = 1;
				i++;
			}
		}
	}
	return (NULL);
}

void	total_meal_control(t_philo_table *table, t_thread *data)
{
	t_philo_table	*temp;
	int				i;

	i = 0;
	if (data->num_meal == -1)
		return ;
	temp = table;
	while (i < data->num_philo)
	{
		if (temp->total_meal < data->num_meal)
			return ;
		temp = temp->next;
		i++;
	}
	data->stop = 1;
}

int	philo_control(t_thread *data)
{
	if (data->num_philo == 1)
	{
		printf("0 1 has taken a fork");
		printf("%d died\n", data->death_time);
		return (1);
	}
	return (0);
}
