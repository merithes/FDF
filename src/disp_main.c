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

int				set_menu(t_info *inf)
{
	int			y;
	void		*p[2];

	p[MLXID] = inf->mid;
	p[WINID] = inf->wid;
	y = HEIGHT - 20;
	put_word(p, 5, y - 75, "Move: ZQSD/WASD");
	put_word(p, 5, y - 60, "Zoom: WX/ZX");
	put_word(p, 5, y - 45, "Rotate X: left/right arrows");
	put_word(p, 5, y - 30, "Rotate Y: top/bottom page");
	put_word(p, 5, y - 15, "Grow height: up/down arrows");
	put_word(p, 5, y, "Activate polygon option: *");
	return (0);
}

static void		set_coordz(t_seg *inp, t_info *inf, double a[2], double b[2])
{
	int			an[3];

	an[X] = inf->rotx;
	an[Y] = inf->roty;
	an[Z] = inf->rotz;
	inp->xa = inf->margin_l + (a[X] * COS(an[X]) - a[Y] * SIN(an[X]));
	inp->ya = inf->margin_t + ((a[X] * SIN(an[X]) + a[Y] * COS(an[X]))) *
				COS(an[Y]) - a[Z] * inf->z_coef * SIN(an[Y]);
	inp->za = a[Z];
	inp->xb = inf->margin_l + (b[X] * COS(an[X]) - b[Y] * SIN(an[X]));
	inp->yb = inf->margin_t + ((b[X] * SIN(an[X]) + b[Y] * COS(an[X]))) *
				COS(an[Y]) - b[Z] * inf->z_coef * SIN(an[Y]);
	inp->zb = b[Z];
}

static t_seg	*set_seg(t_pt *a, t_pt *b, t_info *inf)
{
	t_seg		*outp;
	double		pta[3];
	double		ptb[3];

	pta[X] = inf->zoom * a->x - inf->len * inf->zoom / 2;
	pta[Y] = inf->zoom * a->y - inf->height * inf->zoom / 2;
	pta[Z] = (double)(inf->zoom * a->z)/32;
	ptb[X] = inf->zoom * b->x - inf->len * inf->zoom / 2;
	ptb[Y] = inf->zoom * b->y - inf->height * inf->zoom / 2;
	ptb[Z] = (double)(inf->zoom * b->z)/32;
	if (!(outp = malloc(T_SEG)))
		exits(1001);
	if (!a || !b)
	{
		free(outp);
		exits((!a) ? 1002 : 1003);
	}
	set_coordz(outp, inf, pta, ptb);
	return (outp);
}


void			draw_tool(void *p, t_pt *pt, int col, t_info *inf)
{
	int			i;

	i = 0;
	if (pt->b)
	{
		ft_drawline(p, set_seg(pt, pt->b, inf), col);
		if (inf->detail && pt->b->r && pt->r && inf->z_coef && inf->roty &&
				((pt->z != pt->b->z && pt->z != pt->r->z) ||
					(pt->b->r->z != pt->b->z && pt->b->r->z != pt->r->z)) &&
						(((pt->b->z != pt->r->z && pt->z != pt->b->r->z) ||
							(pt->r->z == pt->b->z &&
								pt->b->r->z - pt->z != pt->z - pt->r->z))))
			ft_drawline(p, set_seg(pt, pt->b->r, inf), col + i++);
	}
	if (pt->r)
	{
		ft_drawline(p, set_seg(pt, pt->r, inf), col);
		if (inf->detail && pt->r->b && pt->b && inf->z_coef && inf->roty &&
				((pt->r->z != pt->r->b->z && pt->r->z != pt->z) ||
					(pt->b->z != pt->r->b->z && pt->b->z != pt->z)) &&
						(((pt->z != pt->r->b->z && pt->b->z != pt->r->z) ||
							(pt->z == pt->b->r->z &&
								pt->z - pt->r->z != pt->b->z - pt->z))) && !i)
			ft_drawline(p, set_seg(pt->b, pt->r, inf), col);
	}
}

void			draw_grid(t_info *inp, int color)
{
	void		*p[2];
	t_pt		*scroll_v;
	t_pt		*scroll_h;

	p[WINID] = inp->wid;
	p[MLXID] = inp->mid;
	if (!inp)
		return ;
	scroll_v = inp->first_pt;
	scroll_h = scroll_v;
	while (scroll_v)
	{
		while (scroll_h)
		{
			draw_tool(p, scroll_h, color, inp);
			scroll_h = scroll_h->r;
		}
		scroll_v = scroll_v->b;
		scroll_h = scroll_v;
	}
}
