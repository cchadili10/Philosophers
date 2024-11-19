/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:34:55 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/14 23:09:04 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_clear_sema(sem_t *forks, t_program *monitor)
{
	sem_close(forks);
	sem_close(monitor->write);
	sem_close(monitor->var_sem);
	sem_close(monitor->start_sem);
	sem_unlink("/fork");
	sem_unlink("/start_sem");
	sem_unlink("/write");
	sem_unlink("/var_sem");
}

void	ft_set_value_for_pholo(t_program	*monitor, int i)
{
	monitor->philos[i].program = monitor;
	monitor->philos[i].philo_id = i + 1;
	monitor->philos[i].time_to_die = monitor->time_to_die;
	monitor->philos[i].time_to_eat = monitor->time_to_eat;
	monitor->philos[i].time_to_sleep = monitor->time_to_sleep;
	monitor->philos[i].how_many_meals = monitor->how_many_meals;
	monitor->philos[i].cont = 0;
	monitor->philos[i].start_time = monitor->start_time;
	monitor->philos[i].done_eat = 0;
}

void	ft_set_value_for_monitor_v2(t_program *monitor)
{
	monitor->dead_flag = 0;
	monitor->done_eat = 0;
	monitor->can_pick_up_fork = 0;
	monitor->status = 0;
	monitor->cont = 0;
	monitor->philos = malloc(sizeof(t_philo) * monitor->num_philo);
	if (!monitor->philos)
	{
		ft_print_error("malloc fail\n");
		exit(1);
	}
}

void	ft_set_value_for_monitor(t_program	*monitor,
	const char **argv, int argc, sem_t *forks)
{
	ft_clear_sema(forks, monitor);
	monitor->write = NULL;
	monitor->var_sem = NULL;
	monitor->how_many_meals = 0;
	monitor->num_philo = (int)ft_atoi(argv[1]);
	monitor->time_to_die = ft_atoi(argv[2]);
	monitor->time_to_eat = ft_atoi(argv[3]);
	monitor->time_to_sleep = ft_atoi(argv[4]);
	monitor->start_time = get_current_time();
	if (argc == 6)
		monitor->how_many_meals = (int)ft_atoi(argv[5]);
	if (monitor->num_philo <= 0 || (int)monitor->time_to_die == -1
		|| (int)monitor->time_to_eat == -1 || (int)monitor->time_to_sleep == -1
		|| (monitor->how_many_meals <= 0 && argc == 6)
		|| monitor->how_many_meals == -1)
	{
		ft_print_error("put valid argmunt\n");
		exit(2);
	}
	ft_set_value_for_monitor_v2(monitor);
}
