/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:29:16 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/06 13:40:39 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	matrix_len(char **matrix)
{
	int	len;

	len = 0;
	while (matrix[len])
		len++;
	return (len);
}

int	ft_strccmp_caseless(const char *s1, const char *s2, char c)
{
	size_t				i;
	const unsigned char	*s1cmp;
	const unsigned char	*s2cmp;

	i = 0;
	s1cmp = (unsigned char *)s1;
	s2cmp = (unsigned char *)s2;
	while (s1cmp[i] && s2cmp[i])
	{
		if (s1cmp[i] == c)
			return (-1);
		if (s2cmp[i] == c)
			return (1);
		if (ft_toupper(s1cmp[i]) != ft_toupper(s2cmp[i]))
			return (ft_toupper(s1cmp[i]) - ft_toupper(s2cmp[i]));
		i++;
	}
	if (ft_toupper(s1cmp[i]) != ft_toupper(s2cmp[i]))
		return (ft_toupper(s1cmp[i]) - ft_toupper(s2cmp[i]));
	return (0);
}

t_bool	matrix_sort(char **matrix)
{
	int		i;
	t_bool	end_of_sort;

	i = 0;
	end_of_sort = TRUE;
	while (matrix[i])
	{
		if (matrix[i + 1]
			&& ft_strccmp_caseless(matrix[i], matrix[i + 1], '\0') > 0)
		{
			end_of_sort = FALSE;
			ft_strswap(&matrix[i], &matrix[i + 1]);
		}
		i++;
	}
	return (end_of_sort);
}
