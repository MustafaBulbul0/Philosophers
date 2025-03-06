#include "../philo.h"

static void	free_thread(t_thread *thread);

void	shut_prgram_err(t_thread *thread, t_data *data)
{
	if (data)
		free(data);
	if (thread)
		free_thread(thread);
	exit(EXIT_FAILURE);
}

void	shut_prgram_scc(t_thread *thread, t_data *data)
{
	if (data)
		free(data);
	if (thread)
		free_thread(thread);
	exit (EXIT_SUCCESS);
}

static void	clear_2d_pointer(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

static void	free_thread(t_thread *thread)
{
	clear_2d_pointer((char **)thread->ret_val);
	free(thread->mutex);
	free(thread);
}
