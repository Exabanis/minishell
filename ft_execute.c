/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 11:05:07 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 10:09:56 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*g_array[] = {"cd", "echo", "env", "help", "setenv", "unsetenv"};

void		ft_exec(char **args)
{
	char	*path;

	path = NULL;
	if (args[0][0] == '/')
		execve(args[0], args, g_utils->env);
	else if ((path = ft_cmd(args[0])) != NULL)
		execve(path, args, g_utils->env);
	else
	{
		ft_putstr("\033[33m");
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\033[31m: command not found\n\033[0m", 2);
	}
}

int			ft_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		ft_exec(args);
		exit(1);
	}
	else if (pid < 0)
		ft_putstr_fd("\033[31mCommand error\n\033[0m", 2);
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status) && !wpid)
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

int			ft_builtin_func(char **args, char *argv)
{
	t_env	*ptr;

	ptr = g_envlst;
	if (ft_strcmp(argv, "cd") == 0)
		return (ft_cd(args));
	if (ft_strcmp(argv, "echo") == 0)
		return (ft_echo(args));
	if (ft_strcmp(argv, "env") == 0)
		return (ft_env());
	if (ft_strcmp(argv, "help") == 0)
		return (ft_help());
	if (ft_strcmp(argv, "setenv") == 0)
		return (ft_setenv(args));
	if (ft_strcmp(argv, "unsetenv") == 0)
		return (ft_unsetenv(args, ptr));
	return (0);
}

int			ft_execute(char **args)
{
	int		i;
	char	*str;

	i = -1;
	if (args[0] == NULL)
		return (1);
	str = args[0];
	if (*str == '/')
	{
		str = ft_strrchr(str, '/');
		str++;
	}
	while (++i < 6)
	{
		if (ft_strcmp(str, "exit") == 0)
			return (0);
		else if (ft_strcmp(str, g_array[i]) == 0)
			return (ft_builtin_func(args, g_array[i]));
	}
	return (ft_launch(args));
}
