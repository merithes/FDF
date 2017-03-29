/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:51 by vboivin           #+#    #+#             */
/*   Updated: 2017/03/29 19:34:31 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hFdF.h"

void			exits(int exnu)
{
	if (exnu == 2)
		ft_putstr("You just forgot to put any arguments. Smartass\n");
	else if (exnu == 3)
	{
		ft_putstr("Y u leav :(\n");
		exit(3);
	}
	else
	exit(exnu);
}

static int		pull_event(int keycode, int *key)
{
	return((*key = keycode));
}

void			set_coords(int coords[4], int xa, int ya, int xb, int yb)
{
	coords[XA] = xa;
	coords[YA] = ya;
	coords[XB] = xb;
	coords[YB] = yb;
}

int				main(void ac, char **av)
{
	int			fildes;
	void		*p[2];
	int			key;

	if (ac < 1)
		exits(2);
	if ((fildes = open(av[1], O_RDONLY)) <= 0)
		exits(fildes);
	p[MLXID] = mlx_init();
	p[WINID] = mlx_new_window(p[MLXID], WIDTH, HEIGHT, TITLE);
	mlx_key_hook(p[WINID], pull_event, &key);
	mlx_loop(p[MLXID]);
}
