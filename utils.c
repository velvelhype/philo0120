#include "philo.h"

void	error(void)
{
	write(1, "error\n", 7);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned int	b;

	i = 0;
	b = n - 1;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i != b)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
		{
			return (0);
		}
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	custom_atoi(const char *str)
{
	unsigned long	i;
	unsigned long	sum;

	sum = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		sum = (sum * 10) + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (0);
	return (sum);
}

size_t	get_time(void)
{
	struct timeval	times;

	gettimeofday(&times, NULL);
	return ((times.tv_sec * 1000) + (times.tv_usec / 1000));
}
