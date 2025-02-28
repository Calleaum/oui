/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:06:09 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/28 16:11:46 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *mini, t_node *list)
{
	int	i;

	if (mini->args[1] && mini->args[2] && isdigit_str(mini->args[1]))
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		clean(mini);
		free_list(list);
		exit(1);
	}
	else if (mini->args[1] && !isdigit_str(mini->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(mini->args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean(mini);
		free_list(list);
		exit(2);
	}
	else if (mini->args[1])
		i = ft_atoi(mini->args[1]);
	else
		i = 0;
	clean(mini);
	final_cleanup(mini);
	free_list(list);
	exit(i);
}
