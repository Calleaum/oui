/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calleaum <calleaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:42:12 by lgrisel           #+#    #+#             */
/*   Updated: 2025/02/26 09:10:28 by calleaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_node *create_node(char *content, int token, int dollar_in_single)
// {
// 	t_node *new_node = malloc(sizeof(t_node));
// 	if (!new_node)
// 		return NULL;
// 	new_node->content = ft_strdup(content);
// 	new_node->token = token;
// 	new_node->dollar_in_single = dollar_in_single;
// 	new_node->next = NULL;
// 	return new_node;
// }

// // Function to append a node to the linked list
// void append_node(t_node **head, char *content, int token, int dollar_in_single)
// {
// 	t_node *new_node = create_node(content, token, dollar_in_single);
// 	if (!new_node)
// 		return;
// 	if (!*head) {
// 		*head = new_node;
// 	} else {
// 		t_node *temp = *head;
// 		while (temp->next)
// 			temp = temp->next;
// 		temp->next = new_node;
// 	}
// }

// // Function to determine the token type
// int get_token_type(char *word)
// {
// 	if (ft_strncmp(word, "|", INT_MAX) == 0) return PIPE;
// 	if (ft_strncmp(word, ">>", INT_MAX) == 0) return OUTPUT_APPEND;
// 	if (ft_strncmp(word, ">", INT_MAX) == 0) return OUTPUT_TRUNC;
// 	if (ft_strncmp(word, "<<", INT_MAX) == 0) return HEREDOC;
// 	if (ft_strncmp(word, "<", INT_MAX) == 0) return INPUT_FILE;
// 	if (ft_strncmp(word, "echo", INT_MAX) == 0 || ft_strncmp(word, "cd", INT_MAX) == 0 || ft_strncmp(word, "pwd", INT_MAX) == 0 ||
// 		ft_strncmp(word, "exit", INT_MAX) == 0 || ft_strncmp(word, "export", INT_MAX) == 0 || ft_strncmp(word, "env", INT_MAX) == 0 || ft_strncmp(word, "unset", INT_MAX) == 0) 
// 		return CMD;
// 	return ARG; // Default to argument
// }

// // Function to parse the input while handling quotes
// void parse_input(char *input, t_node **head)
// {
// 	int i = 0, in_single = 0, in_double = 0;
// 	char buffer[1024]; // Temporary storage
// 	int buf_index = 0;
// 	int dollar_in_single = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == '\'')
// 			in_single = !in_single;
// 		else if (input[i] == '"' && !in_single)
// 			in_double = !in_double;
// 		else
// 		{
// 			if (in_single && input[i] == '$')
// 				dollar_in_single = 1;
// 			if (!isspace(input[i]) || in_single || in_double || strchr("|<>", input[i]))
// 			{
// 				if (strchr("|<>", input[i]) && !in_single && !in_double)
// 				{
// 					if (buf_index > 0)
// 					{
// 						buffer[buf_index] = '\0';
// 						append_node(head, buffer, get_token_type(buffer), dollar_in_single);
// 						buf_index = 0;
// 						dollar_in_single = 0;
// 					}
// 					if ((input[i] == '<' || input[i] == '>') && input[i + 1] == input[i])
// 					{
// 						buffer[0] = input[i];
// 						buffer[1] = input[i + 1];
// 						buffer[2] = '\0';
// 						append_node(head, buffer, get_token_type(buffer), 0);
// 						i++; // Skip the next character
// 					}
// 					else
// 					{
// 						buffer[0] = input[i];
// 						buffer[1] = '\0';
// 						append_node(head, buffer, get_token_type(buffer), 0);
// 					}
// 				}
// 				else
// 				{
// 					buffer[buf_index++] = input[i];
// 				}
// 			}
// 			else
// 			{
// 				if (buf_index > 0)
// 				{
// 					buffer[buf_index] = '\0';
// 					append_node(head, buffer, get_token_type(buffer), dollar_in_single);
// 					buf_index = 0;
// 					dollar_in_single = 0;
// 				}
// 			}
// 		}
// 		i++;
// 	}
// 	if (buf_index > 0)
// 	{
// 		buffer[buf_index] = '\0';
// 		append_node(head, buffer, get_token_type(buffer), dollar_in_single);
// 	}
// }

// void	print_list(t_node *head)
// {
// 	while (head)
// 	{
// 		printf("Content: %s, Token: %d, Dollar in Single: %d\n", head->content, head->token, head->dollar_in_single);
// 		head = head->next;
// 	}
// }

// void free_list(t_node *head)
// {
// 	t_node *temp;

// 	while (head)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp->content);
// 		free(temp);
// 	}
// }

void append_node(t_node **head, char *value, int token, int dollar_flag) {
    t_node *new_node = malloc(sizeof(t_node));
    new_node->content = strdup(value);
    new_node->token = token;
    new_node->dollar_in_single = dollar_flag;
    new_node->next = NULL;

    if (!*head) {
        *head = new_node;
        return;
    }
    t_node *temp = *head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_node;
}

// Function to determine token type
int get_token_type(char *str) {
    if (strcmp(str, "|") == 0) return 5;
    if (strcmp(str, "<") == 0) return 1;
    if (strcmp(str, "<<") == 0) return 2;
    if (strcmp(str, ">") == 0) return 3;
    if (strcmp(str, ">>") == 0) return 4;
    if (!strcmp(str, "echo") || !strcmp(str, "cd") || !strcmp(str, "pwd") ||
        !strcmp(str, "exit") || !strcmp(str, "export") || !strcmp(str, "env") ||
        !strcmp(str, "unset"))
        return 6;
    return 7;
}

// Function to parse input and build linked list
void parse_input(char *input, t_node **head) {
    int i = 0, j;
    char buffer[1024];
    int in_single_quote = 0, in_double_quote = 0, dollar_flag = 0;

    while (input[i]) {
        while (isspace(input[i])) i++;  // Skip spaces
        if (!input[i]) break;

        j = 0;
        dollar_flag = 0;

        while (input[i] && (!isspace(input[i]) || in_single_quote || in_double_quote)) {
            if (input[i] == '\'' && !in_double_quote) {
                in_single_quote = !in_single_quote;
            } else if (input[i] == '"' && !in_single_quote) {
                in_double_quote = !in_double_quote;
            } else {
                if (in_single_quote && input[i] == '$')
                    dollar_flag = 1;
                buffer[j++] = input[i];
            }
            i++;
        }
        buffer[j] = '\0';

        if (j > 0)
            append_node(head, buffer, get_token_type(buffer), dollar_flag);
    }
}

// Function to print linked list
void print_list(t_node *head) {
    while (head) {
        printf("Value: %s | Token: %d | Dollar in SQ: %d\n", head->content, head->token, head->dollar_in_single);
        head = head->next;
    }
}

// Free the linked list
void free_list(t_node *head)
{
	t_node *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}
