/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:17:53 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/07 19:31:48 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	eat(t_philo *philo, t_program *pro)
{
	size_t	curt_time;

	pthread_mutex_lock(&philo->program->meal_lock);
	pthread_mutex_lock(&pro->write_);
	pthread_mutex_lock(&pro->dead);
	if (pro->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->program->meal_lock);
		pthread_mutex_unlock(&pro->write_);
		pthread_mutex_unlock(&pro->dead);
		return ;
	}
	curt_time = get_current_time() - philo->program->start_time;
	philo->last_meal = curt_time;
	printf("%zu %d is eating\n", curt_time, philo->philo_id);
	pthread_mutex_unlock(&philo->program->meal_lock);
	pthread_mutex_unlock(&pro->write_);
	pthread_mutex_unlock(&pro->dead);
	if (philo->time_to_eat > philo->time_to_die)
		ft_usleep(philo->time_to_die);
	else
		ft_usleep(philo->time_to_eat);
}

void	ft_time_sleep(t_philo *philo, t_program *pro)
{
	pthread_mutex_lock(&pro->write_);
	pthread_mutex_lock(&pro->dead);
	if (pro->dead_flag == 1)
	{
		pthread_mutex_unlock(&pro->write_);
		pthread_mutex_unlock(&pro->dead);
		return ;
	}
	printf("%zu %d is sleeping\n",
		(get_current_time() - philo->program->start_time), philo->philo_id);
	pthread_mutex_unlock(&pro->write_);
	pthread_mutex_unlock(&pro->dead);
	if (philo->time_to_sleep > philo->time_to_die)
		ft_usleep(philo->time_to_die);
	else
		ft_usleep(philo->time_to_sleep);
}

void	think_philo(t_program *pro, t_philo *philo)
{
	pthread_mutex_lock(&pro->write_);
	pthread_mutex_lock(&pro->dead);
	if (pro->dead_flag == 1)
	{
		pthread_mutex_unlock(&pro->write_);
		pthread_mutex_unlock(&pro->dead);
		return ;
	}
	printf("%zu %d is thinking\n",
		(get_current_time() - pro->start_time), philo->philo_id);
	pthread_mutex_unlock(&pro->write_);
	pthread_mutex_unlock(&pro->dead);
}

void	pick_up_fork(t_program *pro, t_philo *philo, int fork)
{
	pthread_mutex_lock(&pro->fork[fork]);
	pthread_mutex_lock(&pro->write_);
	pthread_mutex_lock(&pro->dead);
	if (!pro->can_pick_up_fork)
	{
		pthread_mutex_unlock(&pro->fork[fork]);
		pthread_mutex_unlock(&pro->write_);
		pthread_mutex_unlock(&pro->dead);
		return ;
	}
	printf("%zu %d has taken a fork\n",
		(get_current_time() - pro->start_time), philo->philo_id);
	pthread_mutex_unlock(&pro->dead);
	pthread_mutex_unlock(&pro->write_);
	if (pro->num_philo == 1)
		pthread_mutex_unlock(&pro->fork[fork]);
}
