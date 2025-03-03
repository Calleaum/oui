/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:45:27 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/03 17:23:38 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libftFINAL/libft.h"
# include <unistd.h>
# include <linux/limits.h>
# include <limits.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
    char    **env_vars;
    int     count;
	int     last_exit_status;
} t_env;

typedef struct s_expand
{
	char	*expanded;
	int		j;
}	t_expand;

// Linked list structure
typedef struct s_node {
	char	*content;
	int		token;
	int		dollar_in_single;
	struct s_node *next;
} t_node;


typedef struct s_mini
{
	char	*str;
	char	*tmpstr;
	char	**args;
	t_node	*tokens;
	int		last_exit_status;
	size_t	count;
	int		in_word;
	char	quote;
	t_env	*env;
}	t_mini;

int	ft_pwd(void);

int add_env_value(t_env *env, const char *name, const char *value);
int update_pwd(t_env *env);
int init_shell_vars(t_env *env);

void initialize_env(t_env *env);
void initialize_expand(t_expand *expand);
// void initialize_expand_data(t_env *env, t_env *env);
void initialize_node(t_node *node);
void initialize_minix(t_mini *mini, t_env *env);

void free_env_vars(char **env_vars, int index);
void free_env(t_env *env);
void free_tokens(t_node *tokens);
void free_mini(t_mini *mini);

char *get_env_value(t_env *env, const char *name);
int set_env_value(t_env *env, const char *name, const char *value);
char *ft_strjoin3(const char *s1, const char *s2, const char *s3);
t_env *init_env(char **envp);
void final_cleanup(t_mini *mini);
void    ft_echo(char *str);
void    ft_exit(t_mini *mini, t_node *list);
void initialize_mini(t_mini *mini, char **env);
char *ft_strcpy2(char *dest, const char *src);
size_t  ft_varlen(char *str);
size_t  handle_dollar(char *str, int *i, int last_exit_status, t_env *env);
size_t  calculate_expanded_size(char *str, int last_exit_status, t_env *env);
char    *expand_exit_status(t_expand *exp, int last_exit_status);
char    *expand_env_variable(char *str, int *i, t_expand *exp, t_env *env);
char *process_dollar_sign(char *str, int *i, t_expand *exp, t_env *env);
char *expand_variables(char *str, int last_exit_status, t_env *env);

// Define token types
#define INPUT_FILE 1
#define HEREDOC 2
#define OUTPUT_TRUNC 3
#define OUTPUT_APPEND 4
#define PIPE 5
#define CMD 6
#define ARG 7


void	parse_input(char *input, t_node **head);
void	print_list(t_node *head);
void	free_list(t_node *head);

int		only_space(t_mini *mini);
int		ft_isspace(char c);
int		isdigit_str(char *str);
char	**ft_split_all(const char *s);
size_t	count_words(const char *s, t_mini *split);

// ctrl //

void	setup_signals(void);

// echo //

// void	ft_echo(char *str);
// void	print_words_with_spaces(char *str, int *i);
// int		handle_n_option(char *str, int *i);

// cd //

/// @brief Changes the current directory and updates PWD
/// @param mini Structure containing the minishell information
int	change_directory(t_mini *mini);

// exit //

void	ft_exit(t_mini *mini, t_node *list);
void	clean(t_mini *mini);

// env //

// /// @brief Processes a dollar sign encountered during expansion
// /// @param str The string to analyze
// /// @param i Pointer to the index in the string, will be updated
// /// @param exp Structure containing the result string and its current index
// /// @param last_exit_status The exit code of the last command
// /// @return Pointer to the updated result string
// char	*process_dollar_sign(char *str, int *i, t_expand *exp, int last_exit_status);
// /// @brief Gets the size of an environment variable
// /// @param str The string containing the variable name starting at index i
// /// @param i Pointer to the index in the string, will be updated to point after the variable name
// /// @return The size of the environment variable's value, or 0 if not found
// size_t	get_var_size(char *str, int *i);
// /// @brief Main function that expands all variables in a string
// /// @param str The string to analyze
// /// @param last_exit_status The exit code of the last command
// /// @return A new string with all variables expanded, or NULL if error
// char	*expand_variables(char *str, int last_exit_status);
// /// @brief Calculates the total size needed after expansion
// /// @param str The string to analyze
// /// @param last_exit_status The exit code of the last command
// /// @return The total calculated size, plus 1 for the final null character
// size_t	calculate_expanded_size(char *str, int last_exit_status);
// /// @brief Handles the expansion of a dollar sign found in a string
// /// @param str The string containing the '$' character
// /// @param i Pointer to the index in the string, will be updated
// /// @param last_exit_status The exit code of the last executed command
// /// @return The size the variable will take once expanded
// size_t	handle_dollar(char *str, int *i, int last_exit_status);
// /// @brief Expands an environment variable into the result string
// /// @param str The string containing the variable name
// /// @param i Pointer to the index in the string, will be updated
// /// @param exp Structure containing the result string and its current index
// /// @return  new string with all variables expanded, or NULL if error
// char	*expand_env_variable(char *str, int *i, t_expand *exp);
// /// @brief Expands the exit code ($?) into the result string
// /// @param exp Structure containing the result string and its current index
// /// @param last_exit_status The exit code of the last command
// /// @return Pointer to the updated result string
// char	*expand_exit_status(t_expand *exp, int last_exit_status);
// /// @brief Calculates the length of a variable name in a string
// /// @param str The string containing the variable name
// /// @return The length of the variable name
// int		ft_varlen(char *str);

#endif
