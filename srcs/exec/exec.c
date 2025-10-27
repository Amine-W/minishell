/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:50:17 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/24 17:56:29 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_ast(t_node *node, char **envp)
{
	int	status;
	
	if (node == NULL)
		return (-1);
	if (node->type == NODE_COMMAND)
		status = exec_command(node->command, envp);
	else if (node->type == NODE_AND)
		status = exec_and(node, envp);
	else if (node->type == NODE_OR)
		status = exec_or(node, envp);
	else if (node->type == NODE_PIPE)
		status = exec_pipeline(node, envp);
	return (status);
}
