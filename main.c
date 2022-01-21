#include "philo.h"

int	init_count(t_status *stat, int argc, char **argv)
{
	stat->is_dead = 0;

	stat->max = custom_atoi(argv[1]);
	if (stat->max == 0)
		return (1);
	stat->number = custom_atoi(argv[1]);
	if (stat->number == 0)
		return (1);
	stat->time_to_die = custom_atoi(argv[2]);
	if (stat->time_to_die == 0)
		return (1);
	stat->last_meal_t = (size_t *)malloc(sizeof(size_t) * stat->max);
	if (!stat->last_meal_t)
		return (1);
	stat->eat_time = custom_atoi(argv[3]);
	if (stat->eat_time == 0)
		return (1);
	stat->sleep_time = custom_atoi(argv[4]);
	if (stat->sleep_time == 0)
		return (1);
	if (argc == 6)
	{
		stat->eat_limit = custom_atoi(argv[5]);
		if (stat->eat_limit == 0)
			return (1);
	}
	else
		stat->eat_limit = 0;
	return (0);
}

int	init_status(t_status *stat, int argc, char **argv)
{
	size_t	norm_esc;
	int		i;

	if (init_count(stat, argc, argv))
		return (1);
	stat->eat_counts = (size_t *)malloc(sizeof(size_t) * (stat->max + 1));
	if (!stat->eat_counts)
		return (1);
	stat->forks = (int *)malloc(sizeof(int) * (stat->max + 1));
	if (!stat->forks)
		return (1);
	norm_esc = sizeof(pthread_mutex_t) * stat->max;
	stat->fork_mutex = (pthread_mutex_t *)malloc(norm_esc);
	if (!stat->fork_mutex)
		return (1);
	i = 0;
	while (i < stat->max)
	{
		stat->eat_counts[i] = 0;
		stat->forks[i] = 1;
		pthread_mutex_init(&stat->fork_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&stat->talk_mtx, NULL);
	return (0);
}

int	are_philos_full(t_status *stat)
{
	int	i;

	if (stat->eat_limit == 0)
		return (0);
	i = 0;
	while (i < stat->max)
	{
		if (stat->eat_counts[i] < stat->eat_limit)
			return (0);
		i++;
	}
	return (1);
}

int	are_philos_starved(t_status *stat)
{
	size_t	now;
	int		i;

	i = 0;
	now = get_time();
	while (i < stat->max)
	{
		if (stat->last_meal_t[i] + stat->time_to_die <= now)
		{
			printf("%zu ", get_time());
			printf("%d died\n", i + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_status	stat;
	pthread_t	*philos;
	int			i;
	if (argc != 5 && argc != 6)
	{
		error();
		return (0);
	}
	if (init_status(&stat, argc, argv))
	{
		error();
		return (0);
	}

	philos = (pthread_t *)malloc(sizeof(pthread_t) * stat.max);
	if (!philos)
		return (1);
	i = 0;
	while (i < stat.max)
	{
		if (pthread_create(&philos[i], NULL, &philo_life, &stat))
		{
			error();
			return (0);
		}
		pthread_detach(philos[i]);
		usleep(500);
		i++;
	}
	while (1)
	{
		if (are_philos_starved(&stat) || are_philos_full(&stat))
		{
			stat.is_dead = 1;
			usleep(500);
			return (0);
		}
	}
}
