/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_identool0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 20:55:23 by ayel-bou          #+#    #+#             */
/*   Updated: 2025/08/26 05:32:53 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	identify_argument(t_token **id_class)
{
	t_token	*curr;

	curr = *id_class;
	while (curr != NULL)
	{
		if (curr->op_case)
			break ;
		if (curr->next && ((1 <= curr->tok && curr->tok <= 4)
				|| curr->tok == DEL_ID
				|| curr->tok == 7 || curr->tok == 8))
		{
			curr = curr->next;
			continue ;
		}
		else if (!curr->next && curr->tok != STRING_ID)
			break ;
		curr->tok = ARG_ID;
		curr = curr->next;
	}
}

void	cmd_arg(t_token **curr, int *string)
{
	if ((*curr)->tok == STRING_ID && !*string)
	{
		*string = 1;
		(*curr)->tok = COMMAND_ID;
	}
	else if ((*curr)->tok == STRING_ID && *string == 1)
	{
		*string = 0;
		identify_argument(curr);
	}
}

static void	takeoff_red(t_token *res)
{
	t_token *curr;
	t_token *tmp;
	t_token *reserve;

	tmp = NULL;
	curr = res->next;
	reserve = res;
	while (curr)
	{
		free(tmp);
		tmp = curr;
		if (curr->next == NULL)
		{
			free(tmp);
			reserve->next = NULL;
			break ;
		}
		if (curr->next->op_case || curr->space_next == true)
		{
			reserve->next = curr->next;
			free(tmp);
			break ;
		}
		curr = curr->next;
	}
}

// STILL NEED WORK
static t_token	*red_join(t_token *curr)
{
	char *tmp;
	t_token *reserve;

	tmp = NULL;
	reserve = curr;
	while (curr->space_next == false && curr->next
		&& !curr->next->op_case)
	{
		tmp = reserve->identity;
		reserve->identity = ft_strjoin(reserve->identity, curr->next->identity);
		if (!reserve->identity)
			return (NULL);
		free(tmp);
		curr = curr->next;
	}
	takeoff_red(reserve);
	return (reserve);
}

static int	join_redirections(t_token **id_class)
{
	t_token *curr;

	curr = *id_class;
	curr = red_join(curr);
	if (curr == NULL)
		return (0);
	return (1);
}	

// NEED TO RETURN PROTECTION && TEST FOR LEAKS && OVERALL CHECKING OF BEHAVIOR
void	re_identifications(t_token *curr)
{
	if (curr->tok == RED_IN_ID)
	{
		curr->next->tok = INPUT_FILE_ID;
		join_redirections(&curr->next);
	}
	else if (curr->tok == RED_OUT_ID)
	{
		curr->next->tok = OUTPUT_FILE_ID;
		join_redirections(&curr->next);
	}
	else if (curr->tok == RED_APP_ID)
	{
		curr->next->tok = INPUT_APP_FILE_ID;
		join_redirections(&curr->next);
	}
}

void	check_set_cmd(t_token **curr, t_token **id_class)
{
	if ((*curr)->op_case)
		set_last_cmd(*id_class);
}

void	check_delete(t_token **curr, t_token **id_class)
{
	(*curr) = delete_red(id_class);
	if (!(*curr))
		(*curr) = *id_class;
}
