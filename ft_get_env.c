/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 08:06:03 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/13 13:19:11 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_env		*ft_create_env(char *str)
{
	size_t	i;
	t_env	*ret;

	i = 0;
	ret = (t_env *)malloc(sizeof(t_env));
	while (str[i] != '\0' && str[i] != '=')
		i++;
	ret->name = ft_strnew(i);
	ret->name = ft_strncpy(ret->name, str, i);
	if (str[++i] != '\0')
	{
		str += i;
		i = 0;
		while (str[i] != '\0')
			i++;
		ret->value = ft_strnew(i);
		ret->value = ft_strncpy(ret->value, str, i);
	}
	else
		ret->value = NULL;
	ret->next = NULL;
	return (ret);
}

t_env		*ft_get_env(char **str)
{
	int		i;
	t_env	*ret;
	t_env	*temp;

	i = 0;
	ret = ft_create_env(str[i++]);
	temp = ret;
	while (str[i])
	{
		temp->next = ft_create_env(str[i]);
		temp = temp->next;
		i++;
	}
	return (ret);
}
