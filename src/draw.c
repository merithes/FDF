/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:36 by vboivin           #+#    #+#             */
/*   Updated: 2017/05/24 18:27:36 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

static int			color_mkr(t_seg *seg, t_info *inf, int x, int y)
{
	double			dist[2];
	double			ptv[2];
	int				outp;

	if (!inf->detail)
		return (inf->color);
	ptv[X] = seg->xb - seg->xa;
	ptv[Y] = seg->yb - seg->ya;
	dist[0] = PYTH(ptv[X], ptv[Y]);
	dist[1] = PYTH((double)x, (double)y);
	if (seg->xb == seg->xa)
		outp = (((y - seg->ya) / ptv[Y]) * seg->zb * inf->z_coef) +
					(((ptv[Y] - y + seg->ya) / ptv[Y]) * seg->za * inf->z_coef);
	else if (seg->yb == seg->ya)
		outp = (((x - seg->xa) / ptv[X]) * seg->zb * inf->z_coef) +
					(((ptv[X] - x + seg->xa) / ptv[X]) * seg->za * inf->z_coef);
	else
		outp = ((dist[1] / dist[0]) * seg->zb * inf->z_coef) +
					(((dist[0] - dist[1]) / dist[0]) * seg->za * inf->z_coef);
	outp *= (outp < 0) ? -1 : 1;
	outp = (outp > 108) ? inf->color - 216 : inf->color - outp * 2;
	return (outp);
}

static int			straight(t_info *inf, t_seg *seg)
{
	int				xy;

	if (seg->xa == seg->xb)
	{
		xy = seg->ya;
		while ((seg->ya > seg->yb && xy >= seg->yb) ||
				(seg->ya <= seg->yb && xy <= seg->yb))
		{
			set_pixie(inf, seg->xa, xy,
					color_mkr(seg, inf, seg->xa, xy));
			xy += (seg->ya > seg->yb) ? -1 : 1;
		}
	}
	else
	{
		xy = seg->xa;
		while ((seg->xa > seg->xb && xy >= seg->xb) ||
				(seg->xa <= seg->xb && xy <= seg->xb))
		{
			set_pixie(inf, xy, seg->ya, color_mkr(seg, inf, xy, seg->ya));
			xy += (seg->xa > seg->xb) ? -1 : 1;
		}
	}
	return (0);
}

static void			angled(t_info *inf, t_seg *seg)
{
	double			coef;
	int				i;
	int				y[2];

	coef = (double)(seg->yb - seg->ya) / (double)(seg->xb - seg->xa);
	i = 0;
	while (i + seg->xa <= seg->xb)
	{
		y[0] = coef * i;
		y[1] = coef * (i + 1);
		set_pixie(inf, i + seg->xa, y[0] + seg->ya,
			color_mkr(seg, inf, i, y[0]));
		while ((0 > coef && y[0] > y[1] && y[0] + seg->ya > seg->yb) ||
			(0 < coef && y[0] < y[1] && y[0] + seg->ya < seg->yb))
		{
			if (y[0] == y[1])
				break ;
			set_pixie(inf, i + seg->xa, y[0] + seg->ya,
				color_mkr(seg, inf, i, y[1]));
			y[0] += (coef >= 0) ? 1 : -1;
		}
		i++;
	}
}

/*
**  The following function draws a line between two given points.
*/

int					ft_drawline(t_info *inf, t_seg *seg)
{
	int				tmp;

	if (seg->xa > seg->xb)
	{
		tmp = seg->xa;
		seg->xa = seg->xb;
		seg->xb = tmp;
		tmp = seg->ya;
		seg->ya = seg->yb;
		seg->yb = tmp;
		tmp = seg->za;
		seg->za = seg->zb;
		seg->zb = tmp;
	}
	if (seg->xa == seg->xb || seg->ya == seg->yb)
		straight(inf, seg);
	else
		angled(inf, seg);
	free(seg);
	return (0);
}

/*
** Rectangles. Simple enough?
*/

int					rekt_angle(t_info *inf, int rec[4], int color)
{
	int				xa;
	int				xb;
	int				ya;
	int				yb;

	xa = (rec[XA] > rec[XB]) ? rec[XB] : rec[XA];
	ya = (rec[YA] > rec[YB]) ? rec[YB] : rec[YA];
	xb = (rec[XA] > rec[XB]) ? rec[XA] : rec[XB];
	yb = (rec[YA] > rec[YB]) ? rec[YA] : rec[YB];
	while (xa <= xb)
	{
		while (ya <= yb)
		{
			set_pixie(inf, xa, ya, color);
			ya++;
		}
		ya = (rec[YA] > rec[YB]) ? rec[YB] : rec[YA];
		xa++;
	}
	return (0);
}
