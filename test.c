#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 64

typedef struct			s_list
{
	char				*country;
	size_t				sum;
	int					count_uniq;
	struct s_id_list	*id_list;
	struct s_list		*next;
}						t_list;

typedef struct			s_id_list
{
	int					id;
	struct s_id_list	*next;
}						t_id_list;

//TODO validation (1. strlen по id (5 символов))

char		*strnew(size_t size)
{
	char	*temp;
	size_t	i;

	i = 0;
	if (((size + 1) == 0) || !(temp = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (i < (size + 1))
	{
		temp[i] = '\0';
		i++;
	}
	return (temp);
}

char		*strjoin(char const *s1, char const *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	temp = NULL;
	if (s1 || s2)
	{
		len_s1 = (s1 ? strlen(s1) : 0);
		len_s2 = (s2 ? strlen(s2) : 0);
		if (!(temp = strnew(len_s1 + len_s2)))
			return (NULL);
		i = -1;
		j = -1;
		while (++i < len_s1)
			temp[i] = s1[i];
		while (++j < len_s2)
			temp[i + j] = s2[j];
		temp[i + j] = '\0';
	}
	return (temp);
}

char		*strsub(char const *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	if (s)
	{
		i = 0;
		if (!(temp = strnew(len)))
			return (NULL);
		while ((i < len) && *s)
		{
			temp[i] = s[start + i];
			i++;
		}
		temp[i] = '\0';
		return (temp);
	}
	else
		return (NULL);
}

t_id_list	*create_id_node(int id)
{
	t_id_list	*temp;

	if (!(temp = (t_id_list *)malloc(sizeof(t_id_list))))
		return (NULL);
	temp->id = id;
	temp->next = NULL;
	return (temp);
}

t_list		*create_node(char const *country, size_t sum, int count_uniq)
{
	t_list	*temp;

	if (!(temp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!country)
	{
		temp->country = NULL;
		temp->sum = 0;
		temp->count_uniq = 0;
		temp->id_list = NULL;
		temp->next = NULL;
	}
	else
	{
		if (!(temp->country = (char *)malloc(sizeof(char) * (strlen(country) + 1))))
		{
			free(temp);
			return (NULL);
		}
		strcpy(temp->country, country);
		temp->sum = sum;
		temp->count_uniq = count_uniq;
		temp->id_list = NULL;
		temp->next = NULL;
	}
	return (temp);
}

void		add_id_node_back(t_id_list *begin, t_id_list *new)
{
	t_id_list	*temp;

	if (begin && new)
	{
		temp = begin;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

void		add_node_back(t_list *begin, t_list *new)
{
	t_list	*temp;

	if (begin && new)
	{
		temp = begin;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

char		*read_file(int fd)
{
	int		ret;
	char	buf[BUFF_SIZE + 1];
	char	*temp;
	char	*reading;

	reading = NULL;
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		temp = strjoin(reading, buf);
		free(reading);
		reading = temp;
	}
	return (reading);
}

char		*split_reading(char **reading)
{
	char	*temp;
	char	*one_string;

	one_string = NULL;
	if ((temp = strchr(*reading, '\n')) != NULL)
	{
		one_string = strsub(*reading, 0, temp - *reading);
		temp = strsub(*reading, temp - *reading + 1,
			strlen(*reading) - (temp - *reading));
		free(*reading);
		*reading = temp;
	}
	return (one_string);
}

void		fill_struct(t_list *list, char *str)
{
	t_id_list	*id_temp;
	char		*temp;

	temp = strrchr(str, ';');
	list->country = ++temp;
	temp = strchr(str, ';');
	list->sum += atoi(++temp);
	// if (list)
	// {
	// 	if (list->id_list == NULL)
	// 	{
	// 		list->id_list = create_id_node(atoi(one_string));
	// 		id_temp = list->id_list;
	// 	}
	// 	else
	// 		add_id_node_back(list->id_list, id_temp = create_id_node(atoi(one_string)));
	// }
}

t_list		*find_node(t_list *begin, char *str)
{
	char	*temp_str;
	t_list	*temp_node;

	temp_node = begin;
	temp_str = strrchr(str, ';');
	temp_str++;
	while (temp_node)
	{
		if (strcmp(temp_node->country, temp_str) == 0)
			return (temp_node);
		temp_node = temp_node->next;
	}
	return (NULL);
}

// int			analyze_string(char *str)
// {
// 	return (strcmp(str, "user_id;count;country"));
// }

int		main(int argc, char **argv)
{
	int			fd;
	char		*reading;
	char		*one_string;
	t_list		*begin;
	t_list		*temp;

	begin = NULL;
	temp = NULL;
	fd = open(argv[1], O_RDONLY);
	if ((reading = read_file(fd)) == NULL)
		return (-1); //TODO
	// printf("1. reading = %s\n", reading);
	// one_string = split_reading(&reading);
	// printf("1. one_string = %s\n", one_string);
	// printf("2. reading = %s\n", reading);
	while (*reading != '\0')
	{
	//	if (analyze_string(one_string) == 0)
			one_string = split_reading(&reading);
		// printf("2. one_string = %s\n", one_string);
		if (begin == NULL)
		{
			begin = create_node(NULL, 0, 0);
			temp = begin;
		}
		else
		{
			if ((temp = find_node(begin, one_string)) == NULL)
				add_node_back(begin, temp = create_node("NULL", 0, 0));
		}
		// if (find_node(begin) == NULL)
		// 	add_node_back(begin, temp = create_node("NULL", 0, 0));
		// else
		// 	temp = find_node(begin);
		fill_struct(temp, one_string);
	}
	while (begin)
	{
		// id_temp = temp->id_list;
		// while (id_temp)
		// {
		// 	printf("%d\n", id_temp->id);
		// 	id_temp = id_temp->next;
		// }
		printf("%s , %zu, %d\n", begin->country, begin->sum, begin->count_uniq);
		begin = begin->next;
	}
	// printf("3. reading = %s\n", reading);
	// printf("3. one_string = %s\n", one_string);
	return (0);
}
