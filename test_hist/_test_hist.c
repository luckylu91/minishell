#include "hist.h"

int g_exit_code;

t_hist	*setup1()
{
	t_hist *h = create_hist(".hist");

	printf("hist->len = %d\n", h->len);
	printf("hist->histsize = %d\n", h->hist_size);
	printf("hist->histfilesize = %d\n", h->histfile_size);

	add_hist_line(h, ft_strdup("line 1"));
	add_hist_line(h, ft_strdup("line 2"));
	add_hist_line(h, ft_strdup("line 3"));

	printf("hist->len = %d\n", h->len);
	printf("%s\n", get_hist_line(h));

	return (h);
}

void test1(t_hist *h)
{
	move_hist(h, 1);
	printf("move +1; line = ");
	printf("%s\n", get_hist_line(h));

	move_hist(h, 1);
	printf("move +1; line = ");
	printf("%s\n", get_hist_line(h));

	printf("adding cop; line =  ");
	add_hist_line(h, ft_strdup("cop"));
	printf("%s\n", get_hist_line(h));

	move_hist(h, 1);
	printf("move +1; line = ");
	printf("%s\n", get_hist_line(h));
	
	move_hist(h, -1);
	printf("move -1; line = ");
	printf("%s\n", get_hist_line(h));

	move_hist(h, -1);
	printf("move -1; line = ");
	printf("%s\n", get_hist_line(h));
}

int main()
{
	t_hist *h;

	h = setup1();
	test1(h);
	destroy_hist(h);
}
