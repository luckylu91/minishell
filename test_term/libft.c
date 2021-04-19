#include "libft.h"

void	ft_arrayclear(void **array, size_t size)
{
	size_t i;

	i = 0;
	if (array)
	{
		while (i < size)
			free(array[i++]);
		free(array);
	}
}

int		ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}


void	*ft_calloc(size_t count, size_t size)
{
	size_t	total_size;
	void	*m;

	total_size = count * size;
	m = malloc(total_size);
	if (m == NULL)
		return (NULL);
	ft_bzero(m, total_size);
	return (m);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_uchar;
	unsigned char	c_uchar;
	size_t			i;

	s_uchar = (unsigned char*)s;
	c_uchar = (unsigned char)c;
	i = 0;
	while (i < n)
		s_uchar[i++] = c_uchar;
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_uc;
	unsigned char	*src_uc;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_uc = (unsigned char*)dst;
	src_uc = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dst_uc[i] = src_uc[i];
		i++;
	}
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return ((int)(unsigned char)s1[i] - (int)(unsigned char)s2[i]);
}
