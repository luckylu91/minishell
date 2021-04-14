#include <string.h>
#include <errno.h>
#include <stdio.h>
int	cd(char **argv);

int main()
{
	char *args[4] = {"cd", "nowhere", "tookittoofar", 0};
	int ret;

	if (ret = cd(args))
		printf("%s\n", strerror(errno));
}
