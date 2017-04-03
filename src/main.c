/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 12:37:51 by vboivin           #+#    #+#             */
/*   Updated: 2017/04/03 15:56:31 by vboivin          ###   ########.fr       */
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

static int		pull_event(int keycode)
{
	printf("%d\n", keycode);
	if (keycode == 53)
		exits(3);
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
	printf("ka\n");
	set_menu(p);
	printf("kb\n");
	if (!(inf = get_map(fildes, p)))
		exits(1000);
	printf("kc\n");
	mlx_key_hook(p[WINID], pull_event, 0);
	mlx_loop(p[MLXID]);
}
