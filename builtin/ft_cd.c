/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:05:21 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/03 10:04:33 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static char	*get_target_path(t_mini *mini, int *error)
{
	char	*path;

	if (mini->args[1] == NULL || ft_strcmp(mini->args[1], "~") == 0)
	{
		path = get_env_value(mini->env, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (*error = 1, NULL);
		}
	}
	else if (ft_strcmp(mini->args[1], "-") == 0)
	{
		path = get_env_value(mini->env, "OLDPWD");
		if (!path || !*path)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (*error = 1, NULL);
		}
		ft_putendl_fd(path, 1);
	}
	else
		path = mini->args[1];
	return (path);
}

int	change_directory(t_mini *mini)
{
	char	*path;
	int		error;

	error = 0;
	path = get_target_path(mini, &error);
	if (error)
	{
		mini->last_exit_status = 1;
		return (1);
	}
	if (chdir(path) != 0)
	{
		mini->last_exit_status = handle_cd_error(path);
		return (1);
	}
	update_pwd(mini->env);
	mini->last_exit_status = 0;
	return (0);
}
