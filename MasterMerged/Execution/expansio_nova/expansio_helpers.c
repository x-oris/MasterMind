/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansio_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oimzilen <oimzilen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 21:32:44 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/26 21:32:44 by oimzilen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

t_expand_node	*create_node(char *string)
{
	t_expand_node	*node;

	node = allocate_gc(malloc(sizeof(t_expand_node)));
	if (!node)
		return (NULL);
	node->string = string;
	node->next = NULL;
	return (node);
}

void	add_node_back(t_expand_node **head, t_expand_node *new_node)
{
	t_expand_node	*current;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

int	list_strlen(t_expand_node *head)
{
	t_expand_node	*current;
	int				len;
	int				j;

	len = 0;
	current = head;
	while (current != NULL)
	{
		j = 0;
		while (current->string[j] != '\0')
		{
			len++;
			j++;
		}
		current = current->next;
	}
	return (len);
}
