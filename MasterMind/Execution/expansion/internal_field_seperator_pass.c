/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_field_seperator_pass.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:24:32 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

char	*red_ifs_pass(char *str)
{
	char	*cleaned;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	cleaned = allocate_gc(malloc(sizeof(char) * (o_ft_strlen(str) + 1)));
	if (!cleaned)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != (char)1 && str[i] != (char)127)
		{
			cleaned[j] = str[i];
			j++;
		}
		i++;
	}
	cleaned[j] = '\0';
	return (cleaned);
}
