/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/05 15:37:06 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

static t_list		*readall(int fd)
{
	char			*str;
	t_list			*mem;
	t_list			*tmp;
	t_list			*outp;

	mem = ft_lstnew(NULL, 0);
	outp = mem;
	tmp = NULL;
	while (get_next_line(fd, &str) > 0)
	{
		mem->content = str;
		mem->next = ft_lstnew(0, 0);
		tmp = mem;
		mem = mem->next;
	}
	if (tmp)
	{
		free(tmp->next);
		tmp->next = NULL;
	}
	return (outp);
}

t_info				*get_map(int fd, void *p[2])
{
	t_info			*outp;
	t_list			*tab;

	if (!(outp = malloc(sizeof(t_info))))
		exits(4);
	outp->mid = p[MLXID];
	outp->wid = p[WINID];
	tab = readall(fd);
	if (!(outp->first_pt = transfo(tab)))
		return (NULL);
	return (NULL);
}
