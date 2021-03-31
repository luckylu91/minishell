SUBDIRS = $(shell find .. -type d | grep -Ev "(.git|.vscode)")
IFLAGS = $(addprefix -I, $(SUBDIRS))
LFLAGS = -L../libft -lft
SRCS = $(addprefix add/, add_textitem_totext.c add_textredir_tocmd.c add_cmd_tochain.c)
SRCS += $(addprefix create_destroy/, create_ast.c create_block.c destroy_block.c dup_block.c destroy_ast.c)
SRCS += $(addprefix print/, print_ast.c print_block.c)
SRCS += $(addprefix ../block_api/, parse_redirop.c)
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
