/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/01 19:56:33 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// int has_heredoc(t_data *data)
// {
	
// 	while (data)
// 	{
// 		if (data->type && ft_strcmp(data->type, "HEREDOC") == 0 && ft_strcmp(data->word, "<<") == 0)
// 			return (1);
// 		data = data->next;
// 	}
// 	return (0);
// }

// void	here_doc(t_data *data)
// {	

// 	int fd;
// 	char *line = NULL;
	
// 	fd = open("here_doc", O_TRUNC | O_CREAT | O_WRONLY, 0777);
// 	if(fd < 0)
// 		return ;
// 	while(1)
// 	{
// 		line = readline("\033[1m\033[38;5;129mheredoc → \033[0m");
// 		if(!line)
// 			break;
// 		if(ft_strcmp(line, data->word) == 0)
// 		{
// 			free(line);
// 			break;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);

		
// 	}
// 	free(line);
// 	close (fd);
	
	
	
// }