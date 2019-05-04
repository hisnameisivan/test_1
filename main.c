#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int		main()
{
	char	*s = "11231;6;Russia";
	char	*t;

	t = strrchr(s, ';');
	t++;
	// t = strchr(t, ';');
	printf("%s\n", t);
	printf("%d\n", atoi(t));
	printf("%d\n", atoi(s));
	return (0);
}
