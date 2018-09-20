/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:54:36 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/13 12:58:40 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_addenv(t_env *ptr, char **args)
{
	ptr->next = (t_env*)malloc(sizeof(t_env));
	ptr->next->name = ft_strnew(ft_strlen(args[1]));
	ptr->next->name = ft_strcpy(ptr->next->name, args[1]);
	if (args[2] != NULL)
	{
		ptr->next->value = ft_strnew(ft_strlen(args[2]));
		ptr->next->value = ft_strcpy(ptr->next->value, args[2]);
		ptr->next->next = NULL;
	}
}

int			ft_changenv(t_env *ptr, char **args)
{
	if (args[2] == NULL)
		ft_strdel(&(ptr->value));
	else
	{
		ft_strdel(&(ptr->value));
		ptr->value = ft_strnew(ft_strlen(args[2]));
		ptr->value = ft_strcpy(ptr->value, args[2]);
	}
	return (1);
}

int			ft_setenv(char **args)
{
	t_env	*ptr;
	int		flag;

	flag = 0;
	ptr = g_envlst;
	if (args[1] == NULL)
		ft_putstr_fd("\033[31mExpected argument to \"setenv\"\n\033[0m", 2);
	else
	{
		while (ptr)
		{
			if (ft_strcmp(ptr->name, args[1]) == 0)
			{
				flag = ft_changenv(ptr, args);
				break ;
			}
			if (ptr->next != NULL)
				ptr = ptr->next;
			else
				break ;
		}
		if (ptr->next == NULL && flag == 0)
			ft_addenv(ptr, args);
	}
	return (1);
}
