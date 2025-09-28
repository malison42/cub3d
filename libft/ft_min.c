#include "libft.h"

size_t	ft_min(size_t a, size_t b)
{
	return (a * (a < b) + b * (a >= b));
}
