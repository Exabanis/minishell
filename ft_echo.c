/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:37:55 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 00:32:41 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_printdol(char **args)
{
	t_env	*ptr;
	char	*str;

	ptr = g_envlst;
	str = ft_strchr(args[1], '$');
	str++;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, str) == 0)
		{
			str = ptr->value;
			while (*str)
			{
				if (*str != 34 && *str != 39)
					ft_putchar(*str);
				str++;
			}
			ft_putchar('\n');
		}
		ptr = ptr->next;
	}
}

void		ft_cont(char **args, char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 1;
	while (args[++i])
	{
		s = ft_strjoin(str, " ");
		free(str);
		str = ft_strjoin(s, args[i]);
		free(s);
	}
	j = 0;
	while (str[j])
	{
		if (str[j] != 34 && str[j] != 39)
			ft_putchar(str[j]);
		j++;
	}
	free(str);
}

int			ft_echo(char **args)
{
	char	*str;

	if (args[1] == NULL)
		ft_putstr_fd("\033[31mExpected argument to \"echo\"\n\033[0m", 2);
	else
	{
		if (args[1][0] == '$')
			ft_printdol(args);
		else
		{
			str = ft_strdup(args[1]);
			ft_cont(args, str);
			ft_putchar('\n');
		}
	}
	return (1);
}
