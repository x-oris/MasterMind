/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools11.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:51:08 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/26 02:43:08 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_arglist(t_arg **arg)
{
	t_arg	*temp;

	temp = NULL;
	while ((*arg) != NULL)
	{
		free(temp);
		free((*arg)->value);
		temp = (*arg);
		if ((*arg)->next == NULL)
		{
			free(temp);
			break ;
		}
		(*arg) = (*arg)->next;
	}
}

void	cleaner_arg(t_token *list)
{
	while (list != NULL)
	{
		if (list->arg != NULL)
			clean_arglist(&list->arg);
		list = list->next;
	}
}

void	clean_yard(t_token **yard, int mode)
{
	if (mode == FAIL)
	{
		clean_fd(*yard);
		cleaner_red(*yard);
		cleaner_arg(*yard);
		list_cleaner(yard);
	}
	else if (mode == CLEAN)
		list_cleaner(yard);
}

void	clean_id_class(t_token **id_class, int mode)
{
	if (mode == FAIL)
	{
		clean_fd(*id_class);
		cleaner_red(*id_class);
		cleaner_arg(*id_class);
		list_cleaner(id_class);
	}
	else if (mode == CLEAN)
	{
		clean_fd(*id_class);
		list_cleaner(id_class);
	}
}
void	printer_red(t_red *red, char *str)
{
	// if (str)
		// printf("      ---RED >> ");
	while (red)
	{
		printf("     ---red > %s\n", red->value);
		red = red->next;
	}
}

void	printer_arg(t_arg *arg, char *str)
{
	// if (str)
	// 	printf("      ---ARG >> ");
	while (arg)
	{
		printf("     ---arg > %s\n", arg->value);
		arg = arg->next;
	}
}
void debbuger_tk(t_token *id_class)
{
    t_token *trav = id_class;
    printf("***************************************\n");
    while (trav != NULL)
    {
        printf("RE_identity> %s\n", trav->identity);
        if (trav->tok == 0)
        {
            printf("ID-> PIPE\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 1)
        {
            printf("ID-> RED_IN_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 2)
        {
            printf("ID-> RED_OUT_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 3)
        {
            printf("ID-> RED_APP_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 4)
        {
           printf("ID-> HERE_DOC_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 5)
        {
            printf("ID-> AND_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 6)
        {
            printf("ID-> OR_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 7)
        {
            printf("ID-> BRACE_O_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 8)
        {
            printf("ID-> BRACE_C_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 9)
        {
            printf("ID-> S_QUOTE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 10)
        {
            printf("ID-> D_QUOTE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 11)
        {
            printf("ID-> STRING_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 12)
        {
            printf("ID-> DEL_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
            if (trav->here_doc_fd != -1)
                printf("File Descriptor Stored [fd %d]\n", trav->here_doc_fd);
            else if (trav->here_doc_fd == -1)
                printf("File desciptor Unsaved\n");
        }
        else if (trav->tok == 13)
        {
            printf("ID-> INPUT_FILE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 14)
        {
            printf("ID-> OUTPUT_FILE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 15)
        {
            printf("ID-> INPUT_APP_FILE_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
        }
        else if (trav->tok == 16)
        {
            printf("ID-> COMMAND_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
            if (trav->end == true)
                printf("End Marked\n");
            if (trav->here_document_act == true)
                printf("HERE_DOC_INPUT\n");
            if (trav->red)
                printer_red(trav->red, "Red ");
            if (trav->arg)
                printer_arg(trav->arg, "Ags ");
            if (trav->was_single_quote == 1)
                printf("       └─ Was s quoted\n");
            else
                printf("       └─ Not Quoted\n");
            if (trav->fake == true)
                printf("       └─ FAKE CMD\n");

        }
        else if (trav->tok == 17)
        {
            printf("ID-> ARG_ID\n");
            if (trav->space_next == true)
                printf("Space next True\n");
            if (trav->end == true)
                printf("End Marked\n");
        }
        trav = trav->next;
        printf("****************\n");
    }
    printf("***************************************\n");
    
}
