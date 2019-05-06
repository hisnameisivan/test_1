#include "test.h"

/*
** Функция выделяет память (с пом. malloc) под строку длины (size + 1)
** заполненную '\0'.
*/

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

/*
** Функция выделяет память (с пом. malloc) под строку состоящую из s1 и s2.
*/

char		*strjoin(char *s1, char *s2)
{
	char	*temp;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	temp = NULL;
	if (s1 != NULL || s2 != NULL)
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

/*
** Функция выделяет память (с пом. malloc) под строку, образованную из
** участка строки s с позиции start длины len.
*/

char		*strsub(char *s, unsigned int start, size_t len)
{
	char	*temp;
	size_t	i;

	if (s != NULL)
	{
		i = 0;
		if (!(temp = strnew(len)))
			return (NULL);
		while ((i < len) && (*s != '\0'))
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

/*
** Функция освобождает выделенную под строку s память (с пом. free)
** и "зануляет" указатель s.
*/

void		strdel(char **s)
{
	if (s != NULL)
	{
		free(*s);
		*s = NULL;
	}
}
