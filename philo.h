#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_status
{
	int				is_dead;

	int				max;
	int				number;
	int				time_to_die;
	int				eat_time;
	int				sleep_time;
	int				*forks;
	size_t			*last_meal_t;
	size_t			eat_limit;
	size_t			*eat_counts;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	act_mtx;
	pthread_mutex_t	talk_mtx;
}	t_status;

size_t	ft_strlen(const char *str);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int		custom_atoi(const char *str);
void	*philo_life(void *p);
void	error(void);
size_t	get_time(void);

#endif
