/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:05:21 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/28 14:41:47 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int change_directory(t_mini *mini)
{
    char *path;
    
    // Obtenir le chemin cible
    if (mini->args[1] == NULL || ft_strcmp(mini->args[1], "~") == 0)
    {
        path = get_env_value(mini->env, "HOME");
        if (!path)
        {
            ft_putstr_fd("minishell: cd: HOME not set\n", 2);
            return (1);
        }
    }
    else if (ft_strcmp(mini->args[1], "-") == 0)
    {
        path = get_env_value(mini->env, "OLDPWD");
        if (!path || !*path)
        {
            ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
            return (1);
        }
        ft_putendl_fd(path, 1); // Afficher le répertoire pour cd -
    }
    else
    {
        path = mini->args[1];
    }
    
    // Changer de répertoire
    if (chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd("\n", 2);
        mini->last_exit_status = 1;
        return (1);
    }
    
    // IMPORTANT: Mettre à jour PWD et OLDPWD après un changement réussi
    update_pwd(mini->env);
    
    mini->last_exit_status = 0;
    return (0);
}
