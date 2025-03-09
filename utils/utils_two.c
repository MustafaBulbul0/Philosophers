#include "../philo.h"

static void edit_meal_time(t_philo_table **temp, t_thread *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		if ((*temp)->num == 0 || (*temp)->num == 1)
			(*temp)->meal_time++;
		(*temp) = (*temp)->next;
		i++;
	}
}

static void	who_hungry(t_philo_table **temp, t_thread *data)
{
	int 			i;
	int				j;
	int				p_info[2];

	j = 0;
	while (j != (data->philo_num) / 2)
	{
		p_info[1] = __INT_MAX__;
		i = 0;
		while (i < data->philo_num)
		{
			if (((*temp)->meal_time < p_info[1]) && (*temp)->num == 0 && (*temp)->next->num == 0)
			{
				(*temp)->before_num = (*temp)->num;
				(*temp)->num = 2;
				(*temp)->next->before_num = (*temp)->next->num;
				(*temp)->next->num = 1;
				p_info[0] = (*temp)->philo_num;
				p_info[1] = (*temp)->meal_time;
				j++;
			}
			(*temp) = (*temp)->next;
			i++;
		}
	}
}

void	who_do_what(t_philo_table **table, t_thread *data)
{
	t_philo_table	**temp;

	temp = table;
	who_hungry(temp, data);
	edit_meal_time(temp, data);

	for (int i = 0; i < 6 ; i++)
	{
		printf("%d %d %d %d \n", (*table)->philo_num, (*table)->num, (*table)->before_num, (*table)->meal_time);
		(*table) = (*table)->next;
	}
}
