/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:10:05 by shuwang           #+#    #+#             */
/*   Updated: 2024/10/02 17:10:09 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	args_error(int ac, char **av)
{
	(void) av;
	if (ac > 1)
	{
		ft_err(ERR_PREF "More than one argument is given\n");
		exit (EXIT_FAILURE);
	}
	return (0);
}

int	main(int ac, char **av)
{
	args_error(ac, av);
	signals();
	minishell_loop();

	return (0);
}