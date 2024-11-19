/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:02:21 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/15 18:49:01 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	insert_to_philos(t_philo *philo)
{
	philo->time_to_die = philo->program->time_to_die;
	philo->time_to_eat = philo->program->time_to_eat;
	philo->time_to_sleep = philo->program->time_to_sleep;
	philo->cont = 0;
	philo->done_eat = 0;
	philo->left_fork = 0;
	philo->right_fork = 0;
}

void	insert_to_monitor(t_program *pro, int x)
{
	pro->philos[x].philo_id = x + 1;
	pro->philos[x].program = pro;
	pro->philos[x].last_meal = 0;
	pro->dead_flag = 0;
	pro->can_pick_up_fork = 1;
	pro->philos[x].done_eat = 0;
	pro->done_eat = 0;
	pro->start_time = (size_t)get_current_time();
}

int	ft_set_value_pro(char **str, t_program *pro, int argc)
{
	pro->num_philo = (int)ft_atoi(str[1]);
	pro->time_to_die = ft_atoi(str[2]);
	pro->time_to_eat = ft_atoi(str[3]);
	pro->time_to_sleep = ft_atoi(str[4]);
	if (argc == 6)
		pro->how_many_meals = (int)ft_atoi(str[5]);
	if (pro->num_philo <= 0 || (int)pro->time_to_die == -1
		|| (int)pro->time_to_eat == -1 || (int)pro->time_to_sleep == -1
		|| pro->how_many_meals == -1
		|| (pro->how_many_meals <= 0 && argc == 6))
		return (1);
	pro->philos = NULL;
	pro->fork = NULL;
	pro->philos = malloc(sizeof(t_philo) * pro->num_philo);
	pro->fork = malloc(sizeof(pthread_mutex_t) * pro->num_philo);
	if (!pro->philos || !pro->fork)
	{
		free(pro->philos);
		free(pro->fork);
		return (2);
	}
	return (0);
}

int	ft_set_mutex_forks(t_program *pro, int x)
{
	while (x < pro->num_philo)
	{
		if (pthread_mutex_init(&pro->fork[x], NULL) != 0)
		{
			x--;
			return (ft_destroy(pro, x, -1), 2);
		}
		x++;
	}
	return (0);
}

int	set_value(char **str, t_program *pro, int argc)
{
	int	x;

	x = 0;
	pro->check = ft_set_value_pro(str, pro, argc);
	if (pro->check)
		return (pro->check);
	if (ft_set_mutex_forks(pro, x) == 2)
		return (2);
	if (pthread_mutex_init(&pro->meal_lock, NULL) != 0)
		return (ft_destroy(pro, x, 0), 2);
	if (pthread_mutex_init(&pro->dead, NULL) != 0)
		return (ft_destroy(pro, x, 1), 2);
	if (pthread_mutex_init(&pro->write_, NULL) != 0)
		return (ft_destroy(pro, x, 2), 2);
	if (pthread_mutex_init(&pro->eat_lock, NULL))
		return (ft_destroy(pro, x, 3), 2);
	if (pthread_mutex_init(&pro->start_sem, NULL) != 0)
		return (ft_destroy(pro, x, 4), 2);
	x = -1;
	while (++x < pro->num_philo)
	{
		insert_to_monitor(pro, x);
		insert_to_philos(&(pro->philos[x]));
	}
	return (0);
}
