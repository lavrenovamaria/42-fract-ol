/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_formulas.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:18 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:28:39 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	burning_ship(t_fractal *fractal)
{
	unsigned int	iteration;
	t_complex		z;
	t_complex		tmp_z;

	iteration = 0;
	z = init_complex(fractal->c.re, fractal->c.im);
	tmp_z = init_complex(z.re * z.re, z.im * z.im);
	while (tmp_z.re + tmp_z.im <= 4
		&& iteration < fractal->max_iter)
	{
		z.im = -fabs(z.re * z.im);
		z.im += z.im;
		z.im += fractal->c.im;
		z.re = tmp_z.re - tmp_z.im + fractal->c.re;
		tmp_z = init_complex(z.re * z.re, z.im * z.im);
		iteration++;
	}
	return (iteration);
}

unsigned int	julia(t_fractal *fractal)
{
	unsigned int	iteration;
	t_complex		z;
	t_complex		tmp_z;

	iteration = 0;
	z = init_complex(fractal->c.re, fractal->c.im);
	tmp_z = init_complex(z.re * z.re, z.im * z.im);
	while (tmp_z.re + tmp_z.im <= 4
		&& iteration < fractal->max_iter)
	{
		z.im = z.re * z.im;
		z.im += z.im;
		z.im += fractal->k.im;
		z.re = tmp_z.re - tmp_z.im + fractal->k.re;
		tmp_z = init_complex(z.re * z.re, z.im * z.im);
		iteration++;
	}
	return (iteration);
}

unsigned int	mandelbrot(t_fractal *fractal)
{
	unsigned int	iteration;
	t_complex		z;
	t_complex		tmp_z;

	iteration = 0;
	z = init_complex(fractal->c.re, fractal->c.im);
	tmp_z = init_complex(z.re * z.re, z.im * z.im);
	while (tmp_z.re + tmp_z.im < 4
		&& iteration < fractal->max_iter)
	{
		z.im = z.re * z.im;
		z.im += z.im;
		z.im += fractal->c.im;
		z.re = tmp_z.re - tmp_z.im + fractal->c.re;
		tmp_z = init_complex(z.re * z.re, z.im * z.im);
		iteration++;
	}
	return (iteration);
}
