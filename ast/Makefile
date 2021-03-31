SUBDIRS = $(shell find .. -type d | grep -Ev "(.git|.vscode)")
IFLAGS = $(addprefix -I, $(SUBDIRS))
LFLAGS = -L../libft -lft
SRCS = $(addprefix add/, add_textitem_totext.c add_textredir_tocmd.c add_cmd_tochain.c)
SRCS += $(addprefix create_destroy/, create_ast.c create_block.c destroy_block.c dup_block.c destroy_ast.c)
SRCS += $(addprefix parse/, identify_semicol.c parse_cmd.c parse_cmdchain.c parse_cmdseq.c parse_redir.c parse_text.c skip_spaces.c to_str.c)
# SRCS += $(addprefix lst_utils/, )
SRCS += $(addprefix print/, print_ast.c print_block.c)
SRCS += $(addprefix ../block_api/, block_at.c is_chainop.c is_eof.c is_redirop.c is_semicol.c is_space.c is_special.c is_wildcard.c parse_redirop.c is_text.c)
SRCS += $(addprefix errors/, unexpected_token.c)
OBJS = $(SRCS:%.c=%.o) 
LIBFT = ../libft/libft.a

$(LIBFT):
	make -C ../libft bonus

libft:
	make -C ../libft bonus

%.o:	%.c
	gcc -c $< -o $@ $(IFLAGS)

.SECONDARY:	$(OBJS)

_%:	_%.c $(OBJS) $(LIBFT)
	gcc $< $(OBJS) -o $@ $(IFLAGS) $(LFLAGS)

clean:
	make -C ../libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ../libft fclean

.PHONY: all libft clean fclean
