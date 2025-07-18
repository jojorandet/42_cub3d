
#include "cub3d.h"

static bool	is_only_spaces(char *line)
{
	while (*line)
	{
		if ((9 <= *line && *line <= 13) || *line == ' ')
			line++;
		else
			return (false);
	}
	return (true);
}

static void	null_terminate_line(char **line)
{
	char	*cursor;

	cursor = *line;
	while (*cursor && *cursor != '\n')
		cursor++;
	*cursor = '\0';
}

static bool	fill_parse_buffer(char ***file_content, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		null_terminate_line(&line);
		if (!is_only_spaces(line) || (i > 5 && is_only_spaces(line)))
		{
			(*file_content)[i] = ft_strdup(line);
			if (!(*file_content)[i])
			{
				free(line);
				free_string_array(file_content);
				return (false);
			}
			i++;
		}
		free(line);
	}
	return (true);
}

static void	count_lines(char *file, int *line_counter)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	*line_counter = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			break ;
		}
		if (*line_counter > 5 && is_only_spaces(line))
			(*line_counter)++;
		else if (!is_only_spaces(line))
			(*line_counter)++;
		free(line);
	}
	close (fd);
}

char	**get_file_content(t_main *main, int fd, char *file)
{
	int		line_counter;
	char	**file_content;

	count_lines(file, &line_counter);
	file_content = ft_calloc(line_counter + 1, sizeof(char *));
	if (!file_content)
	{
		exit_cub3d(main, "Malloc failed in get_file_content.");
		return (NULL);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free_string_array(&file_content);
		exit_cub3d(main, "Open failed in get_file_content");
		return (NULL);
	}
	if (!fill_parse_buffer(&file_content, fd))
	{
		close(fd);
		exit_cub3d(main, "Malloc failed in fill parse buffer.");
		return (NULL);
	}
	close(fd);
	return (file_content);
}
