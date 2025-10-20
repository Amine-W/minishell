/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:00:55 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/16 11:27:38 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_node_type type, t_command *command)
{
	t_node	*new_node;
	
	new_node = malloc(sizeof(t_node));
	if(!new_node)
		return(NULL);
	new_node->type = type;
	new_node->command = command;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	count_nodes(t_node *node)
{
	if(node == NULL)
		return (0);
	if(node->type == NODE_COMMAND)
		return (1);
	else
		return(1 + count_nodes(node->left) + count_nodes(node->right));
}
