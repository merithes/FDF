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

t_info				*get_map(int fd, void *p[2])
{
	t_info			*outp;
	t_list			*tab;

	if (!(outp = malloc(sizeof(t_info))))
		exits(4, NULL);
	outp->mid = p[MLXID];
	outp->wid = p[WINID];
	outp->margin_t = MARGIN_TOP;
	outp->margin_l = MARGIN_LEF;
	outp->z_coef = Z_CO;
	outp->rotx = ROTX;
	outp->roty = ROTY;
	outp->len = 0;
	outp->zoom = sqrt(HEIGHT * HEIGHT + WIDTH * WIDTH) / (D_P * 2);
	outp->detail = 0;
	outp->fd = fd;
	outp->color = DEF_COL;
	if (!(tab = readall(fd)))
		return (0);
	if (check_range(tab) != 1 || (outp->height = into_int(tab) - 1) < 1)
		return (free_stuff(tab));
	if (!(outp->first_pt = to_pt_list(tab, outp)))
		return (free_stuff(tab));
	create_image(outp);
	return (outp);
}

void			free_all(t_info *inf)
{
	t_pt		*horizontal;
	t_pt		*vertical;
	t_pt		*swapper;

	vertical = inf->first_pt;
	while (vertical)
	{
		horizontal = vertical;
		while(horizontal)
		{
			swapper = horizontal->r;
			free(horizontal);
			horizontal = swapper;
		}
		vertical = vertical->b;
	}
}
