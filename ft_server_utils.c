#include "ft_minitalk.h"

int	ft_pow(int base, int expo)
{
	int	result;

	result = 1;
	while (expo-- > 0)
	{
		result *= base;
	}
	return (result);
}
