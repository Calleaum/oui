/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:22:13 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/03 17:27:34 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->str)
	{
		free(mini->str);
		mini->str = NULL;
	}
	if (mini->args)
	{
		while (mini->args[i])
		{
			free(mini->args[i]);
			mini->args[i] = NULL;
			i++;
		}
		free(mini->args);
		mini->args = NULL;
	}
	if (mini->tokens)
	{
		free_list(mini->tokens);
		mini->tokens = NULL;
	}
}

void	final_cleanup(t_mini *mini)
{
	int	i;

	if (mini->env)
	{
		i = 0;
		while (i < mini->env->count)
		{
			free(mini->env->env_vars[i]);
			i++;
		}
		free(mini->env->env_vars);
		free(mini->env);
	}
}

void	free_env_vars(char **env_vars, int index)
{
	if (env_vars[index] != NULL)
	{
		free(env_vars[index]);
		free_env_vars(env_vars, index + 1);
	}
}

void	free_env(t_env *env)
{
	if (!env)
		return ;
	free_env_vars(env->env_vars, 0);
	free(env->env_vars);
	free(env);
}

void	free_tokens(t_node *tokens)
{
	if (!tokens)
		return ;
	free_tokens(tokens->next);
	free(tokens->content);
	free(tokens);
}
