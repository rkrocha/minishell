/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_wildcard_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkochhan <rkochhan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 10:53:49 by rkochhan          #+#    #+#             */
/*   Updated: 2022/01/04 14:51:45 by rkochhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	matrix_len(char **matrix)
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


static t_bool	matrix_sort(char **matrix)
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

static void	compare_and_expand(char **exp_str, char *name, char *exp)
{
	(void)exp;



	if (name[0] == '.')
		return ;
	if (!*exp_str)
		*exp_str = ft_strdup(name);
	else
	{
		*exp_str = ft_strjoin_free(exp_str, "\30");
		*exp_str = ft_strjoin_free(exp_str, name);
	}
}

static char	**get_expansions(t_shell *msh, char *expansion)
{
	struct dirent	*ret;
	DIR				*folder;
	char			*expansion_str = NULL;
	char			**expansion_args;

	folder = opendir(msh->pwd);
	if (!folder)
		return (NULL);
	ret = readdir(folder);
	while (ret)
	{
		compare_and_expand(&expansion_str, ret->d_name, expansion);
		ret = readdir(folder);
	}
	expansion_args = ft_split(expansion_str, '\30');
	free(expansion_str);
	closedir(folder);
	while (matrix_sort(expansion_args) != TRUE)
		;
	return (expansion_args);


	// recebe pwd e expansion
	// retorna array de strs que tomarão o lugar do arg "expansion" no argv
}

static int	arg_wildcard_parser(t_shell *msh, t_cmd *cmd, int current_arg)
{
	char	**new_argv;
	char	**expansion_args;
	int		expansion_len;

	expansion_args = get_expansions(msh, cmd->argv[current_arg]);
	expansion_len = matrix_len(expansion_args);
	new_argv = (char **)ft_calloc(expansion_len + matrix_len(cmd->argv) + 1,
			sizeof(char *));
	ft_memcpy(new_argv, cmd->argv, current_arg * sizeof(char *));
	ft_memcpy(&new_argv[matrix_len(new_argv)], expansion_args,
			expansion_len * sizeof(char *));
	ft_memcpy(&new_argv[matrix_len(new_argv)], &cmd->argv[current_arg + 1],
			matrix_len(&cmd->argv[current_arg + 1]) * sizeof(char *));
	free(cmd->argv[current_arg]);
	free(cmd->argv);
	free(expansion_args);
	cmd->argv = new_argv;
	return (matrix_len(new_argv));

	// essa seria a função que expande cada wildcard
	// primeiro teria que analisar a expansão e verificar o número de resultados
	// alocar um argv maior que suporte o novo número de args e popular as lacunas do argv
	// concatenar no novo argv os args anteriores, os novos args vindos da expansão, e os seguintes
	// o novo argv substitui o antigo no new_cmd
}

void	cmd_wildcard_parser(t_shell *msh, t_cmd *new_cmd)
{
	int		i;
	char	*asterisk;

	i = 0;
	while (new_cmd->argv[i])
	{
		asterisk = ft_strchr(new_cmd->argv[i], '*');
		if (asterisk && !is_inquotes(new_cmd->argv[i], asterisk))
			i += arg_wildcard_parser(msh, new_cmd, i);
		else
			i++;
	}
	new_cmd->argc = matrix_len(new_cmd->argv);
}
