#include "test.h"

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

int			count_uniq(int *array)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (array[i] != 0)
	{
		count++;
		i++;
	}
	return (count);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*reading;
	char	*one_string;
	t_list	*begin;
	t_list	*temp;

	if (argc == 2)
	{
		begin = NULL;
		temp = NULL;
		fd = open(argv[1], O_RDONLY);
		if ((reading = read_file(fd)) == NULL)
		{
			printf("Invalid input\n");
			return (-1);
		}
		while (*reading != '\0')
		{
			one_string = split_reading(&reading);
			if (valid_simbols(one_string) == 0)
			{
				free(one_string);
				one_string = split_reading(&reading);
				if (one_string == NULL)
				{
					free(reading);
					break ;
				}
			}
			if (begin == NULL)
			{
				begin = create_node();
				temp = begin;
			}
			else
			{
				if ((temp = find_node(begin, one_string)) == NULL)
					add_node_back(begin, temp = create_node());
			}
			fill_struct(temp, one_string);
			free(one_string);
		}
		free(reading);
		temp = begin;
		while (temp != NULL)
		{
			if (temp->country != NULL)
				printf("%s;%zu;%d\n", temp->country, temp->sum,
					temp->count_uniq = count_uniq(temp->uniq));
			begin = temp->next;
			if (temp->country != NULL)
				free(temp->country);
			free(temp);
			temp = begin;
		}
		return (0);
	}
	else
	{
		printf("Invalid input\n");
		return (-1);
	}
}
