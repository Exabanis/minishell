/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 15:03:25 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 03:57:32 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char			**ft_expath(void)
{
	t_env		*temp;
	char		**g_expath;

	temp = g_envlst;
	g_expath = NULL;
	while (temp)
	{
		if (ft_strcmp(temp->name, "PATH") == 0)
		{
			g_expath = ft_strsplit(temp->value, ':');
			break ;
		}
		temp = temp->next;
	}
	return (g_expath);
}

char			*ft_continue(char *ex_path, char **g_expath)
{
	char		*ptr;
	int			i;
	struct stat	buf;

	i = -1;
	while (g_expath[++i])
	{
		ptr = ft_strjoin(g_expath[i], ex_path);
		if (access(ptr, F_OK) == 0)
		{
			stat(ptr, &buf);
			if ((buf.st_mode & S_IXUSR) == 0)
				ft_putstr_fd("\033[31mCould not execute. Permission denied\n\
						\033[0m", 2);
			i = -1;
			while (g_expath[++i] != NULL)
				ft_strdel(&g_expath[i]);
			free(g_expath);
			free(ex_path);
			return (ptr);
		}
		free(ptr);
	}
	return (NULL);
}

char			*ft_cmd(char *str)
{
	int			i;
	char		*ex_path;
	char		**g_expath;
	char		*ptr;

	i = -1;
	g_expath = ft_expath();
	if (g_expath == NULL)
		return (NULL);
	if (*str == '/')
		str = ft_strrchr(str, '/');
	ex_path = ft_strjoin("/", str);
	if ((ptr = ft_continue(ex_path, g_expath)) != NULL)
		return (ptr);
	while (g_expath[++i] != NULL)
		ft_strdel(&g_expath[i]);
	free(g_expath);
	free(ex_path);
	return (NULL);
}
