#include "test.h"

void		uniq_init(int *array, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		array[i] = 0;
		i++;
	}
}

t_list		*create_node(char *country, size_t sum, int count_uniq)
{
	t_list	*temp;

	if (!(temp = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (country == NULL)
	{
		temp->country = NULL;
		temp->sum = 0;
		temp->count_uniq = 0;
		uniq_init(temp->uniq, UNIQ_SIZE);
		temp->next = NULL;
	}
	else
	{
		if (!(temp->country = (char *)malloc(sizeof(char)
			* (strlen(country) + 1))))
		{
			free(temp);
			return (NULL);
		}
		strcpy(temp->country, country);
		temp->sum = sum;
		temp->count_uniq = count_uniq;
		uniq_init(temp->uniq, UNIQ_SIZE);
		temp->next = NULL;
	}
	return (temp);
}

void		add_node_back(t_list *begin, t_list *new)
{
	t_list	*temp;

	if (begin != NULL && new != NULL)
	{
		temp = begin;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void		add_id(int *array, int id)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (array[i] == id)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if ((flag == 0) && (i < (UNIQ_SIZE - 1)))
		array[i] = id;
}

void		fill_struct(t_list *list, char *str)
{
	char	*temp;

	if (list != NULL && str != NULL && *str != '\0')
	{
		if (list->country == NULL)
		{
			temp = strrchr(str, ';');
			list->country = ++temp;
		}
		temp = strchr(str, ';');
		list->sum += atoi(++temp);
		add_id(list->uniq, atoi(str));
	}
}

t_list		*find_node(t_list *begin, char *str)
{
	char	*temp_str;
	t_list	*temp_node;

	if (str != NULL && *str != '\0')
	{
		temp_node = begin;
		temp_str = strrchr(str, ';');
		temp_str++;
		while (temp_node)
		{
			if (strcmp(temp_node->country, temp_str) == 0)
				return (temp_node);
			temp_node = temp_node->next;
		}
	}
	return (NULL);
}
