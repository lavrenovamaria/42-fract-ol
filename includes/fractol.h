/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:40 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/11 14:13:51 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# define WIN_WIDTH		800
# define WIN_HEIGHT		800
# define UI	unsigned int

# include "../libft/libft.h"
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>

# include <string.h>
# include <inttypes.h>
# include <stdlib.h>

typedef struct s_complex
{
	double			re;
	double			im;
}				t_complex;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_fractal
{
	void			*mlx;
	void			*win;
	t_image			image;
	unsigned int	max_iter;
	t_complex		min;
	t_complex		max;
	t_complex		factor;
	t_complex		c;
	t_complex		k;
	char			julia_block;
	unsigned char	color_shift;
	double			bright_shift;
	unsigned int	((*formula)(struct	s_fractal *fractal));
}				t_fractal;

void			set_defaults(t_fractal *fractal);
t_complex		init_complex(double re, double im);
void			my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color);

void			draw_fractal(t_fractal *fractal);
void			draw_help(t_fractal *fractal);

unsigned int	mandelbrot(t_fractal *fractal);
unsigned int	julia(t_fractal *fractal);
unsigned int	burning_ship(t_fractal *fractal);

int				get_color(unsigned int iteration, t_fractal *fractal);

int				close_win(void *param);
int				key_press(int key, t_fractal *fractal);
int				zoom(int button, int x, int y, t_fractal *fractal);
int				julia_motion(int x, int y, t_fractal *fractal);

#endif
