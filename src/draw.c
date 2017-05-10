/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:36 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/26 19:25:39 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

static int			color_mkr(t_seg *seg, t_info *inf, int x, int y)
{
	double			dist[2];
	double			ptv[2];
	int				outp;

	if (inf->ghost == 1)
		return (GHOST_COL);
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

void				put_word(void *p[2], int x, int y, char *inp)
{
	int				square[4];

	square[XA] = x;
	square[YA] = y;
	square[XB] = ft_strlen(inp) * 6.6;
	square[YB] = y + 10;

	rekt_angle(p, square, 0xFEFEFE);
	mlx_string_put(p[0], p[1], x + 1, y + 10, 0, inp);
}

static int			straight(void *p[2], t_info *inf, t_seg *seg)
{
	int				xy;

	if (seg->xa == seg->xb)
	{
		xy = seg->ya;
		while ((seg->ya > seg->yb && xy >= seg->yb) ||
				(seg ->ya <= seg->yb && xy <= seg->yb))
		{
			mlx_pixel_put(p[MLXID], p[WINID], seg->xa, xy,
					color_mkr(seg, inf, seg->xa, xy));
			xy += (seg->ya > seg->yb) ? -1 : 1;
		}
	}
	else
	{
		xy = seg->xa;
		while ((seg->xa > seg->xb && xy >= seg->xb) ||
				(seg ->xa <= seg->xb && xy <= seg->xb))
		{
			mlx_pixel_put(p[MLXID], p[WINID], xy, seg->ya,
					color_mkr(seg, inf, xy, seg->ya));
			xy += (seg->xa > seg->xb) ? -1 : 1;
		}
	}
	return (0);
}

static void			angled(void *p[2], t_info *inf, t_seg *seg)
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
		mlx_pixel_put(p[MLXID], p[WINID], i + seg->xa, y[0] + seg->ya,
			color_mkr(seg, inf, i, y[0]));
		while ((0 > coef && y[0] > y[1] && y[0] + seg->ya > seg->yb) ||
			(0 < coef && y[0] < y[1] && y[0] + seg->ya < seg->yb))
		{
			if (y[0] == y[1])
				break ;
			mlx_pixel_put(p[MLXID], p[WINID], i + seg->xa, y[0] + seg->ya,
				color_mkr(seg, inf, i, y[1]));
			y[0] += (coef >= 0) ? 1 : -1;
		}
		i++;
	}
}

/*
 **  The following function draws a line between two given points.
 */

int					ft_drawline(void *p[2], t_info *inf, t_seg *seg)
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
		straight(p, inf, seg);
	else
		angled(p, inf, seg);
	free(seg);
	return (0);
}

/*
 ** Rectangles. Simple enough?
 */

int					rekt_angle(void *p[2], int rec[4], int color)
{
	int				xa;
	int				xb;
	int				ya;
	int				yb;

	(void)p;
	xa = (rec[XA] > rec[XB]) ? rec[XB] : rec[XA];
	ya = (rec[YA] > rec[YB]) ? rec[YB] : rec[YA];
	xb = (rec[XA] > rec[XB]) ? rec[XA] : rec[XB];
	yb = (rec[YA] > rec[YB]) ? rec[YA] : rec[YB];
	while (xa <= xb)
	{
		while (ya <= yb)
		{
			mlx_pixel_put(p[MLXID], p[WINID], xa, ya, color);
			ya++;
		}
		ya = (rec[YA] > rec[YB]) ? rec[YB] : rec[YA];
		xa++;
	}
	return (0);
}
