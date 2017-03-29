/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:36 by vboivin           #+#    #+#             */
/*   Updated: 2017/03/29 21:21:40 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hFdF.h"

static int			straight(void *p[2], int li[4], int color)
{
	int				xy;

	if (li[XA] == li[XB])
	{
		xy = (li[YA] > li[YB] ? li[YB] : li[YA]);
		while (xy <= li[YA] || xy <= li[YB])
			mlx_pixel_put(p[MLXID], p[WINID], li[XA], xy++, color);
		return (1);
	}
	xy = (li[XA] > li[XB] ? li[XB] : li[XA]);
	while (xy < li[XA] || xy < li[XB])
		mlx_pixel_put(p[MLXID], p[WINID], xy++, li[YA], color);
	return (2);
}

static void			angled(void *p[2], int li[4], int color)
{
	double			coef;
	int				i;
	int				y;

	coef = (double)(li[YB] - li[YA]) / (double)(li[XB] - li[XA]);
	i = 0;
	while (i + li[XA] <= li[XB])
	{
		y = coef * i;
		mlx_pixel_put(p[MLXID], p[WINID], i + li[XA], y + li[YA], color);
		i++;
	}
	printf("%f\n", coef);
}

/*
**  The following function draws a line between two given points.
*/

int					ft_drawline(void *p[2], int li[4], int color)
{
	int				tmp;

	if (li[XA] > li[XB])
	{
		tmp = li[XA];
		li[XA] = li[XB];
		li[XB] = tmp;
		tmp = li[YA];
		li[YA] = li[YB];
		li[YB] = tmp;
	}
	if (li[XA] == li[XB] && li[YA] == li[YB])
		mlx_pixel_put(p[MLXID], p[WINID], li[XA], li[YA], color);
	else if (li[XA] == li[XB] || li[YA] == li[YB])
		straight(p, li, color);
	else
		angled(p, li, color);
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

	printf("a\n");
	color++;
	(void)p;
	xa = (rec[XA] > rec[XB]) ? rec[XB] : rec[XA];
	ya = (rec[YA] > rec[YB]) ? rec[YB] : rec[YA];
	xb = (rec[XA] > rec[XB]) ? rec[XA] : rec[XB];
	yb = (rec[YA] > rec[YB]) ? rec[YA] : rec[YB];
	printf("%d, %d, %d, %d.", xa, ya, xb, yb);
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
	printf("a\n");
	return (0);
}
