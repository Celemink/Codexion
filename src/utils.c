/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lodazzan <lodazzan@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 13:17:40 by lodazzan          #+#    #+#             */
/*   Updated: 2026/08/11 12:57:54 by lodazzan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ft_atol(const char *str)
{
	int		i;
	int		sign;
	long	n;

	i = 0;
	n = 0;
	sign = 1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (((str[i] == '-') || (str[i] == '+')) && (str[i + 1] != 0))
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') || (n > INT_MAX || n < INT_MIN))
			return (LONG_MAX);
		n = (n * 10) + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	is_coder_burned_out(t_coder *coder)
{
	int	result;

	pthread_mutex_lock(&coder->state_mutex);
	result = coder->burned_out;
	pthread_mutex_unlock(&coder->state_mutex);
	return (result);
}

void	set_coder_burned_out(t_coder *coder)
{
	pthread_mutex_lock(&coder->state_mutex);
	coder->burned_out = 1;
	pthread_mutex_unlock(&coder->state_mutex);
}
