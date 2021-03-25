

struct
{
    t_ast   *building_ast;
    int     is_error;
    int     is_building_command;
    int     is_piping; // 0 or 1
}

int add_block(t_ast_statemachine *st, char *block)
{
    if (is_redir(block))
        st->add_redir(block);
    ....
}

int main ()
{
    t_list *lst;
    t_ast_statemachine st;

    while (lst)
    {
        add_block(&st, lst->content);
        if (st.is_error)
            print_error(&st);
            //error
        
        lst = lst->next;
    }

}