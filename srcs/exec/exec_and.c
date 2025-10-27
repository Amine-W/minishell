/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_and.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 15:07:59 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/24 17:49:12 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_and(t_node *node, char **envp)
{
	int	status;

	if (node->left->type == NODE_COMMAND)
		status = exec_command(node->left->command, envp);
	else if (node->left->type != NODE_COMMAND)
		status = exec_ast(node->left, envp);
	if (status == 0)
	{
		if (node->right->type == NODE_COMMAND && status == 0)
			status = exec_command(node->right->command, envp);
		else
			status = exec_ast(node->right, envp);
	}
	return(status);
}
