/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:29:02 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/23 18:03:29 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		execve(STDOUT_FILENO, cmd->argv, envp);
	
	waitpid(pid, &status, 0);
}