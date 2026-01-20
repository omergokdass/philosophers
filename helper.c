/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokdas <ogokdas@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:29:31 by ogokdas           #+#    #+#             */
/*   Updated: 2026/01/20 18:44:41 by ogokdas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			return -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = (10 * result) + (nptr[i] - '0');
		if (result > 2147483647)
            return (-1);
		i++;
	}
	if (!(nptr[i] >= '0' && nptr[i] <= '9') && nptr[i] != '\0')
		return -1;

	return result;
}

int parse(int ac, char **av)
{
    int i;
    int value;

    if (ac != 5 && ac != 6)
        return (printf("Error\n"), 1);

    i = 1;
	if(ft_atoi(av[1]) == 1)
		return 1;
    while (i < ac)
    {
        value = ft_atoi(av[i]);
        if (value <= 0)
            return (printf("Error\n"), 1);
        i++;
    }
    return (0);
}
