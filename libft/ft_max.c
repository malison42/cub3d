#include "libft.h"

int	ft_max(int a, int b)
{
	return (a * (a > b) + b * (a <= b));
}
