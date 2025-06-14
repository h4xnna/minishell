# include "minishell.h"

void	space_pars(t_list *list, t_data *data)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
		data->j = 0;
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
	}
	data->i++;
}

void	operator_pars(t_list *list, t_data *data, char *args)
{
	if (data->j > 0)
	{
		data->retour[data->j] = '\0';
		node_creation(list, ft_strdup(data->retour));
		data->j = 0;
	}
	if (args[data->i] == '>' && args[data->i + 1] == '>')
	{
		node_creation(list, ft_strdup(">>"));
		data->i += 2;
	}
	else if (args[data->i] == '<' && args[data->i + 1] == '<')
	{
		node_creation(list, ft_strdup("<<"));
		data->i += 2;
	}
	else
	{
		data->retour[0] = args[data->i++];
		data->retour[1] = '\0';
		node_creation(list, ft_strdup(data->retour));
	}	
}

void	single_quote_pars(t_data *data, char *args)
{
	data->i++;
	while (args[data->i] && args[data->i] != '\'')
		data->retour[data->j++] = args[data->i++];
	if (args[data->i] == '\'')
		data->i++;
	else
		exit (1);
}

void	double_quotes_pars(t_data *data, char *args)
{
	data->i++;
	while (args[data->i] && args[data->i] != '"')
	{
		if (args[data->i] == '$')
			double_quotes_expansion(data, args);
		else
			data->retour[data->j++] = args[data->i++];
	}
	if (args[data->i] == '"')
		data->i++;
	else 
		exit (1);
}

void	dollar_pars(t_data *data, char *args)
{
	char c;

	data->i++;
	if (is_digit(args[data->i]) || is_quote(args[data->i]))
	{
		c = args[data->i];
		data->i++;
		if (is_quote(args[data->i - 1]))
		{
			while (args[data->i] && !is_quote(args[data->i]))
				data->retour[data->j++] = args[data->i++];
			if (args[data->i] == c)
				data->i++;
			else
				exit (1);
		}
		while (is_digit(args[data->i]))
			data->i++;
	}
	else if (args[data->i] == '=' || args[data->i] == '%')
		data->retour[data->j++] = '$';
	else if (args[data->i] == '?')
	{
		return_code(data, args);
		data->i++;
	}
	else
		expansion(data, args);
}