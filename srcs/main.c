/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:49:44 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/22 10:51:01 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			printf("exit\n");
			clear_history();
			break ;
		}
		else if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);
		printf("vous avez tapé: %s\n", line);
		free(line);
	}
	return (0);
}
