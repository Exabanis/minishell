/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:17:51 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 10:13:57 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_ssh(char **args)
{
	t_env	*ptr;

	ptr = g_envlst;
	if (ft_strcmp(ptr->name, args[1]) == 0)
	{
		g_envlst = g_envlst->next;
		free(ptr);
		return (1);
	}
	return (0);
}

int			ft_unsetenv(char **args, t_env *ptr)
{
	t_env	*del;

	if (ft_ssh(args) == 1)
		return (1);
	while (ptr)
	{
		if (ft_strcmp(ptr->next->name, args[1]) == 0)
		{
			del = ptr->next;
			if (ptr->next->next != NULL)
				ptr->next = ptr->next->next;
			else
				ptr->next = NULL;
			free(del->name);
			free(del->value);
			free(del);
			break ;
		}
		if (ptr->next->next != NULL)
			ptr = ptr->next;
		else
			break ;
	}
	return (1);
}
