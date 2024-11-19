/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:43:40 by hchadili          #+#    #+#             */
/*   Updated: 2024/10/16 10:31:52 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*ft_monitor(void *ptr)
{
	t_philo	*philo;
	size_t	cur_time;

	philo = (t_philo *)ptr;
	while (1)
	{
		sem_wait(philo->program->var_sem);
		cur_time = get_current_time() - philo->start_time;
		if ((size_t)philo->time_to_die <= (cur_time) - philo->last_meal
			&& philo->done_eat == 0)
		{
			sem_post(philo->program->var_sem);
			sem_wait(philo->program->write);
			printf("%zu %d died\n", cur_time, philo->philo_id);
			exit(42);
		}
		if (philo->done_eat == 1)
		{
			sem_post(philo->program->var_sem);
			exit(1);
		}
		sem_post(philo->program->var_sem);
		usleep(500);
	}
}
