#ifndef TEST_H
# define TEST_H

# include "lamer.h"
# include "lesfrites.h"

typedef struct s_caca
{
	int		c;
	int		a;
	char	*ca;
} t_caca;

int				cacafun(void);
t_caca			cacafun2(int c, int a, char *ca);
struct s_caca	cacafun2(int c, int a, char *ca);

typedef struct s_pipi
{
	int				p;
	struct s_caca	c;
	struct s_caca	*aca;
} t_catatat;

int				caca_funy(void);
t_caca			__cacafun2y(int c, int a, char *ca);
struct s_caca	**cacafun2y(int c, int a, char *ca);

#endif

