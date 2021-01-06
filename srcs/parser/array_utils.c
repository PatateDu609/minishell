/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gboucett <gboucett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 22:19:09 by gboucett          #+#    #+#             */
/*   Updated: 2021/01/06 19:52:16 by gboucett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**ft_copy_splitted(char **strs, size_t new_len)
{
	char	**result;
	size_t	len;

	len = ft_size_splitted(strs);
	result = ft_calloc(new_len + 1, sizeof(char *));
	if (!result)
		return (NULL);
	ft_memcpy(result, strs, len * sizeof(char *));
	free(strs);
	return (result);
}

char		**ft_strs_append(char **strs1, char **to_append)
{
	size_t	len1;
	size_t	len2;
	char	**result;

	len1 = ft_size_splitted(strs1);
	len2 = ft_size_splitted(to_append);
	result = ft_copy_splitted(strs1, len1 + len2);
	if (!result)
		return (NULL);
	ft_memcpy(result + len1, to_append, len2 * sizeof(char *));
	free(to_append);
	return (result);
}

char		**ft_strs_append_str(char **strs, char *str)
{
	size_t	len1;
	char	**result;

	if (!str)
		str = "";
	len1 = ft_size_splitted(strs);
	result = ft_copy_splitted(strs, len1 + 1);
	if (!result)
		return (NULL);
	result[len1] = ft_strdup(str);
	return (result);
}

char		**ft_strs_remove(char **strs, size_t index)
{
	size_t	len;

	len = ft_size_splitted(strs);
	if (len <= index)
		return (NULL);
	free(strs[index]);
	ft_memmove(strs + index, strs + index + 1, sizeof(char *) * (len - index));
	return (ft_copy_splitted(strs, len - 1));
}

t_redirect	**ft_append_redir(t_redirect **redirs, t_redirect *redir)
{
	t_redirect	**result;
	size_t		len;

	len = ft_size_redirs(redirs);
	result = ft_calloc(len + 2, sizeof(t_redirect *));
	if (!result)
		return (NULL);
	ft_memcpy(result, redirs, len * sizeof(t_redirect *));
	free(redirs);
	result[len] = redir;
	return (result);
}
