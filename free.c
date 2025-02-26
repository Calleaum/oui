/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:22:13 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/26 10:26:26 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env_vars(char **env_vars, int index)
{
    if (env_vars[index] != NULL) // Continue tant qu'il y a des chaînes
    {
        free(env_vars[index]); // Libère la chaîne actuelle
        free_env_vars(env_vars, index + 1); // Appelle récursivement pour la suivante
    }
}

void free_env(t_env *env)
{
    if (!env)
        return;
    free_env_vars(env->env_vars, 0); // Libère les chaînes
    free(env->env_vars);              // Libère le tableau
    free(env);                        // Libère la structure
}

void free_expand(t_expand *exp)
{
    if (!exp)
        return;
    free(exp->expanded); // Libère la chaîne expandée
}

void free_tokens(t_node *tokens)
{
    if (!tokens)
        return; // Si le nœud est NULL, on retourne

    free_tokens(tokens->next); // Appelle récursivement pour le prochain nœud
    free(tokens->content);      // Libère la chaîne du nœud courant
    free(tokens);               // Libère le nœud courant
}

void free_mini(t_mini *mini)
{
    if (!mini)
        return;

    free(mini->str);
    free(mini->tmpstr);

    if (mini->args)
    {
        int index = 0;
        while (mini->args[index] != NULL) // Utilisation d'une boucle while au lieu d'une fonction imbriquée
        {
            free(mini->args[index]); // Libère chaque chaîne
            index++; // Passe à l'index suivant
        }
        free(mini->args); // Libère le tableau lui-même
    }

    free_tokens(mini->tokens); // Libère les tokens
    free_env(mini->env);       // Libère l'environnement
    free(mini);                // Libère la structure t_mini
}