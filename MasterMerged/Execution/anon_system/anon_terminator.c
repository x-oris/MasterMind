/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anon_terminator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayel-bou <ayel-bou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:02:06 by oimzilen          #+#    #+#             */
/*   Updated: 2025/08/19 19:25:13 by ayel-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Parse/minishell.h"

bool	single_anon(char *str)
{
	if (str[0] == ANON && str[1] == '\0')
		return (true);
	return (false);
}

static void	init_terminator(t_ifs **args, int *i)
{
	*args = NULL;
	*i = 0;
}

char	**terminate_inside_anons(char **argv)
{
	t_ifs	*args;
	char	**new_argv;
	int		i;

	init_terminator(&args, &i);
	while (argv[i])
	{
		if (!single_anon(argv[i]))
		{
			if (add_ifs_back(&args, argv[i]) != EXIT_SUCCESS)
				return (NULL);
		}
		i++;
	}
	new_argv = ifs_list_to_argv(args);
	return (new_argv);
}
