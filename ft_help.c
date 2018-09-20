/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:09:48 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 03:43:10 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_help(void)
{
	ft_putendl("\033[33menv\033[32m: to show the environment list.");
	ft_putstr("\033[33msetenv [NAME] [value]\033[32m: to add [NAME] to");
	ft_putendl("environment list.");
	ft_putstr("\033[33munsetenv [NAME]\033[32m: to remove [NAME] from");
	ft_putendl("environment list.");
	ft_putendl("\033[33mls\033[32m: to list files in a directory.");
	ft_putendl("\033[33mpwd\033[32m: to print current working directory.");
	ft_putendl("\033[33mexit\033[32m: to exit the minishell.");
	ft_putendl("\033[33mcd [path]\033[32m: to change directory.\033[0m");
	return (1);
}
