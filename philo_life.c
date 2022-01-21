#include "philo.h"

void	timer(unsigned long time)
{
	size_t	ini;

	if (time == 0)
		return ;
	ini = get_time();
	while (1)
	{
		if (get_time() - ini >= time)
			return ;
		usleep(100);
	}
}

void	action(char *message, t_status *stat, int code_number, int time)
{
	pthread_mutex_lock(&stat->talk_mtx);
	printf("%zu ", get_time());
	if (!ft_strncmp("fork", message, ft_strlen(message)))
	{
		printf("%d has taken a fork\n", code_number + 1);
		printf("%zu ", get_time());
		printf("%d has taken a fork\n", code_number + 1);
	}
	if (!ft_strncmp("eat", message, ft_strlen(message)))
	{
		printf("%d is eating\n", code_number + 1);
		stat->last_meal_t[code_number] = get_time();
	}
	if (!ft_strncmp("sleep", message, ft_strlen(message)))
	{
		printf("%d is sleeping\n", code_number + 1);
	}
	if (!ft_strncmp("think", message, ft_strlen(message)))
		printf("%d is thinking\n", code_number + 1);
	pthread_mutex_unlock(&stat->talk_mtx);
	timer(time);
}

int	fork_cnt(int fork_number, int max_number)
{
	if (fork_number == max_number)
		fork_number = 0;
	return (fork_number);
}

void	take_a_fork(t_status *s, int c)
{
	while (1)
	{
		if (is_over(s))
			return ;
		if (s->forks[fork_cnt(c, s->max)] && s->forks[fork_cnt(c + 1, s->max)])
		{
			pthread_mutex_lock(&s->fork_mutex[fork_cnt(c, s->max)]);
			pthread_mutex_lock(&s->fork_mutex[fork_cnt(c + 1, s->max)]);
			s->forks[fork_cnt(c, s->max)] = 0;
			s->forks[fork_cnt(c + 1, s->max)] = 0;
			action("fork", s, c, 0);
			action("eat", s, c, s->eat_time);
			if (s->is_dead)
				return ;
			(s->eat_counts[c])++;
			s->forks[fork_cnt(c, s->max)] = 1;
			s->forks[fork_cnt(c + 1, s->max)] = 1;
			pthread_mutex_unlock(&s->fork_mutex[fork_cnt(c, s->max)]);
			pthread_mutex_unlock(&s->fork_mutex[fork_cnt(c + 1, s->max)]);
			return ;
		}
		usleep(100);
	}
}

void	*philo_life(void *p)
{
	int			code_number;
	t_status	*stat;

	stat = p;
	stat->number -= 1;
	code_number = stat->number;
	stat->last_meal_t[code_number] = get_time();
	while (1)
	{
		take_a_fork(stat, code_number);
		action("sleep", stat, code_number, stat->sleep_time);
		if (is_over(stat))
			return (NULL);
		action("think", stat, code_number, 0);
	}
	return (NULL);
}
