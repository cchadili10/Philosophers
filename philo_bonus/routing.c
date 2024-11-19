/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:40:36 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/05 10:37:18 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_eat(sem_t *forks, t_philo *philo, t_program *monitor)
{
	philo->last_meal = get_current_time() - philo->program->start_time;
	sem_wait(monitor->write);
	printf("%zu %d is eating\n",
		(get_current_time() - monitor->start_time), philo->philo_id);
	sem_post(monitor->write);
	ft_usleep(monitor->time_to_eat);
	sem_post(forks);
	sem_post(forks);
}

void	ft_pick_up_fork(sem_t *forks, t_philo *philo, t_program *monitor)
{
	sem_wait(forks);
	sem_wait(monitor->write);
	printf("%zu %d has taken a fork\n",
		(get_current_time() - monitor->start_time), philo->philo_id);
	sem_post(monitor->write);
}

void	ft_sleep(t_philo *philo, t_program *monitor)
{
	sem_wait(monitor->write);
	printf("%zu %d is sleeping\n",
		(get_current_time() - monitor->start_time), philo->philo_id);
	sem_post(monitor->write);
	ft_usleep(monitor->time_to_sleep);
}

void	ft_routing(t_program *monitor, t_philo *philo, sem_t *forks)
{
	sem_wait(monitor->start_sem);
	sem_post(monitor->start_sem);
	if (philo->philo_id % 2 == 0)
		ft_usleep(monitor->time_to_eat);
	while (1)
	{
		ft_pick_up_fork(forks, philo, monitor);
		ft_pick_up_fork(forks, philo, monitor);
		ft_eat(forks, philo, monitor);
		ft_sleep(philo, monitor);
		sem_wait(monitor->write);
		printf("%zu %d is thinking\n",
			(get_current_time() - monitor->start_time), philo->philo_id);
		sem_post(monitor->write);
		philo->cont++;
		sem_wait(philo->program->var_sem);
		if (philo->cont == philo->how_many_meals && philo->how_many_meals != 0)
		{
			philo->done_eat = 1;
			sem_post(philo->program->var_sem);
			break ;
		}
		sem_post(philo->program->var_sem);
	}
}
