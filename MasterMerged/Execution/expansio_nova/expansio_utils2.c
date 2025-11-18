/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansio_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:33:47 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/26 21:33:47 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

static t_arg	*create_new_arg_node(char *value, t_arg *original_arg)
{
	t_arg	*new_node;

	new_node = allocate_gc(malloc(sizeof(t_arg)));
	new_node->value = allocate_gc(ft_strdup(value));
	new_node->tok = original_arg->tok;
	new_node->was_s_quote = original_arg->was_s_quote;
	new_node->was_d_quote = original_arg->was_d_quote;
	new_node->space_next = original_arg->space_next;
	new_node->next = NULL;
	return (new_node);
}

static t_arg	*create_anon_node(t_arg *original_arg)
{
	t_arg	*new_node;
	char	anon[2];

	anon[0] = ANON;
	anon[1] = '\0';
	new_node = create_new_arg_node(anon, original_arg);
	new_node->space_next = original_arg->space_next;
	return (new_node);
}

t_arg	*split_and_create_nodes(char *expanded_value, t_arg *original_arg)
{
	t_sc	sc;

	sc.split_result = tab_split(expanded_value, " \t");
	if (sc.split_result != NULL && sc.split_result[0] == NULL)
		return (create_anon_node(original_arg));
	sc.head = NULL;
	sc.current = NULL;
	sc.i = 0;
	while (sc.split_result[sc.i] != NULL)
	{
		sc.new_node = create_new_arg_node(sc.split_result[sc.i], original_arg);
		if (sc.split_result[sc.i] != NULL && sc.split_result[sc.i + 1] != NULL)
			sc.new_node->space_next = true;
		else
			sc.new_node->space_next = original_arg->space_next;
		if (sc.head == NULL)
			sc.head = sc.new_node;
		else
			sc.current->next = sc.new_node;
		sc.current = sc.new_node;
		sc.i++;
	}
	return (sc.head);
}
