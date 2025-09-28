#include "libft.h"

size_t	ft_max(size_t a, size_t b)
{
	return (a * (a > b) + b * (a <= b));
}
