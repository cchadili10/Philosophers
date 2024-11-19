/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:08:21 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/11 19:39:57 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_kill_pro(t_program *monitor, int i)
{
	ft_print_error("fork error");
	while (i--)
		kill(monitor->philos[i].proc, SIGKILL);
	free(monitor->philos);
}

void	ft_creat_philos(t_program *monitor, sem_t *forks)
{
	int	i;

	i = -1;
	sem_wait(monitor->start_sem);
	while (++i < monitor->num_philo)
	{
		monitor->philos[i].proc = fork();
		if (monitor->philos[i].proc == -1)
		{
			ft_kill_pro(monitor, i);
			exit(1);
		}
		else if (monitor->philos[i].proc == 0)
		{
			ft_set_value_for_pholo(monitor, i);
			pthread_create(&monitor->prog, NULL,
				ft_monitor, &monitor->philos[i]);
			pthread_detach(monitor->prog);
			ft_routing(monitor, &monitor->philos[i], forks);
			exit(1);
		}
	}
	sem_post(monitor->start_sem);
}

void	ft_wait_for_philo(t_program	*monitor)
{
	int	i;

	i = -1;
	while (waitpid(-1, &monitor->status, 0))
	{
		if (WIFEXITED(monitor->status) && WEXITSTATUS(monitor->status) == 42)
		{
			while (++i < monitor->num_philo)
				kill(monitor->philos[i].proc, SIGKILL);
			break ;
		}
		if (WIFEXITED(monitor->status) && WEXITSTATUS(monitor->status) == 1)
		{
			monitor->cont++;
			if (monitor->cont == monitor->num_philo)
				break ;
		}
	}
}
