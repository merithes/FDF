/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:51 by vboivin           #+#    #+#             */
/*   Updated: 2017/03/29 21:21:48 by vboivin          ###   ########.fr       */
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

static int		pull_event(int keycode)
{
	printf("%d\n", keycode);
	if (keycode == 53)
		exits(3);
	return(0);
}

void			set_coords(int coords[4], int xa, int ya, int xb, int yb)
{
	coords[XA] = xa;
	coords[YA] = ya;
	coords[XB] = xb;
	coords[YB] = yb;
}

int				main(int ac, char **av)
{
	int			fildes;
	int			test[4];
	void		*p[2];

	if (ac < 1)
		exits(2);
	if ((fildes = open(av[1], O_RDONLY)) <= 0)
		exits(fildes);
	set_coords(test, 0, 0, 100, 100);
	p[MLXID] = mlx_init();
	p[WINID] = mlx_new_window(p[MLXID], WIDTH, HEIGHT, TITLE);
	printf("ka\n");
	rekt_angle(p, test, BLUU);
	ft_drawline(p, test, CYAN);
	//set_menu(p);
	mlx_key_hook(p[WINID], pull_event, 0);
	mlx_loop(p[MLXID]);
}
