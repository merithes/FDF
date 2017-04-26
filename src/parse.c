/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/26 19:26:27 by vboivin          ###   ########.fr       */
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

static void			set_matrix(t_info *inp)
{
	int				i1;
	int				i2;
	int				i3;

	i1 = -1;
	while (++i1 < 3 && !(i2 = -1))
		while (++i2 < 3 && !(i3 = -1))
			while (++i3 < 2)
				inp->mat[i1][i2][i3] = 0;
}

t_info				*get_map(int fd, void *p[2])
{
	t_info			*outp;
	t_list			*tab;

	if (!(outp = malloc(sizeof(t_info))))
		exits(4);
	outp->mid = p[MLXID];
	outp->wid = p[WINID];
	outp->margin_t = MARGIN_TOP;
	outp->margin_l = MARGIN_LEF;
	outp->z_coef = Z_CO;
	outp->roty = ROT;
	outp->rotx = ROT;
	if (!(tab = readall(fd)))
		return (0);
	if (check_range(tab) != 1 || into_int(tab) != 1)
		return (free_stuff(tab));
	if (!(outp->first_pt = to_pt_list(tab)))
		return (free_stuff(tab));
	set_matrix(outp);
	return (outp);
}
