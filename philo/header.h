/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 19:39:18 by hchadili          #+#    #+#             */
/*   Updated: 2024/11/15 19:03:33 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_program	t_program;
typedef struct s_philo		t_philo;

struct s_philo
{
	pthread_t			thread;
	size_t				last_meal;
	int					philo_id;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					how_many_meals;
	int					cont;
	int					done_eat;
	int					left_fork;
	int					right_fork;
	struct s_program	*program;
};

struct s_program
{
	pthread_t		prog;
	pthread_mutex_t	*fork;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_;
	pthread_mutex_t	start_sem;
	int				can_pick_up_fork;
	int				dead_flag;
	size_t			start_time;
	int				how_many_meals;
	int				num_philo;
	int				check;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				done_eat;
	struct s_philo	*philos;
};

size_t	get_current_time(void);
size_t	ft_atoi(const char *str);
int		ft_usleep(size_t milliseconds);
int		set_value(char **str, t_program *pro, int argc);
void	*ft_monitor(void *t);
void	*ft_routing(void *t);
void	eat(t_philo *philo, t_program *pro);
void	ft_time_sleep(t_philo *philo, t_program *pro);
void	think_philo(t_program *pro, t_philo *philo);
void	pick_up_fork(t_program *pro, t_philo *philo, int fork);
int		check_for_error(char const **str, int argc);
void	ft_destroy(t_program *pro, int x, int check);
void	ft_print_error(char *str);
#endif

// -lpthread