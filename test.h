#ifndef TEST_H
# define TEST_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define BUFF_SIZE 64
# define UNIQ_SIZE 16384

/*
** Структура:
**	Название страны
**	Сумма по count (по заданию)
**	Число уникальных user_id для country (по заданию)
**	Массив уникальных id
**	Указатель на следующий элемент s_list
*/

typedef struct			s_list
{
	char				*country;
	size_t				sum;
	int					count_uniq;
	int					uniq[UNIQ_SIZE];
	struct s_list		*next;
}						t_list;

char		*strnew(size_t size);
char		*strjoin(char *s1, char *s2);
char		*strsub(char *s, unsigned int start, size_t len);
void		strdel(char **s);
void		uniq_init(int *array, int len);
t_list		*create_node(void);
void		add_node_back(t_list *begin, t_list *new);
void		add_id(int *array, int id);
void		fill_struct(t_list *list, char *str);
t_list		*find_node(t_list *begin, char *str);
int			go_to_end(char **str, int situation);
int			valid_simbols(char *str);

#endif
