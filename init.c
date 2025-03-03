/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:37:54 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/03 10:11:09 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_mini(t_mini *mini, char **env)
{
	mini->str = NULL;
	mini->tmpstr = NULL;
	mini->args = NULL;
	mini->tokens = NULL;
	mini->last_exit_status = 0;
	mini->count = 0;
	mini->in_word = 0;
	mini->quote = 0;
	mini->env = init_env(env);
	if (mini->env)
		init_shell_vars(mini->env);
}
