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

#include "hfdf.h"

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
	int			an;
	int			pta[2];
	int			ptb[2];

	pta[X] = D(a->x) - D(inf->len) / 2;
	pta[Y] = D(a->y) - D(inf->height) / 2;
	ptb[X] = D(b->x) - D(inf->len) / 2;
	ptb[Y] = D(b->y) - D(inf->height) / 2;
	an = inf->rotx;
	if (!(outp = malloc(T_SEG)))
		exits(1001);
	if (!a || !b)
	{
		free(outp);
		exits((!a) ? 1002 : 1003);
	}
	outp->xa = inf->margin_l + (pta[X] * COS(an) - pta[Y] * SIN(an));
	outp->ya = inf->margin_t + (pta[X] * SIN(an) + pta[Y] * COS(an)) - a->z * inf->z_coef;
	outp->xb = inf->margin_l + (ptb[X] * COS(an) - ptb[Y] * SIN(an));
	outp->yb = inf->margin_t + (ptb[X] * SIN(an) + ptb[Y] * COS(an)) - b->z * inf->z_coef;
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
	printf("sico(%f;%f)\n", SIN(inp->rotx), COS(inp->rotx));
	printf("marg:(%d;%d)\n", inp->margin_l, inp->margin_t);
	printf("maxdim:(%d:%d)\n", inp->len, inp->height);
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
