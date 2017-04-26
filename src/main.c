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

static void		redraw_quad(t_info *inf, int keycode)
{
	draw_grid(inf, BLUU - 1 );
	if (keycode == 125 || keycode == 126)
		inf->z_coef += (keycode == 126) ? -1 : 1;
	if (keycode == 123 || keycode == 124)
		inf->rotx = (keycode == 123) ?
			(inf->rotx - ANG_DIFF) % 360 : (inf->rotx + ANG_DIFF) % 360;
	if (keycode == 6 || keycode == 7)
		inf->roty += (keycode == 6) ?
			(inf->rotx - ANG_DIFF % 360) : (inf->rotx + ANG_DIFF) % 360;
	if (keycode == 0 || keycode == 2)
		inf->margin_l += (keycode == 0) ? -MAR_DIFF: MAR_DIFF;
	if (keycode == 1 || keycode == 13)
		inf->margin_t += (keycode == 13) ? -MAR_DIFF: MAR_DIFF;
	draw_grid(inf, GRIDCOL);
}

static int		pull_event(int keycode, void *param)
{
	t_info		*inf;

	inf = (t_info *)param;
	if (keycode == 53)
		exits(3);
	if ((123 <= keycode && keycode <= 126) || (0 <= keycode && keycode <= 2) ||
			keycode == 13 || keycode == 7 || keycode == 6)
		redraw_quad(inf, keycode);
	printf("key #%d\n", keycode);
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
	printf("a:%d\n", mlx_key_hook(p[WINID], pull_event, inf));
	printf("b:%d\n", mlx_loop(p[MLXID]));
}
