/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools12.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 22:28:18 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/26 22:28:18 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	takeoff_red(t_token *res)
{
	t_token	*curr;
	t_token	*tmp;
	t_token	*reserve;

	tmp = NULL;
	curr = res->next;
	reserve = res;
	while (curr)
	{
		free(curr->identity);
		free(tmp);
		tmp = curr;
		if (curr->next == NULL)
			return (free(tmp), reserve->next = NULL, 0);
		if (curr->next->op_case || curr->space_next == true)
			return (reserve->next = curr->next, free(tmp), 0);
		curr = curr->next;
	}
	return (1);
}

static t_token	*red_join(t_token *curr)
{
	char	*tmp;
	t_token	*reserve;

	tmp = NULL;
	reserve = curr;
	while (curr->space_next == false && curr->next
		&& !curr->next->op_case)
	{
		tmp = reserve->identity;
		reserve->identity = ft_strjoin(reserve->identity, curr->next->identity);
		if (!reserve->was_double_quote)
			reserve->was_double_quote = F;
		reserve->was_single_quote = 0;
		free(tmp);
		if (!reserve->identity)
			return (NULL);
		curr = curr->next;
	}
	if (reserve->next && !reserve->next->op_case
		&& !(1 <= reserve->next->tok && reserve->next->tok <= 4))
		takeoff_red(reserve);
	return (reserve);
}

int	join_redirections(t_token **id_class)
{
	t_token	*curr;

	curr = *id_class;
	curr = red_join(curr);
	if (curr == NULL)
		return (0);
	return (1);
}

t_token	*get_reserve_del(t_token *curr)
{
	while (curr)
	{
		if (curr->next_del == false)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
