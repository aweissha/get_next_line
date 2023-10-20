#include <stdio.h>
void test(void)
{
	static int	i;
	i = 0;

	i++;
	printf("%i", i);
}


int main(void)
{
	int i;

	i = 0;
	while (i < 100)
	{
		test();
		i++;
	}
}
