/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:36 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:28:18 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
{
	char	*dst;

	dst = fractal->image.addr + (y * fractal->image.line_length + x
			* (fractal->image.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

int	close_win(void *param)
{
	(void)param;
	exit(0);
}
