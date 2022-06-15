/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:31 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:32:12 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static unsigned int	(*get_fractal(char *name)) (t_fractal *fractal)
{
	if (!ft_strcmp(name, "Mandelbrot"))
		return (&mandelbrot);
	else if (!ft_strcmp(name, "Julia"))
		return (&julia);
	else if (!ft_strcmp(name, "Burning Ship"))
		return (&burning_ship);
	else
		return (0);
}

void	set_defaults(t_fractal *fractal)
{
	fractal->max_iter = 50;
	fractal->min = init_complex(-2.0, -2.0);
	if (WIN_HEIGHT > WIN_WIDTH)
	{
		fractal->max.re = 2.0;
		fractal->max.im = fractal->min.im
			+ (fractal->max.re - fractal->min.re) * WIN_HEIGHT / WIN_WIDTH;
	}
	else
	{
		fractal->max.im = 2.0;
		fractal->max.re = fractal->min.re
			+ (fractal->max.im - fractal->min.im) * WIN_WIDTH / WIN_HEIGHT;
	}
	fractal->k = init_complex(-0.4, 0.6);
	fractal->color_shift = 0;
	fractal->bright_shift = 0;
}

static void	init_fractal(t_fractal *fractal, char *name)
{
	fractal->mlx = mlx_init();
	fractal->win = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT, name);
	if (!fractal->win)
		exit(-1);
	fractal->image.img = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fractal->image.img)
		exit(-1);
	fractal->image.addr = mlx_get_data_addr(
			fractal->image.img, &(fractal->image.bits_per_pixel),
			&(fractal->image.line_length), &(fractal->image.endian));
	set_defaults(fractal);
	fractal->julia_block = 1;
	fractal->formula = get_fractal(name);
	mlx_hook(fractal->win, 2, 1L << 0, key_press, fractal);
	mlx_hook(fractal->win, 17, 0, close_win, fractal);
	mlx_mouse_hook(fractal->win, zoom, fractal);
	if (!ft_strcmp(name, "Julia"))
		mlx_hook(fractal->win, 6, 1L << 6, julia_motion, fractal);
}

static void	help(void)
{
	write(1, " ____________________________________________________ \n", 55);
	write(1, "|                      Fract'ol                      |\n", 55);
	write(1, "|____________________________________________________|\n", 55);
	write(1, "|                      Mandelbrot                    |\n", 55);
	write(1, "|                      Julia                         |\n", 55);
	write(1, "|                      Burning Ship                  |\n", 55);
	write(1, "|____________________________________________________|\n", 55);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc == 2 && get_fractal(argv[1]))
	{
		init_fractal(&fractal, argv[1]);
		draw_fractal(&fractal);
		mlx_loop(fractal.mlx);
	}
	else
		help();
	return (0);
}
