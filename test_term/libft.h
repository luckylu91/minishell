#ifndef LIBFT_H
#define LIBFT_H

#include <unistd.h>
#include <stdlib.h>

void	ft_arrayclear(void **array, size_t size);
int		ft_isprint(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);

#endif