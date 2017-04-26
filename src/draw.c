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

#include "hFdF.h"

static int			straight(void *p[2], t_seg *seg, int color)
{
	int				xy;

	if (seg->xa == seg->xb)
	{
		xy = (seg->ya > seg->yb ? seg->yb : seg->ya);
		while (xy <= seg->ya || xy <= seg->yb)
			mlx_pixel_put(p[MLXID], p[WINID], seg->xa, xy++, color);
		return (1);
	}
	xy = (seg->xa > seg->xb ? seg->xb : seg->xa);
	while (xy < seg->xa || xy < seg->xb)
		mlx_pixel_put(p[MLXID], p[WINID], xy++, seg->ya, color);
	return (2);
}

static void			angled(void *p[2], t_seg *seg, int col)
{
	double			coef;
	int				i;
	int				y;
	int				ypp;

	coef = (double)(seg->yb - seg->ya) / (double)(seg->xb - seg->xa);
	i = 0;
	while (i + seg->xa <= seg->xb)
	{
		y = coef * i;
		ypp = coef * (i + 1);
		mlx_pixel_put(p[MLXID], p[WINID], i + seg->xa, y + seg->ya, col);
		while ((0 > coef && y > ypp && y + seg->ya > seg->yb) ||
			(0 < coef && y < ypp && y + seg->ya < seg->yb))
		{
			if (y == ypp)
				break ;
			mlx_pixel_put(p[MLXID], p[WINID], i + seg->xa, y + seg->ya, col);
			y += (coef >= 0) ? 1 : -1;
		}
		i++;
	}
}

/*
 **  The following function draws a line between two given points.
 */

int					ft_drawline(void *p[2], t_seg *seg, int color)
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
	}
	if (seg->xa == seg->xb && seg->ya == seg->yb)
	{
		mlx_pixel_put(p[MLXID], p[WINID], seg->xa, seg->ya, color);
	}
	else if (seg->xa == seg->xb || seg->ya == seg->yb)
	{
		straight(p, seg, color);
	}
	else
	{
		angled(p, seg, color);
	}
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
