/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/07/04 19:20:18 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_heredoc(t_data *data)
{
	if (data->type && !ft_strcmp(data->type, "HERE_DOC"))
		return (1);
	return (0);
}

// void here_doc_cmd(t_data *data)
// {
// 	int fd;
// 	char *line = NULL;
// 	if (data->next->next && ft_strcmp(data->next->next->type, "CMD") == 0
// 		&& ft_strcmp(data->next->word, line) != 0)
// 	{
// 		// printf("%s", data->next->next->type);
// 		fd = open("here_doc", O_RDONLY);
// 		if (fd < 0)
// 			return ;
// 		dup2(fd, STDIN_FILENO);
// 		unlink("here_doc");
// 		close(fd);
// 		return ;
// 	}
// 	return ;
// }

void	here_doc(t_data *data)
{
	(void)data;
	int fd;
	char *line = NULL;
	
	if (!data->next || !data)
		return ;
	if (!data->here_doc_fd)
	{
		data->here_doc_fd = open("here_doc", O_TRUNC | O_CREAT | O_RDWR, 0677);
		if (data->here_doc_fd < 0)
			return ;
	}
	fd = data->here_doc_fd;
	while ((line = readline("\033[1m\033[31mheredoc → \033[0m")) != NULL
		&& ft_strcmp(data->next->word, line) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (line)
		free(line);
	close(fd);
	if (data->next->next && ft_strcmp(data->next->next->type, "CMD") == 0
		&& ft_strcmp(data->next->word, line) != 0)
	{
		// printf("%s", data->next->next->type);
		fd = open("here_doc", O_RDONLY);
		if (fd < 0)
			return ;
		dup2(fd, STDIN_FILENO);
		unlink("here_doc");
		close(fd);
	}
}


