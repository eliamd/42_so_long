/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edetoh <edetoh@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:04:50 by edetoh            #+#    #+#             */
/*   Updated: 2024/11/26 11:29:44 by edetoh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(t_list_gnl *list)
{
	int		line_len;
	int		k;

	line_len = 0;
	while (list)
	{
		k = 0;
		while (list->content[k] != '\0')
		{
			if (list->content[k] == '\n')
			{
				line_len++;
				return (line_len);
			}
			k++;
			line_len++;
		}
		list = list->next;
	}
	return (line_len);
}

static char	*get_line(t_list_gnl *list)
{
	char	*line;
	int		line_len;
	int		k;
	int		i;

	k = 0;
	line_len = count_len(list);
	line = malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (list)
	{
		i = 0;
		while (list->content[i] != '\0')
		{
			if (list->content[i] == '\n')
				return (line[k++] = '\n', line[k] = '\0', line);
			line[k++] = list->content[i++];
		}
		list = list->next;
	}
	line[k] = '\0';
	return (line);
}

int	found_newline(t_list_gnl *list)
{
	char	*last_content_string;
	int		i;

	if (!list)
		return (0);
	last_content_string = ft_lstlast_gnl(list)->content;
	i = 0;
	while (last_content_string[i] != '\0')
	{
		if (last_content_string[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	clean_list(t_list_gnl **list)
{
	t_list_gnl		*last_node;
	t_list_gnl		*clean_node;
	int				i;
	int				k;
	char			*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return ;
	clean_node = malloc(sizeof(t_list_gnl));
	if (!clean_node)
		return ;
	last_node = ft_lstlast_gnl(*list);
	i = 0;
	k = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
		buf[k++] = last_node->content[i];
	buf[k] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	dealloc(list, clean_node, buf);
}

char	*get_next_line(int fd)
{
	static t_list_gnl	*list[1024];
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(list[fd]);
		return (NULL);
	}
	create_list(&list[fd], fd);
	if (!list[fd])
		return (NULL);
	next_line = get_line(list[fd]);
	clean_list(&list[fd]);
	return (next_line);
}

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>

// int main(void)
// {
// 	int fd = open("bonjour.txt", O_RDONLY);
// 	int fd2 = open("tt.txt", O_RDONLY);

// 	char *chargnl;
// 	while (1)
// 	{
// 		chargnl = get_next_line(fd);
// 		printf("%s", chargnl);
// 		if (!chargnl)
// 			break ;
// 		free(chargnl);
// 		chargnl = get_next_line(fd2);
// 		printf("%s", chargnl);
// 		if (!chargnl)
// 			break ;
// 		free(chargnl);
// 	}
// 	return 0;
// }