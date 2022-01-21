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
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		custom_atoi(const char *str);
int		is_over(t_status *s);
void	*philo_life(void *p);
size_t	get_time(void);
int		is_over(t_status *s);
int		launch(t_status *stat, pthread_t *philos);
int		are_philos_full(t_status *stat);
int		are_philos_starved(t_status *stat);
int		is_starved_or_full(t_status *s);

#endif
