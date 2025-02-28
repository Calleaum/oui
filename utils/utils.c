/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:10:17 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/28 16:18:58 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_space(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->str[i] == '\0')
		return (1);
	while (mini->str[i])
	{
		if (!ft_isspace(mini->str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	isdigit_str(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
