/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:55:02 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/04 18:02:47 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_done_eat(t_program *pro, t_philo *philo)
{
	philo->done_eat = 1;
	pthread_mutex_lock(&pro->eat_lock);
	pro->done_eat++;
	pthread_mutex_unlock(&pro->eat_lock);
}

void	ft_release_forks(t_program *pro, t_philo *philo)
{
	pthread_mutex_unlock(&pro->fork[philo->left_fork]);
	pthread_mutex_unlock(&pro->fork[philo->right_fork]);
}

void	ft_routing_loop(t_program *pro, t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&pro->dead);
		if (pro->dead_flag == 1)
		{
			pthread_mutex_unlock(&pro->dead);
			break ;
		}
		pthread_mutex_unlock(&pro->dead);
		pick_up_fork(pro, philo, philo->left_fork);
		if (pro->num_philo == 1)
			break ;
		pick_up_fork(pro, philo, philo->right_fork);
		eat(philo, pro);
		ft_release_forks(pro, philo);
		ft_time_sleep(philo, pro);
		think_philo(pro, philo);
		philo->cont++;
		if (philo->cont == pro->how_many_meals && pro->how_many_meals != 0)
		{
			ft_done_eat(pro, philo);
			break ;
		}
	}
}

void	*ft_routing(void *t)
{
	t_philo		*philo;
	t_program	*pro;

	philo = (t_philo *)t;
	pro = philo->program;
	pthread_mutex_lock(&pro->start_sem);
	pthread_mutex_unlock(&pro->start_sem);
	philo->left_fork = philo->philo_id - 1;
	philo->right_fork = philo->philo_id % pro->num_philo;
	if (philo->philo_id % 2 == 0)
	{
		if (philo->time_to_eat > philo->time_to_die)
			ft_usleep(philo->time_to_die / 2);
		else
			ft_usleep(philo->time_to_eat / 2);
	}
	ft_routing_loop(pro, philo);
	return (NULL);
}
