/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 15:50:17 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/23 17:49:47 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_ast(t_node *node)
{
	if (node == NULL)
		return (-1);
	if (node->type == NODE_COMMAND)
	{
		
	}
	else if (node->type == NODE_AND)
	{
		
	}
	else if (node->type == NODE_OR)
	{
		
	}
	else if (node->type == NODE_PIPE)
	{
		
	}
}
