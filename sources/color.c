/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:47:59 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:29:39 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	rainbow(unsigned int iteration, t_fractal *fractal)
{
	int		color;
	int		i;

	(void)fractal;
	i = iteration;
	color = (unsigned char)(sin(0.3 * (double)i + 0.0) * 127.0 + 128.0);
	color <<= 8;
	color += (unsigned char)(sin(0.3 * (double)i + 2.0) * 127.0 + 128.0);
	color <<= 8;
	color += (unsigned char)(sin(0.3 * (double)i + 4.0) * 127.0 + 128.0);
	return (color);
}

int	aqua_blue(unsigned int iteration, t_fractal *fractal)
{
	int		color;
	int		i;

	(void)fractal;
	i = iteration;
	color = (unsigned char)(sin(0.3 * (double)i));
	color <<= 8;
	color += (unsigned char)(sin(0.3 * (double)i + 3) * 127 + 128);
	color <<= 8;
	color += (unsigned char)(sin(0.3 * (double)i + 3) * 127 + 128);
	return (color);
}

int	nikitos_blue(unsigned int iteration, t_fractal *fractal)
{
	double	t;
	int		color;

	if (iteration == fractal->max_iter)
		return (0);
	t = (double)iteration / fractal->max_iter;
	color = (unsigned char)(t / ((fractal->color_shift + 0) % 3 + 1) * 255);
	color <<= 8;
	color += (unsigned char)(t / ((fractal->color_shift + 1) % 3 + 1) * 255);
	color <<= 8;
	color += (unsigned char)(t / ((fractal->color_shift + 2) % 3 + 1) * 255);
	return (color);
}

int	get_color(unsigned int iteration, t_fractal *fractal)
{
	if (fractal->color_shift == 0)
		return (rainbow(iteration, fractal));
	else if (fractal->color_shift == 1)
		return (aqua_blue(iteration, fractal));
	else if (fractal->color_shift == 2)
		return (nikitos_blue(iteration, fractal));
	return (0);
}
