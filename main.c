/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 07:56:49 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 03:44:27 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env		*g_envlst;
t_util		*g_utils;

char		*ft_realloc(char *str)
{
	char	*buf;

	g_utils->buf_s += g_utils->buf_s;
	buf = ft_strnew(g_utils->buf_s);
	if (!buf)
	{
		ft_putstr_fd("\033[31mAllocation error\n\033[0m", 2);
		exit(1);
	}
	buf = ft_strcpy(buf, str);
	free(str);
	return (buf);
}

char		ft_getchar(void)
{
	char	buf[1];

	if (read(0, buf, 1) < 0)
		write(2, &buf, 1);
	return (buf[0]);
}

char		*get_next_line(void)
{
	int		i;
	char	*buf;
	int		c;

	i = 0;
	buf = ft_strnew(g_utils->buf_s);
	if (!buf)
	{
		ft_putstr_fd("\033[31mAllocation error\n\033[0m", 2);
		exit(1);
	}
	while (1)
	{
		c = ft_getchar();
		if (c == '\t' || c == '\a' || c == '\r')
			c = ' ';
		g_utils->col = (c == ';') ? 1 : 0;
		if (c == '\n' || c == ';')
			return (buf);
		else
			buf[i] = c;
		i++;
		if (i >= g_utils->buf_s)
			buf = ft_realloc(buf);
	}
}

void		ft_prompt(void)
{
	char	*line;
	char	**args;
	int		status;
	int		i;

	status = 1;
	while (status)
	{
		if (g_utils->sig && g_utils->col == 0)
			ft_putstr("\033[32m$> \033[0m");
		g_utils->col = 0;
		line = get_next_line();
		g_utils->sig = 1;
		if (g_utils->sig)
		{
			i = -1;
			args = ft_strsplit(line, ' ');
			status = ft_execute(args);
			while (args[++i] != NULL)
				ft_strdel(&args[i]);
			free(args);
		}
		free(line);
	}
}

int			main(int ac, char **av, char **envp)
{
	t_env		*temp;
	t_env		*ptr;

	g_envlst = ft_get_env(envp);
	g_utils = (t_util *)malloc(sizeof(t_util));
	g_utils->buf_s = 1024;
	g_utils->env = envp;
	g_utils->sig = 1;
	g_utils->col = 0;
	signal(SIGINT, ft_sig_handler);
	if (ac > 0 && av != NULL)
		ft_prompt();
	ptr = g_envlst;
	while (ptr)
	{
		temp = ptr;
		ptr = ptr->next;
		free(temp->name);
		free(temp->value);
		free(temp);
	}
	return (1);
}
