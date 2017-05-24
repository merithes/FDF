/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vboivin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:46:20 by vboivin           #+#    #+#             */
/*   Updated: 2017/05/24 18:26:19 by vboivin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HFDF_H
# define HFDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>

/*
** WINDOW PROPERTIES
*/
# define TITLE "title goes there"
# define WIDTH 1920
# define HEIGHT 1080
# define TOP_SP HEIGHT -HEIGHT_M

/*
** COLORS
*/
# define WHITE 0xFFFFFF
# define LI_RED 0xFE3333

# define BLUU 255
# define REDD 0xFE0000
# define GRNN 0x00FE00
# define YELO 0xFEFE00

# define BLUE 0x4040FE
# define CYAN 0x00d5d8
# define ORAN 0xFE8800

# define YEL_D 0X333300

/*
** OTHERS[DATA]
*/
# define XA 0
# define YA 1
# define XB 2
# define YB 3

# define X 0
# define Y 1
# define Z 2

# define MLXID 0
# define WINID 1

# define END_F 1471471473
# define END_S -1791791794

# define T_PT sizeof(t_pt)
# define T_SEG sizeof(t_seg)
# define T_IMG sizeof(t_img)
# define COS(angleDegrees) ((cos((angleDegrees) * M_PI / 180)))
# define SIN(angleDegrees) ((sin((angleDegrees) * M_PI / 180)))
# define RX(pt, a) (pt * (COS(a) - SIN(a)))
# define RY(pt, a) (pt * (SIN(a) + COS(a)))
# define PYTH(a, b) (sqrt(a * a + b * b))
# define ABS(a) (sqrt (a * a))

/*
** OTHERS[Preferences]
*/
# define HEIGHT_M 300
# define TOP_M HEIGHT - HEIGHT_M
# define MENU_COLOR LI_RED
# define WALP_COLOR 0x000033

# define DEF_COL CYAN
# define DEF_COL_SEC 0xd510d8

# define D_P 20
# define D(a) (a * D_P)
# define MARGIN_TOP HEIGHT/2
# define MARGIN_LEF WIDTH/2
# define Z_CO 0

# define ROTX 0
# define ROTY 0

# define Z_DIFF 1
# define ANG_DIFF 1
# define MAR_DIFF 10
# define ZOOM_DIFF 1

# define DETMODE 0
# define SPACE 30
# define HEIGHT_W 15

/*
** TYPEDEF(s)
*/

typedef struct		s_pt
{
	int				x;
	int				y;
	int				z;
	int				pos[2];
	struct s_pt		*r;
	struct s_pt		*b;
}					t_pt;

typedef struct		s_seg
{
	int				xa;
	int				ya;
	int				za;
	int				xb;
	int				yb;
	int				zb;
}					t_seg;

typedef struct		s_img
{
	void			*pid;
	char			*str;
	int				end;
	int				bpp;
	int				len;
}					t_img;

typedef struct		s_info
{
	t_img			*img;
	int				fd;
	int				color;
	int				margin_t;
	int				margin_l;
	int				z_coef;
	int				rotx;
	int				roty;
	void			*mid;
	void			*wid;
	struct s_pt		*first_pt;
	int				len;
	int				height;
	int				zoom;
	int				detail;
}					t_info;

/*
** PROTOTYPES
*/

void				free_all(t_info *inf);
void				set_pt(t_pt *inp, int a, int b, int c);
t_pt				*chain_layer(int *inp, int y, t_info *toset);
int					ft_drawline(t_info *inf, t_seg *seg);
void				set_coords(int inp[4], int xa, int ya, int xb, int yb);
int					rekt_angle(t_info *inf, int coords[4], int color);
int					set_menu(t_info *inf);
t_info				*get_map(int fildes, void *pointers[2]);
void				exits(int exnu, t_info *inf);
t_pt				*transfo(t_list *inp);
int					check_range(t_list *inp);
int					into_int(t_list *inp);
t_info				*free_stuff(t_list *inp);
t_pt				*to_pt_list(t_list *inp, t_info *toset);
void				draw_grid(t_info *inp);
void				put_word(t_info *inf, int x, int y, char *inp);
void				create_image(t_info *inf);
void				set_pixie(t_info *inf, int x, int y, unsigned int color);

#endif
