
#include "parsing_map.h"

char	**get_specificers(int mode)
{
	char	**specificers;

	if (mode == 1)
	{
		specificers = malloc(sizeof(char *) * 7);
		if (!specificers)
			return (perror("malloc"), NULL);
		specificers[0] = "NO";
		specificers[1] = "SO";
		specificers[2] = "WE";
		specificers[3] = "EA";
		specificers[4] = "F";
		specificers[5] = "C";
		specificers[6] = NULL;
		return (specificers);
	}
	if (mode == 2)
	{
		specificers = malloc(sizeof(char *) * 5);
		if (!specificers)
			return (perror("malloc"), NULL);
		specificers[0] = "NO";
		specificers[1] = "SO";
		specificers[2] = "WE";
		specificers[3] = "EA";
		specificers[4] = NULL;
		return (specificers);
	}
	if (mode == 3)
	{
		specificers = malloc(sizeof(char *) * 3);
		if (!specificers)
			return (perror("malloc"), NULL);
		specificers[0] = "F";
		specificers[1] = "C";
		specificers[2] = NULL;
		return (specificers);
	}
	return (NULL);
}
