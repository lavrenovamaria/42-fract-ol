/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:14 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:32:27 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_fractal(t_fractal *fractal)
{
	int		x;
	int		y;
	int		color;

	fractal->factor = init_complex((
				fractal->max.re - fractal->min.re) / WIN_WIDTH,
			(fractal->max.im - fractal->min.im) / WIN_HEIGHT);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		fractal->c.im = fractal->max.im - y * fractal->factor.im;
		x = 0;
		while (x < WIN_WIDTH)
		{
			fractal->c.re = fractal->min.re + x * fractal->factor.re;
			color = get_color(fractal->formula(fractal), fractal);
			my_mlx_pixel_put(fractal, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->win,
		fractal->image.img, 0, 0);
}
