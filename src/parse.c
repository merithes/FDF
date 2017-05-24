/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:40:29 by vboivin           #+#    #+#             */
/*   Updated: 2017/05/24 18:55:28 by vboivin          ###   ########.fr       */
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
	outp->zoom = (PYTH(HEIGHT, WIDTH) / (2 * D_P));
	outp->detail = 0;
	outp->fd = fd;
	outp->color = DEF_COL;
	if (!(tab = readall(fd)))
		return (0);
	if (check_range(tab) != 1 || (outp->height = into_int(tab) - 1) < 1)
		return (free_stuff(tab));
	if (!(outp->first_pt = to_pt_list(tab, outp)))
		return (free_stuff(tab));
	return (outp);
}

void				free_all(t_info *inf)
{
	t_pt			*horizontal;
	t_pt			*vertical;
	t_pt			*swapper;

	vertical = inf->first_pt;
	while (vertical)
	{
		horizontal = vertical;
		while (horizontal)
		{
			swapper = horizontal->r;
			free(horizontal);
			horizontal = swapper;
		}
		vertical = vertical->b;
	}
}

static void			link_chain(t_pt *inp)
{
	t_pt			*scroller_u;
	t_pt			*scroller_d;

	while (inp)
	{
		scroller_u = inp;
		scroller_d = inp->b;
		while (scroller_u)
		{
			scroller_u->b = scroller_d;
			scroller_u = scroller_u->r;
			if (scroller_d)
				scroller_d = scroller_d->r;
		}
		inp = inp->b;
	}
}

t_pt				*to_pt_list(t_list *inp, t_info *toset)
{
	t_pt			*first;
	t_pt			*layers;
	t_list			*prev;
	int				i;

	i = 0;
	prev = inp;
	if (!(first = chain_layer((int *)inp->content, 0, toset)))
		return (0);
	inp = inp->next;
	layers = first;
	while (inp && ++i)
	{
		if (!(layers->b = chain_layer((int *)inp->content, i, toset)))
			return (0);
		layers = layers->b;
		free(prev);
		prev = inp;
		inp = inp->next;
	}
	link_chain(first);
	return (first);
}
