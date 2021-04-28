#include "execution.h"

int g_exit_code;

int main()
{
	t_hist *h = create_hist(".hist");
	destroy_hist(h);
}
