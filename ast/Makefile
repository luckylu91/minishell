SUBDIRS = $(shell find .. -type d | grep -Ev "(.git|.vscode)")
IFLAGS = $(addprefix -I, $(SUBDIRS))
LFLAGS = -L../libft -lft
SRCS = $(addprefix create_destroy/, create_block.c destroy_block.c dup_block.c)
OBJS = $(SRCS:%.c=%.o) 
LIBFT = ../libft/libft.a

$(LIBFT):
	make -C ../libft bonus

libft:
	make -C ../libft bonus

_%:	_%.c $(LIBFT)
	gcc $< $(SRCS) -o $@ $(IFLAGS) $(LFLAGS)

clean:
	make -C ../libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ../libft fclean
