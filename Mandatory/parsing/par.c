/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchadili <hchadili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 08:13:04 by hchadili          #+#    #+#             */
/*   Updated: 2024/04/09 03:49:27 by hchadili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int is_num(char *s)
{
    int x;
    
    x = 0;
    if ((s[x] != '+') && (s[x] < 48 || s[x] > 57))
        return (1);
    x++;
    while (s[x])
    {
        if (s[x] < 48 || s[x] > 57)
            return (1);
        x++;
    }
    return (0);
}