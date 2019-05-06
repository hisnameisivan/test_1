#include "test.h"

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
