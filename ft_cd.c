/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:03:16 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/14 21:01:13 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_goback(void)
{
	t_env	*ptr;

	ptr = g_envlst;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "OLDPWD") == 0)
		{
			if (chdir(ptr->value) == 0)
				ft_setpwd();
			break ;
		}
		ptr = ptr->next;
	}
}

void		ft_setpwd(void)
{
	t_env	*ptr;
	char	cwd[g_utils->buf_s];

	ptr = g_envlst;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "PWD") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				ft_strdel(&(ptr->value));
				ptr->value = ft_strdup(cwd);
			}
			break ;
		}
		ptr = ptr->next;
	}
}

void		ft_gohome(void)
{
	t_env	*ptr;

	ptr = g_envlst;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "HOME") == 0)
		{
			if (chdir(ptr->value) == 0)
				ft_setpwd();
			break ;
		}
		ptr = ptr->next;
	}
}

void		ft_setoldpwd(void)
{
	t_env	*ptr;
	char	cwd[g_utils->buf_s];

	ptr = g_envlst;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "OLDPWD") == 0)
		{
			if (getcwd(cwd, sizeof(cwd)) != NULL)
			{
				ft_strdel(&(ptr->value));
				ptr->value = ft_strdup(cwd);
			}
			break ;
		}
		ptr = ptr->next;
	}
}

int			ft_cd(char **args)
{
	if (args[1] == NULL)
	{
		ft_setoldpwd();
		ft_gohome();
	}
	else
	{
		if (ft_strcmp(args[1], "-") != 0 && args[2] != NULL)
			ft_setoldpwd();
		if (chdir(args[1]) == 0)
			ft_setpwd();
		else if (ft_strcmp(args[1], "--") == 0)
			ft_gohome();
		else if (ft_strcmp(args[1], "-") == 0)
			ft_goback();
		else if (args[1][0] == '~')
			ft_go_to(args[1]);
		else
		{
			ft_putstr("\033[34m");
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd("\033[31m: No such directory\n\033[0m", 2);
		}
	}
	return (1);
}
