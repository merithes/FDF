/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:51 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/26 19:27:10 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hfdf.h"

int				remem(int inp_fd, int boo)
{
	static int	fd = -15;

	if (boo == 1)
		fd = inp_fd;
	else
		return (fd);
	return (-1);
}

void			exits(int exnu)
{
	if (exnu == 2)
		ft_putstr("You just forgot to put any arguments. Smartass\n");
	else if (exnu == 3)
		ft_putstr("Y u leav :(\n");
	else if (exnu == 4)
		ft_putstr("Memory Allocation error (5)\n");
	else if (exnu == 5)
		ft_putstr("GNL failed, somehow... Curse you GNL !");
	else if (exnu == 6)
		ft_putstr("Invalid input\n");
	else
	{
		ft_putstr("error #");
		ft_putnbr(exnu);
		ft_putchar('\n');
	}
	if (!(remem(0, 0) == -1))
		close(remem(0, 0));
	exit(exnu);
}

static void		redraw_quad(t_info *inf, int kc)
{
	draw_grid(inf, BLUU - 221);
	if (kc == 125 || kc == 126 || kc == 65362 || kc == 65364)
		inf->z_coef += (kc == 126 || kc == 65364) ? -Z_DIFF : Z_DIFF;
	if (kc == 65365 ||kc == 65366)
		inf->roty = (kc == 65366) ?
			(inf->roty - ANG_DIFF)%360 : (inf->roty + ANG_DIFF)%360;
	if (kc == 123 || kc == 124 || kc == 65361 || kc == 65363)
		inf->rotx = (kc == 123 || kc == 65361) ?
			(inf->rotx - ANG_DIFF) % 360 : (inf->rotx + ANG_DIFF) % 360;
	if (kc == 0 || kc == 2 || kc == 113 ||kc == 100)
		inf->margin_l += (kc == 0 ||kc == 113) ? -MAR_DIFF: MAR_DIFF;
	if (kc == 1 || kc == 13 || kc == 115 || kc == 122)
		inf->margin_t += (kc == 13 || kc == 122) ? -MAR_DIFF : MAR_DIFF;
	if (kc == 119 || kc == 120)
		inf->zoom += (kc == 119) ? -ZOOM_DIFF : ZOOM_DIFF;
	if (kc == 60 || kc == 65506)
		inf->rotz = (kc == 60) ?
			(inf->rotz - ANG_DIFF) % 360 : (inf->rotz + ANG_DIFF) % 360;
	if (kc == 42)
		inf->detail = (inf->detail + 1) % 2;
	if (inf->zoom < 0)
		inf->zoom = 0;
	draw_grid(inf, GRIDCOL);
	set_menu(inf);
}

static int		pull_event(int keycode, void *param)
{
	t_info		*inf;

	inf = (t_info *)param;
	if (keycode == 53 || keycode == 65307)
		exits(3);
	redraw_quad(inf, keycode);
	return (0);
}

int				main(int ac, char **av)
{
	int			fildes;
	void		*p[2];
	t_info		*inf;

	if (ac < 1)
		exits(2);
	if ((fildes = open(av[1], O_RDONLY)) <= 0)
		exits(6);

	remem(fildes, 1);
	p[MLXID] = mlx_init();
	p[WINID] = mlx_new_window(p[MLXID], WIDTH, HEIGHT, TITLE);
	if (!(inf = get_map(fildes, p)))
		exits(1000);
	draw_grid(inf, GRIDCOL);
}
