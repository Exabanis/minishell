/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exabanis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:53:14 by exabanis          #+#    #+#             */
/*   Updated: 2018/09/15 10:11:01 by exabanis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# define FUNC "cd", "echo", "env", "help", "setenv", "unsetenv"

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_util
{
	int				sig;
	int				col;
	int				buf_s;
	char			**env;
}					t_util;

extern t_env		*g_envlst;
extern t_util		*g_utils;

void				ft_newenv(void);
void				ft_sig_handler();
t_env				*ft_get_env(char **str);
int					ft_execute(char **args);
char				*ft_cmd(char *str);
int					ft_cd(char **args);
int					ft_env(void);
int					ft_setenv(char **args);
int					ft_unsetenv(char **args, t_env *ptr);
int					ft_echo(char **args);
int					ft_help(void);
int					ft_exit();
void				ft_setpwd(void);
void				ft_setoldpwd(void);
void				ft_gohome(void);
void				ft_goback(void);
void				ft_go_to(char *str);

#endif
