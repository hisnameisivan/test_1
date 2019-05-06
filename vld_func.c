#include "test.h"

/*
** Однотипные повторяющиеся в функции валидации valid_simbols конструкции.
** Переключатель situation позволяет искать по цифрам (0) и буквам (1).
*/

int			go_to_end(char **str, int situation)
{
	if (situation == 0)
	{
		while (**str != ';' && **str != '\0')
		{
			if (**str < '0' || **str > '9')
				return (0);
			(*str)++;
		}
	}
	else if (situation == 1)
	{
		while (**str != ';' && **str != '\0')
		{
			if ((**str < 'a' || **str > 'z') && (**str < 'A' || **str > 'Z')
				&& **str != ' ')
				return (0);
			(*str)++;
		}
	}
	return (1);
}

/*
** Валидация строки str. Идем по строке до ';' и проверяем, что все элементы
** строки - цифры. Далее опять идем по строке до ';' и проверяем тоже самое.
** Последний проход - проверка оставшихся элементов строки на принадлежность
** буквам английского алфавита + ' '. Пробел позволяет вводить конструкции
** вроде The United States of America. Строка обязательна должна начинаться
** с цифры. Вариант с подряд идущими ';;' учтен.
*/

int			valid_simbols(char *str)
{
	if (str != NULL)
	{
		if ((*str < '0' || *str > '9') || (go_to_end(&str, 0) == 0))
			return (0);
		if (*str != '\0')
		{
			str++;
			if ((*str == ';') || (go_to_end(&str, 0) == 0))
				return (0);
		}
		if (*str != '\0')
		{
			str++;
			if (((*str < 'a' || *str > 'z') && (*str < 'A' || *str > 'Z'))
				|| (go_to_end(&str, 1) == 0))
				return (0);
		}
		if (*str == '\0')
			return (1);
	}
	return (0);
}
