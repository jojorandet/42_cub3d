/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:36:01 by hdougoud          #+#    #+#             */
/*   Updated: 2025/07/18 10:36:25 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_new_line(char *buffer)
{
	char	*fragment;
	int		i;

	i = has_new_line(buffer) - 1;
	fragment = (char *)malloc(sizeof(char) * (i + 2));
	if (!fragment)
		return (NULL);
	ft_strcpy(fragment, buffer, 0, i);
	ft_strcpy(buffer, buffer, i + 1, ft_strlen(buffer) - 1);
	return (fragment);
}

static char	*process_buffer_with_newline(char *line, char *buffer)
{
	char	*tmp2;

	tmp2 = extract_new_line(buffer);
	if (!tmp2)
		return (free(line), NULL);
	return (join_and_free(line, tmp2));
}

static char	*append_buffer_to_line(char *line, char *buffer)
{
	char	*tmp;

	tmp = line;
	line = ft_strjoin(line, buffer);
	free(tmp);
	return (line);
}

static char	*read_until_eol_or_eof(int fd, char *buffer)
{
	int		bytes_read;
	char	*line;

	line = ft_strdup(buffer);
	if (!line)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFERSIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (has_new_line(buffer))
			return (process_buffer_with_newline(line, buffer));
		line = append_buffer_to_line(line, buffer);
		if (!line)
			return (NULL);
		bytes_read = read(fd, buffer, BUFFERSIZE);
	}
	if (*buffer)
		return (*buffer = '\0', line);
	return (free(line), NULL);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFERSIZE + 1];

	if (fd < 0 || BUFFERSIZE < 1)
		return (NULL);
	if (has_new_line(buffer))
		return (extract_new_line(buffer));
	else
		return (read_until_eol_or_eof(fd, buffer));
}
