/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by calleaum          #+#    #+#             */
/*   Updated: 2025/03/03 17:22:53 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_variables(char *str, int last_exit_status, t_env *env)
{
	t_expand		exp;
	int				i;

	if (!str)
		return (NULL);
	env->last_exit_status = last_exit_status;
	env = env;
	exp.expanded = malloc(calculate_expanded_size(str, last_exit_status, env));
	if (!exp.expanded)
		return (NULL);
	i = 0;
	exp.j = 0;
	while (str[i])
	{
		if (str[i] == '$')
			exp.expanded = process_dollar_sign(str, &i, &exp, env);
		else
			exp.expanded[exp.j++] = str[i++];
	}
	exp.expanded[exp.j] = '\0';
	return (exp.expanded);
}

char	*expand_exit_status(t_expand *exp, int last_exit_status)
{
	char	*exit_str;
	int		len;

	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return (exp->expanded);
	len = ft_strlen(exit_str);
	ft_strcpy(exp->expanded + exp->j, exit_str);
	exp->j += len;
	free(exit_str);
	return (exp->expanded);
}

// Fonction modifiée calculate_expanded_size
size_t	calculate_expanded_size(char *str, int last_exit_status, t_env *env)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			size += handle_dollar(str, &i, last_exit_status, env);
		else
		{
			size++;
			i++;
		}
	}
	return (size + 1);
}
