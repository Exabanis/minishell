/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_to.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 13:30:25 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 04:32:21 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		ft_go_to(char *str)
{
	t_env	*ptr;
	char	*s;

	ptr = g_envlst;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "HOME") == 0)
		{
			str = ft_strchr(str, '/');
			s = ft_strjoin(ptr->value, str);
			if (chdir(s) == 0)
				ft_setpwd();
			free(s);
			break ;
		}
		ptr = ptr->next;
	}
}
