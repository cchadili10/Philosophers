/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:01:43 by hchadili          #+#    #+#             */
/*   Updated: 2024/10/16 13:51:38 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_monitor_check_philo(t_program *pro, int x)
{
	pthread_mutex_lock(&pro->write_);
	printf("%zu %d died\n",
		(get_current_time() - pro->start_time), pro->philos[x].philo_id);
	pthread_mutex_unlock(&pro->write_);
	pthread_mutex_lock(&pro->dead);
	(1) && (pro->dead_flag = 1, pro->can_pick_up_fork = 0);
	pthread_mutex_unlock(&pro->dead);
	pthread_mutex_unlock(&pro->meal_lock);
}

void	ft_monitor_check_loop(t_program *pro, t_philo *philo, int x)
{
	while (++x < pro->num_philo)
	{
		pthread_mutex_lock(&pro->meal_lock);
		if (((get_current_time() - pro->start_time) - pro->philos[x].last_meal
				>= (size_t)pro->time_to_die) && philo[x].done_eat == 0)
		{
			ft_monitor_check_philo(pro, x);
			break ;
		}
		pthread_mutex_unlock(&pro->meal_lock);
	}
}

void	ft_monitor_loop(t_program *pro, t_philo *philo, int x)
{
	while (1)
	{
		x = -1;
		ft_monitor_check_loop(pro, philo, x);
		pthread_mutex_lock(&pro->eat_lock);
		if (pro->done_eat == pro->num_philo)
			break ;
		pthread_mutex_unlock(&pro->eat_lock);
		pthread_mutex_lock(&pro->dead);
		if (pro->dead_flag == 1)
		{
			pthread_mutex_unlock(&pro->dead);
			break ;
		}
		pthread_mutex_unlock(&pro->dead);
	}
}

void	*ft_monitor(void *t)
{
	t_program	*pro;
	t_philo		*philo;
	int			x;

	pro = (t_program *)t;
	philo = pro->philos;
	x = -1;
	ft_monitor_loop(pro, philo, x);
	return (NULL);
}
