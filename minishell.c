/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:42:36 by lgrisel           #+#    #+#             */
/*   Updated: 2025/03/03 10:14:31 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->str)
	{
		free(mini->str);
		mini->str = NULL;
	}
	if (mini->args)
	{
		while (mini->args[i])
		{
			free(mini->args[i]);
			mini->args[i] = NULL;
			i++;
		}
		free(mini->args);
		mini->args = NULL;
	}
	if (mini->tokens)
	{
		free_list(mini->tokens);
		mini->tokens = NULL;
	}
}

void	final_cleanup(t_mini *mini)
{
	int	i;

	if (mini->env)
	{
		i = 0;
		while (i < mini->env->count)
		{
			free(mini->env->env_vars[i]);
			i++;
		}
		free(mini->env->env_vars);
		free(mini->env);
	}
}

void	handle_command(t_mini *mini, t_node *list)
{
	char	*expanded_str;

	if (only_space(mini))
		return ;
	else if (!(ft_strncmp(mini->args[0], "exit", 4))
		&& ft_strlen(mini->args[0]) == 4)
		ft_exit(mini, list);
	else if (ft_strncmp(mini->str, "echo", 4) == 0
		&& (mini->str[4] == ' ' || mini->str[4] == '\0'))
	{
		expanded_str = expand_variables(mini->str,
				mini->last_exit_status, mini->env);
		ft_echo(expanded_str);
		free(expanded_str);
	}
	else if (ft_strncmp(mini->str, "cd", 2) == 0
		&& (mini->str[2] == ' ' || mini->str[2] == '\0'))
	{
		change_directory(mini);
	}
	else
	{
		printf("%s: command not found\n", mini->args[0]);
		mini->last_exit_status = 127;
	}
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_mini	mini;
	t_node	*list;
	
	setup_signals();
	initialize_mini(&mini, env);
	if (ac != 1 && av && env)
		return (printf("No arguments needed\n"), 1);
	while (1)
	{
		mini.str = readline("minishell$ ");
		if (!mini.str)
			break;
		if (empty_line(mini.str))
			continue;
		if (count_words(mini.str, &mini) == (size_t)-1)
		{
			free(mini.str);
			continue;
		}
		add_history(mini.str);
		mini.args = ft_split_all(mini.str);
		list = NULL;
		// parse_input(mini.str, &list);
		// print_list(list);
		handle_command(&mini, list);
		clean(&mini);
	}
	clean(&mini);
	final_cleanup(&mini);
	return (0);
}
