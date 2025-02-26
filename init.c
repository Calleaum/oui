/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:37:54 by calleaum          #+#    #+#             */
/*   Updated: 2025/02/26 14:46:51 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void initialize_env(t_env *env) {
//     env->env_vars = NULL; // Initialisé à NULL, pas d'environnement au départ
//     env->count = 0; // Compteur initialisé à 0
// }

// // Fonction d'initialisation pour t_expand
// void initialize_expand(t_expand *expand) {
//     expand->expanded = NULL; // Initialisé à NULL
//     expand->j = 0; // Initialisé à 0
// }

// // Fonction d'initialisation pour t_expand_data
// void initialize_expand_data(t_expand_data *data, t_env *env) {
//     data->last_exit_status = 0; // Initialisé à 0
//     data->env = env; // Pointeur vers l'environnement
// }

// // Fonction d'initialisation pour t_node
// void initialize_node(t_node *node) {
//     node->content = NULL; // Initialisé à NULL
//     node->token = 0; // Valeur par défaut pour le token
//     node->dollar_in_single = 0; // Valeur par défaut pour dollar_in_single
//     node->next = NULL; // Initialisé à NULL
// }

// // Fonction d'initialisation pour t_mini
// void initialize_minix(t_mini *mini, t_env *env) {
//     mini->str = NULL; // Initialisé à NULL
//     mini->tmpstr = NULL; // Initialisé à NULL
//     mini->args = NULL; // Initialisé à NULL
//     mini->tokens = NULL; // Initialisé à NULL
//     mini->last_exit_status = 0; // Initialisé à 0
//     mini->count = 0; // Compteur initialisé à 0
//     mini->in_word = 0; // Initialisé à 0
//     mini->quote = '\0'; // Aucune citation par défaut
//     mini->env = env; // Initialisation avec l'environnement
// }