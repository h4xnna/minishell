# include "../minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	open_infile(int infilefd, char *infile)
{
	infilefd = open(infile, O_RDONLY);
	if (infilefd < 0)
		return (0);
	return (infilefd);
}

t_pipex	*init_pipex(int ac, char **av)
{
	t_pipex	*pipex;
	int		i;

	i = 0;
	pipex = calloc(1, sizeof(t_pipex));
	if (!pipex)
	{
		free(pipex);
		return (NULL);
	}
	pipex->count_cmd = ac - 3;
	pipex->pid = calloc(pipex->count_cmd, sizeof(pid_t));
	i = 0;
	pipex->pipefd = calloc(pipex->count_cmd - 1, sizeof(int *));
	if (!pipex->pid || !pipex->pipefd)
	{
		free(pipex->pid);
		free(pipex->pipefd);
		return (NULL);
	}
	i = 0;
	while ((pipex->count_cmd - 1) > i)
	{
		pipex->pipefd[i] = calloc(2, sizeof(int));
		if (!pipex->pipefd[i])
			return (NULL);
		if (pipe(pipex->pipefd[i]) < 0)
			return (NULL);
		i++;
	}
	i = 0;
	pipex->infilefd = open_infile(pipex->infilefd, av[1]);
	pipex->outfilefd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->outfilefd < 0 || pipex->infilefd < 0)
		return (NULL);
	return (pipex);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->count_cmd - 1))
	{
		close(pipex->pipefd[i][0]);
		close(pipex->pipefd[i][1]);
		i++;
	}
}
int	word_lenght(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

int	get_out_lenght(char const *s, char c)
{
	int	out;
	int	i;

	i = 0;
	out = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			out++;
			i += word_lenght(s + i, c);
		}
		else
			i++;
	}
	return (out);
}

char	*special_strdup(char const *s, char c, int *outi)
{
	char	*out;
	int		i;

	out = ft_calloc(word_lenght(s, c) + 1, sizeof(char));
	if (out)
	{
		i = 0;
		while (s[i] != c && s[i])
		{
			out[i] = s[i];
			i++;
		}
		*outi += word_lenght(s, c);
	}
	else
		return (NULL);
	return (out);
}

void	free_split(char **out, int i)
{
	while (i > 0)
	{
		free(out[i]);
		i--;
	}
	free(out);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		i;
	int		j;

	out = ft_calloc(get_out_lenght(s, c) + 1, sizeof(char *));
	if (!out)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			out[j] = special_strdup(s + i, c, &i);
			if (!out[j])
			{
				free_split(out, j);
				return (NULL);
			}
			j++;
		}
		else
			i++;
	}
	return (out);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*out;

	if (size > 0)
		if (MAX_INT / size < nmemb)
			return (NULL);
	out = malloc(nmemb * size);
	if (!out)
		return (NULL);
	ft_bzero(out, nmemb * size);
	return (out);
}