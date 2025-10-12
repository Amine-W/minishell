/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:49:44 by amwahab           #+#    #+#             */
/*   Updated: 2025/10/12 15:35:41 by amwahab          ###   ########.fr       */
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
			rl_clear_history();
			break ;
		}
		else if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		add_history(line);

		//traiter la commande pour plus tard//
		printf("vous avez tapé: %s\n", line);
		//traiter la commande pour plus tard//
		free(line);
	}
	return (0);
}
