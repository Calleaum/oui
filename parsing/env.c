/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:54:45 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/26 15:38:02 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	env->count = i;
	env->env_vars = malloc(sizeof(char *) * (i + 1));
	if (!env->env_vars)
	{
		free(env);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		env->env_vars[i] = ft_strdup(envp[i]);
		if (!env->env_vars[i])
		{
			while (--i >= 0)
				free(env->env_vars[i]);
			free(env->env_vars);
			free(env);
			return (NULL);
		}
		i++;
	}
	env->env_vars[i] = NULL;
	return (env);
}

// Fonction pour obtenir la valeur d'une variable d'environnement
char	*get_env_value(t_env *env, const char *name)
{
	int		i;
	size_t	name_len;

	if (!env || !name)
		return (NULL);
	name_len = ft_strlen(name);
	i = 0;
	while (env->env_vars[i])
	{
		if (ft_strncmp(env->env_vars[i], name, name_len) == 0
			&& env->env_vars[i][name_len] == '=')
			return (env->env_vars[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

// Fonction pour mettre à jour une variable d'environnement
int	set_env_value(t_env *env, const char *name, const char *value)
{
	int		i;
	char	*new_var;

	if (!env || !name)
		return (0);
	i = 0;
	while (env->env_vars[i])
	{
		if (ft_strncmp(env->env_vars[i], name, ft_strlen(name)) == 0
			&& env->env_vars[i][ft_strlen(name)] == '=')
		{
			free(env->env_vars[i]);
			new_var = ft_strjoin3(name, "=", value);
			if (!new_var)
				return (0);
			env->env_vars[i] = new_var;
			return (1);
		}
		i++;
	}
	return (0);
}

char	*expand_env_variable(char *str, int *i, t_expand *exp, t_env *env)
{
	char	*var_name;
	char	*env_value;

	var_name = ft_substr(str, *i, ft_varlen(str + *i));
	if (!var_name)
		return (exp->expanded);
	env_value = get_env_value(env, var_name);
	if (env_value)
	{
		ft_strcpy(exp->expanded + exp->j, env_value);
		exp->j += ft_strlen(env_value);
	}
	free(var_name);
	*i += ft_varlen(str + *i);
	return (exp->expanded);
}

char *process_dollar_sign(char *str, int *i, t_expand *exp, t_expand_data *data)
{
    char *temp;

    (*i)++;
    if (str[*i] == '?')
    {
        temp = expand_exit_status(exp, data->last_exit_status);
        (*i)++;
    }
    else
    {
        temp = expand_env_variable(str, i, exp, data->env);
    }
    if (!temp)
    {
        return NULL;
    }
    size_t len = strlen(temp);
    ft_strncat(exp->expanded, temp, len);
	exp->j += len;
    free(temp);
    return exp->expanded;
}

