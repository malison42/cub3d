#include "libft.h"

int	ft_min(int a, int b)
{
	return (a * (a < b) + b * (a >= b));
}
