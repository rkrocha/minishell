/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_expansion_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:36:05 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/06 14:17:05 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*define_needle(char *exp, int j)
{
	char	*needle;

	needle = NULL;
	if (exp[j] != '*' && ft_strchr(&exp[j], '*'))
		needle = ft_substr(exp, j, ft_strchr(&exp[j], '*') - &exp[j]);
	else if (exp[j] != '*' && !ft_strchr(&exp[j], '*'))
		needle = ft_strdup(&exp[j]);
	return (needle);
}

static int	increment_expansion(char *needle, char *exp, int j)
{
	if (needle)
		return (j + ft_strlen(needle));
	else if (ft_strignore(&exp[j], "*"))
		return (j + ft_strignore(&exp[j], "*") - &exp[j]);
	else
		return (ft_strlen(exp));
}

t_bool	is_valid_expansion(char *name, char *exp)
{
	int		i;
	int		j;
	char	*needle;
	t_bool	is_valid;

	i = 0;
	j = 0;
	is_valid = TRUE;
	while (is_valid && exp[j])
	{
		needle = define_needle(exp, j);
		if (j == 0 && needle && !ft_strncmp(name, needle, ft_strlen(needle)))
			i += ft_strlen(needle);
		else if (j > 0 && needle && ft_strchr(&exp[j], '*')
			&& ft_strnstr(&name[i], needle, ft_strlen(&name[i])))
			i += ft_strnstr(&name[i], needle,
					ft_strlen(&name[i])) - &name[i] + ft_strlen(needle);
		else if (j > 0 && needle && !ft_strchr(&exp[j], '*'))
			is_valid = is_valid_end(&name[i], needle);
		else if (needle)
			is_valid = FALSE;
		j = increment_expansion(needle, exp, j);
		ft_strdel(&needle);
	}
	return (is_valid);
}

void	wildcard_expand(char **exp_str, char *name, char *exp)
{
	if (name[0] == '.' && exp[0] != '.')
		return ;
	if (!*exp_str)
		*exp_str = ft_strdup(name);
	else
	{
		*exp_str = ft_strjoin_free(exp_str, "\30");
		*exp_str = ft_strjoin_free(exp_str, name);
	}
}
