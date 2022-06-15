/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:09 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:27:22 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "control.h"

static double	interpolation_of(double start, double end, double zoom)
{
	return (start + ((end - start) * zoom));
}

int	zoom(int button, int x, int y, t_fractal *fractal)
{
	t_complex	mouse;
	double		zoom;

	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
	{
		mouse = init_complex(
				(double)x / (WIN_WIDTH / (fractal->max.re - fractal->min.re))
				+ fractal->min.re,
				(double)y / (WIN_HEIGHT / (fractal->max.im - fractal->min.im))
				* -1 + fractal->max.im);
		if (button == MOUSE_SCROLL_UP)
			zoom = 0.80;
		else
			zoom = 1.20;
		fractal->min.re = interpolation_of(mouse.re, fractal->min.re, zoom);
		fractal->min.im = interpolation_of(mouse.im, fractal->min.im, zoom);
		fractal->max.re = interpolation_of(mouse.re, fractal->max.re, zoom);
		fractal->max.im = interpolation_of(mouse.im, fractal->max.im, zoom);
		draw_fractal(fractal);
	}
	return (0);
}

int	julia_motion(int x, int y, t_fractal *fractal)
{
	if (!fractal->julia_block)
	{
		fractal->k = init_complex(4 * ((double)x / WIN_WIDTH - 0.5),
				4 * ((double)(WIN_HEIGHT - y) / WIN_HEIGHT - 0.5));
		draw_fractal(fractal);
	}
	return (0);
}
