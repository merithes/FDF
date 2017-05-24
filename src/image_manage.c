/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 17:27:47 by vboivin           #+#    #+#             */
/*   Updated: 2017/05/24 18:27:03 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

void				create_image(t_info *inf)
{
	t_img			*img;

	if (!(img = malloc(T_IMG)))
		exits(2, inf);
	img->pid = mlx_new_image(inf->mid, WIDTH, HEIGHT);
	img->str = mlx_get_data_addr(img->pid, &img->bpp, &img->len, &img->end);
	inf->img = img;
}

void				set_pixie(t_info *inf, int x, int y, unsigned int color)
{
	char			rgb[3];
	unsigned int	i;
	int				len;
	int				endi;

	endi = (!inf->img->end) ? -1 : 1;
	i = 0;
	len = inf->img->len / (inf->img->bpp / 8);
	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
		return ;
	while (i <= 3)
	{
		rgb[i++] = color % 256;
		color /= 256;
	}
	i = (y * len) + x;
	i = i * (inf->img->bpp / 8);
	inf->img->str[i + 0] = rgb[1 + endi];
	inf->img->str[i + 1] = rgb[1];
	inf->img->str[i + 2] = rgb[1 - endi];
}
