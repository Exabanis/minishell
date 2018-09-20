/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 12:53:47 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/13 12:54:15 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_env(void)
{
	t_env	*ptr;
	char	*str;

	ptr = g_envlst;
	while (ptr)
	{
		ft_putstr(ptr->name);
		ft_putchar('=');
		if (ptr->value != NULL)
		{
			str = ptr->value;
			while (*str)
			{
				if (*str != 34 && *str != 39)
					ft_putchar(*str);
				str++;
			}
		}
		ft_putchar('\n');
		ptr = ptr->next;
	}
	return (1);
}
