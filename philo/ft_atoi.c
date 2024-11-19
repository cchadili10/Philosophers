/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 13:58:54 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/15 18:58:38 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

size_t	ft_atoi(const char *str)
{
	size_t				x;
	__int128_t			res;

	x = 0;
	res = 0;
	if (str[x] == '+')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		res = res * 10 + str[x++] - 48;
		if (res > SIZE_T_MAX)
			return (-1);
	}
	return (res);
}

void	ft_destroy(t_program *pro, int x, int check)
{
	while (x >= 0)
		pthread_mutex_destroy(&pro->fork[x--]);
	if (check == 1)
		pthread_mutex_destroy(&pro->meal_lock);
	if (check == 2)
	{
		pthread_mutex_destroy(&pro->meal_lock);
		pthread_mutex_destroy(&pro->dead);
	}
	if (check == 3)
	{
		pthread_mutex_destroy(&pro->meal_lock);
		pthread_mutex_destroy(&pro->dead);
		pthread_mutex_destroy(&pro->write_);
	}
	if (check == 4)
	{
		pthread_mutex_destroy(&pro->meal_lock);
		pthread_mutex_destroy(&pro->dead);
		pthread_mutex_destroy(&pro->write_);
		pthread_mutex_destroy(&pro->eat_lock);
	}
}
