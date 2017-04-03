/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/03 19:53:09 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

static t_list		*readall(int fd)
{
	char			*str;
	t_list			*mem;
	t_list			*outp;

	mem = ft_lstnew(NULL, 0);
	outp = mem;
	while (get_next_line(fd, &str) > 0)
	{
		mem->content = str;
		mem->next = ft_lstnew(0, 0);
		mem = mem->next;
	}
	return (outp);
}

static int			*byebyebullshit(char **input)
{
	int				*outp;
	int				cnt;
	int				i;

	i = 0;
	cnt = 0;
	while (input[cnt])
		cnt++;
	if (!(outp = malloc(sizeof(int) * (cnt + 1))))
		return (NULL);
	while (i < cnt)
	{
		outp[i] = ft_atoi(input[i]);
		free(input[i++]);
	}
	free(input);
	return (outp);
}

static t_pt			*transfo(t_list *tabinp)
{
	int				i = -1;
	t_list			*tabout;

	tabout = tabinp;
	while (tabout)
	{
		i = -1;
		if (!tabout->next)
			break ;
		tabout->content = ft_strsplit(tabout->content, ' ');
		tabout = tabout->next;
	}
	tabout = tabinp;
	while (tabout)
	{
		if (!(tabout->content = byebyebullshit(tabout->content)))
			return (NULL);
		tabout = tabout->next;
	}

	return (NULL);
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
	outp->first_pt = transfo(tab);
	return (NULL);
}
