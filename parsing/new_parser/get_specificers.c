#include "parsing_map.h"

static char	**get_specificers_mode1(void)
{
	char	**specificers;

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

static char	**get_specificers_mode2(void)
{
	char	**specificers;

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

static char	**get_specificers_mode3(void)
{
	char	**specificers;

	specificers = malloc(sizeof(char *) * 3);
	if (!specificers)
		return (perror("malloc"), NULL);
	specificers[0] = "F";
	specificers[1] = "C";
	specificers[2] = NULL;
	return (specificers);
}

char	**get_specificers(int mode)
{
	if (mode == 1)
		return (get_specificers_mode1());
	if (mode == 2)
		return (get_specificers_mode2());
	if (mode == 3)
		return (get_specificers_mode3());
	return (NULL);
}
