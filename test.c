#include "test.h"

/*
** Считывание содержания файла с файловым дескриптором fd в переменную reading.
*/

static char	*read_file(int fd)
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

/*
** Строка (символы до '\n') из reading помещается в one_string. Функция
** "нарезает" reading на отдельные строки.
*/

static char	*split_reading(char **reading)
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

/*
** Подсчет уникальных id для страны country.
*/

static int	count_uniq(int *array)
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

/*
** Программа рассчитана на работу с одним аргументом (имя файла). Подаваемый
** файл открывается open. По файловому дескриптору fd происходит считывание
** содержания файла целиком в reading. Далее split_reading "нарезает" reading
** по одной строке в one_string. Каждая строка one_string проходит валидацию.
** Если строка корректна, то мы ищем в списке узел, соответствующий стране
** country из one_string. Если такого узла нет, то создаем его и отправляем в
** конец односвязного списка. Далее происходит запись интересующей нас инфор-
** мации о стране в поля структуры (узла). Когда весь контент обработан (сим-
** волы в reading закончились). Последним шагом является проход по получивше-
** муся односвязному списку и вывод информации. Подсчет уникальных id происхо-
** дит на этом же шаге.
** Предусмотрены сообщения об ошибках ввода.
** Вся выделенная память очищена (valgrind definitely lost: 0 bytes in 0
** blocks).
*/

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
			while (valid_simbols(one_string) == 0)
			{
				free(one_string);
				one_string = split_reading(&reading);
				if (one_string == NULL)
					break ;
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
			strdel(&one_string);
		}
		strdel(&reading);
		temp = begin;
		while (temp != NULL)
		{
			if (temp->country != NULL)
				printf("%s;%zu;%d\n", temp->country, temp->sum,
					temp->count_uniq = count_uniq(temp->uniq));
			begin = temp->next;
			if (temp->country != NULL)
				strdel(&(temp->country));
			free(temp);
			temp = begin;
		}
		temp = NULL;
		return (0);
	}
	else
	{
		printf("Invalid input\n");
		return (-1);
	}
}
