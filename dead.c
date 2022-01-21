#include "philo.h"

int	is_over(t_status *s)
{
	if (s->is_dead)
	{
		usleep(1000);
		return (1);
	}
	return (0);
}

int	launch(t_status *stat, pthread_t *philos)
{
	int	i;

	i = 0;
	while (i < stat->max)
	{
		if (pthread_create(&philos[i], NULL, &philo_life, stat))
		{
			write(1, "error\n", 7);
			return (1);
		}
		pthread_detach(philos[i]);
		usleep(500);
		i++;
	}
	return (0);
}

int	is_starved_or_full(t_status *s)
{
	if (are_philos_starved(s) || are_philos_full(s))
	{
		s->is_dead = 1;
		usleep(500);
		return (1);
	}
	return (0);
}
