/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmimouni <hmimouni@>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:42:28 by hmimouni          #+#    #+#             */
/*   Updated: 2025/06/30 04:39:23 by hmimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	limiteur(char *str)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = redline("> ");
// 		if ((!line || strcmp(line, str) == 0))
// 		{
// 			return (0);
// 		}
// 	}
// 	return (1);
// }
// void	here_doc(t_data *data)
// {
// 	if (ft_strcmp(data->back->word, "<<") == 0)
// 		return (1);
// 	while (limiteur(data->word))
// }