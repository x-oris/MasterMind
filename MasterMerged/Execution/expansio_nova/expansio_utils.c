#include "../../Parse/minishell.h"

static char	*list_to_string(t_expand_node *head)
{
	t_expand_node	*current;
	char			*result;
	int				i;
	int				j;

	result = allocate_gc(malloc(list_strlen(head) + 1));
	if (!result)
		return (NULL);
	i = 0;
	current = head;
	while (current != NULL)
	{
		j = 0;
		while (current->string[j] != '\0')
		{
			result[i] = current->string[j];
			i++;
			j++;
		}
		current = current->next;
	}
	result[i] = '\0';
	return (result);
}

static char	*get_var_value(char *var_name, t_data *data)
{
	char	*value;

	if (var_name == NULL)
		return (allocate_gc(ft_strdup("")));
	if (ft_strcmp(var_name, "?") == 0)
		return (allocate_gc(ft_itoa(data->exit_status)));
	if (ft_strcmp(var_name, "$") == 0)
		return (allocate_gc(ft_itoa(data->pid)));
	value = find_in_env(data->env, var_name);
	if (value == NULL)
		return (allocate_gc(ft_strdup("")));
	return (allocate_gc(ft_strdup(value)));
}

static int	handle_variable(char *str, int i,
		t_expand_node **head, t_data *data)
{
	int		start;
	char	*var_value;

	if (str[i] == '?' )
	{
		var_value = get_var_value("?", data);
		add_node_back(head, create_node(var_value));
		return (i + 1);
	}
	else if (str[i] == '$')
	{
		var_value = get_var_value("$", data);
		add_node_back(head, create_node(var_value));
		return (i + 1);
	}
	start = i;
	while (str[i] != '\0' && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	var_value = get_var_value(allocate_gc(ft_substr(str,
					start, i - start)), data);
	if (var_value != NULL)
		add_node_back(head, create_node(var_value));
	return (i);
}

static int	handle_character(char *str, int i, t_expand_node **head)
{
	char	*char_str;

	char_str = allocate_gc(ft_substr(str, i, 1));
	add_node_back(head, create_node(char_str));
	return (i + 1);
}

char	*expand_double_quoted(char *str, t_data *data)
{
	t_expand_node	*head;
	int				i;

	head = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && str[i + 1] != '\0'
			&& str[i + 1] != ' ' && str[i + 1] != '\t')
			i = handle_variable(str, i + 1, &head, data);
		else
			i = handle_character(str, i, &head);
	}
	return (list_to_string(head));
}
