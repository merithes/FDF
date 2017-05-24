/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 19:31:46 by vboivin           #+#    #+#             */
/*   Updated: 2017/05/24 17:31:46 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

void				set_pt(t_pt *inp, int a, int b, int c)
{
	inp->x = a;
	inp->y = b;
	inp->z = c;
	inp->r = NULL;
	inp->b = NULL;
}

t_pt				*chain_layer(int *inp, int y, t_info *toset)
{
	t_pt			*outp;
	t_pt			*scroll;
	t_pt			*prev;
	int				i;

	i = 0;
	while (inp[i] != END_F && inp[i + 1] != END_S)
	{
		prev = scroll;
		if (!(scroll = malloc(T_PT)))
			return (NULL);
		if (i == 0)
			outp = scroll;
		else
			prev->r = scroll;
		set_pt(scroll, i, y, inp[i]);
		i++;
	}
	if (toset->len < i)
		toset->len = i - 1;
	if (inp)
		free(inp);
	return (outp);
}

int					set_menu(t_info *inf)
{
	int				y;
	int				i;

	i = 5;
	y = HEIGHT - 500;
	put_word(inf, 5, y - i-- * SPACE, "Move: ZQSD/WASD");
	put_word(inf, 5, y - i-- * SPACE, "Zoom: WX/ZX");
	put_word(inf, 5, y - i-- * SPACE, "Rotate X: left/right arrows");
	put_word(inf, 5, y - i-- * SPACE, "Rotate Y: top/bottom page");
	put_word(inf, 5, y - i-- * SPACE, "Grow height: up/down arrows");
	put_word(inf, 5, y - i-- * SPACE, "Activate polygon option: *");
	return (0);
}

void				put_word(t_info *inf, int x, int y, char *inp)
{
	int				square[4];

	square[XA] = x;
	square[YA] = y;
	square[XB] = ft_strlen(inp) * 10.5;
	square[YB] = y + HEIGHT_W;
	rekt_angle(inf, square, 0xFEFEFE);
	mlx_string_put(inf->mid, inf->wid, x + 1, y - 3, 0x006e6e, inp);
}
