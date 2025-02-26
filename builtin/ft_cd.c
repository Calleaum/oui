/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:05:21 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/26 11:36:53 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void change_directory(t_mini *mini)
{
    char *path;
    char current_dir[PATH_MAX];
    
    // Obtenir le répertoire courant pour OLDPWD
    if (getcwd(current_dir, PATH_MAX) == NULL)
    {
        perror("cd: getcwd");
        mini->last_exit_status = 1;
        return;
    }
    
    // Déterminer le chemin cible
    if (mini->args[1] == NULL || ft_strcmp(mini->args[1], "~") == 0)
    {
        // cd sans arguments ou cd ~ -> aller au $HOME
        path = get_env_value(mini->env, "HOME");
        if (!path)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            mini->last_exit_status = 1;
            return;
        }
    }
    else if (ft_strcmp(mini->args[1], "-") == 0)
    {
        // cd - -> aller au $OLDPWD
        path = get_env_value(mini->env, "OLDPWD");
        if (!path)
        {
            ft_putstr_fd("cd: OLDPWD not set\n", 2);
            mini->last_exit_status = 1;
            return;
        }
        ft_putendl_fd(path, 1); // Afficher le répertoire pour cd -
    }
    else
        path = mini->args[1];
    
    // Changer de répertoire
    if (chdir(path) != 0)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(strerror(errno), 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(path, 2);
        mini->last_exit_status = 1;
        return;
    }
    
    // Mettre à jour OLDPWD
    set_env_value(mini->env, "OLDPWD", current_dir);
    
    // Mettre à jour PWD
    if (getcwd(current_dir, PATH_MAX) != NULL)
        set_env_value(mini->env, "PWD", current_dir);
    
    mini->last_exit_status = 0;
}