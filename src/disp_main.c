/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:32:18 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/26 19:47:20 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hFdF.h"

int				set_menu(void *p[2])
{
	int			coords[4];

	coords[XA] = 0;
	coords[YA] = TOP_M;
	coords[XB] = WIDTH;
	coords[YB] = HEIGHT;
	rekt_angle(p, coords, MENU_COLOR);
	return (0);
}

void			wipe_wi(void *p[2])
{
	int			coords[4];

	coords[XA] = 0;
	coords[YA] = 0;
	coords[XB] = WIDTH;
	coords[YB] = TOP_M;
	rekt_angle(p, coords, WALP_COLOR);
}

static t_seg	*set_seg(t_pt *a, t_pt *b, t_info *inf)
{
	t_seg		*outp;

	if (!(outp = malloc(T_SEG)))
		exits(1001);
	if (!a || !b)
	{
		free(outp);
		exits((!a) ? 1002 : 1003);
	}
	printf("%d\n", inf->rotx);
	outp->xa = inf->margin_l + D(a->x) + RX(PYTH(D(a->x), D(a->y)), inf->rotx);
	outp->ya = inf->margin_t + D(a->y) + RY(PYTH(D(a->x), D(a->y)), inf->rotx);
	outp->xb = inf->margin_l + D(b->x) + RX(PYTH(D(b->x), D(b->y)), inf->rotx);
	outp->yb = inf->margin_t + D(b->y) + RY(PYTH(D(b->x), D(b->y)), inf->rotx);
//	printf("(%d;%d)(%d;%d)\n", outp->xa, outp->ya, outp->xb, outp->yb);
	return (outp);
}

void			draw_grid(t_info *inp, int color)
{
	void		*p[2];
	t_pt		*scroll_v;
	t_pt		*scroll_h;

	p[WINID] = inp->wid;
	p[MLXID] = inp->mid;
//	wipe_wi(p);	
	if (!inp)
		return ;
	scroll_v = inp->first_pt;
	scroll_h = scroll_v;
	while (scroll_v)
	{
		while (scroll_h)
		{
			if (scroll_h->b)
				ft_drawline(p, set_seg(scroll_h, scroll_h->b, inp), color);
			if (scroll_h->r)
				ft_drawline(p, set_seg(scroll_h, scroll_h->r, inp), color);
			scroll_h = scroll_h->r;
		}
		scroll_v = scroll_v->b;
		scroll_h = scroll_v;
	}
//	set_menu(p);
}
