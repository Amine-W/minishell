/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:29:02 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/23 18:25:58 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_command *cmd, char **envp)
{
	pid_t	pid;
	int		code;
	int		status;
	char	*path;
	
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		path = get_path(cmd, envp);
		if (!path)
		{
			print_command_error(cmd->argv[0], 127);
			exit(127);
		}
		execve(path, cmd->argv, envp);
		print_command_error(cmd->argv[0], 126);
		exit(126);
	}
	waitpid(pid, &status, 0);
	return(get_exit_code(status));
}
