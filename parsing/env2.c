/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/28 16:16:51 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *expand_variables(char *str, int last_exit_status, t_env *env)
{
    t_expand exp;
    t_expand_data data;
    int i;

    if (!str)
        return (NULL);
    data.last_exit_status = last_exit_status;
    data.env = env;
    exp.expanded = malloc(calculate_expanded_size(str, last_exit_status, env));
    if (!exp.expanded)
        return (NULL);
    i = 0;
    exp.j = 0;
    while (str[i])
    {
        if (str[i] == '$')
            exp.expanded = process_dollar_sign(str, &i, &exp, &data);
        else
            exp.expanded[exp.j++] = str[i++];
    }
    exp.expanded[exp.j] = '\0';
    return (exp.expanded);
}

// Fonction modifiée calculate_expanded_size
size_t calculate_expanded_size(char *str, int last_exit_status, t_env *env)
{
    size_t size;
    int i;

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

// Fonction modifiée handle_dollar
size_t handle_dollar(char *str, int *i, int last_exit_status, t_env *env)
{
    size_t size = 0;
    char *exit_str;
    char *var_name;
    char *env_value;

    (*i)++;    
    if (str[*i] == '?')
    {
        exit_str = ft_itoa(last_exit_status);
        if (exit_str)
        {
            size += ft_strlen(exit_str);
            free(exit_str);
        }
        (*i)++;
    }
    else if (ft_isalpha(str[*i]) || str[*i] == '_')
    {
        var_name = ft_substr(str, *i, ft_varlen(str + *i));
        if (var_name)
        {
            env_value = get_env_value(env, var_name);
            if (env_value)
                size = ft_strlen(env_value);
            free(var_name);
            *i += ft_varlen(str + *i);
        }
    }
    else
    {
        size = 1; // Juste pour le caractère '$'
    }
    
    return size;
}


char *expand_exit_status(t_expand *exp, int last_exit_status)
{
    char *exit_str;
    int len;

    exit_str = ft_itoa(last_exit_status);
    if (!exit_str)
        return (exp->expanded);
    len = ft_strlen(exit_str);
    ft_strcpy(exp->expanded + exp->j, exit_str);
    exp->j += len;
    free(exit_str);
    return (exp->expanded);
}


// test //

int add_env_value(t_env *env, const char *name, const char *value)
{
    char **new_env_vars;
    char *new_var;
    int i;

    if (!env || !name)
        return (0);

    for (i = 0; i < env->count; i++)
    {
        if (env->env_vars[i] && 
            ft_strncmp(env->env_vars[i], name, ft_strlen(name)) == 0 &&
            env->env_vars[i][ft_strlen(name)] == '=')
        {
            free(env->env_vars[i]);
            new_var = ft_strjoin3(name, "=", value ? value : "");
            if (!new_var)
                return (0);
            env->env_vars[i] = new_var;
            return (1);
        }
    }

    new_env_vars = malloc(sizeof(char *) * (env->count + 2));
    if (!new_env_vars)
        return (0);

    for (i = 0; i < env->count; i++)
        new_env_vars[i] = env->env_vars[i];

    new_var = ft_strjoin3(name, "=", value ? value : "");
    if (!new_var)
    {
        free(new_env_vars);
        return (0);
    }

    new_env_vars[env->count] = new_var;
    new_env_vars[env->count + 1] = NULL;
    free(env->env_vars);
    env->env_vars = new_env_vars;
    env->count++;

    return (1);
}


// Fonction pour mettre à jour le PWD après un cd
int update_pwd(t_env *env)
{
    char cwd[PATH_MAX];
    char *old_pwd;

    old_pwd = get_env_value(env, "PWD");
    if (old_pwd)
    {
        if (get_env_value(env, "OLDPWD"))
            set_env_value(env, "OLDPWD", old_pwd);
        else
            add_env_value(env, "OLDPWD", old_pwd);
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return (0);
    if (get_env_value(env, "PWD"))
        return (set_env_value(env, "PWD", cwd));
    else
        return (add_env_value(env, "PWD", cwd));
}

// Fonction à appeler au démarrage du shell pour initialiser les variables importantes
int init_shell_vars(t_env *env)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (!get_env_value(env, "PWD"))
            add_env_value(env, "PWD", cwd);
    }
    if (!get_env_value(env, "PATH"))
        add_env_value(env, "PATH", "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
    if (!get_env_value(env, "OLDPWD"))
        add_env_value(env, "OLDPWD", "");
    return (1);
}