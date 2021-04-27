#include <string.h>
#include <errno.h>
#include <stdio.h>

int	our_cd(char **argv);

int main()
{
	char *args[4] = {"cd", "nowhere", "tookittoofar", 0};
	int ret;

	if (ret = our_cd(args))
		printf("%s\n", strerror(errno));
}
