/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_keyboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wrickard <wrickard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 22:48:05 by wrickard          #+#    #+#             */
/*   Updated: 2021/10/10 15:29:07 by wrickard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "control.h"

static void	move(int key, t_fractal *fractal)
{
	t_complex	complex;

	complex = init_complex(fabs(fractal->max.re - fractal->min.re),
			fabs(fractal->max.im - fractal->min.im));
	if (key == KEY_LEFT)
	{
		fractal->min.re -= complex.re * 0.05;
		fractal->max.re -= complex.re * 0.05;
	}
	else if (key == KEY_RIGHT)
	{
		fractal->min.re += complex.re * 0.05;
		fractal->max.re += complex.re * 0.05;
	}
	else if (key == KEY_UP)
	{
		fractal->min.im += complex.im * 0.05;
		fractal->max.im += complex.im * 0.05;
	}
	else if (key == KEY_DOWN)
	{
		fractal->min.im -= complex.im * 0.05;
		fractal->max.im -= complex.im * 0.05;
	}
	draw_fractal(fractal);
}

static void	change_max_iter(int key, t_fractal *fractal)
{
	if (key == MAIN_PAD_PLUS)
	{
		if (fractal->max_iter < 50)
			fractal->max_iter += 1;
		else if (fractal->max_iter < (unsigned int)
			(fractal->max_iter * 1.05))
			fractal->max_iter = (unsigned int)
				(fractal->max_iter * 1.05);
	}
	if (key == MAIN_PAD_MINUS)
	{
		if (fractal->max_iter > 50)
			fractal->max_iter = (unsigned int)
				(fractal->max_iter * 0.95);
		else if (fractal->max_iter > fractal->max_iter - 1)
			fractal->max_iter -= 1;
	}
	draw_fractal(fractal);
}

static void	change_color_shift(t_fractal *fractal)
{
	fractal->color_shift = (fractal->color_shift + 1) % 3;
	draw_fractal(fractal);
}

int	key_press(int key, t_fractal *fractal)
{
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == MAIN_PAD_R)
	{
		set_defaults(fractal);
		draw_fractal(fractal);
	}
	else if (key == MAIN_PAD_PLUS || key == MAIN_PAD_MINUS)
		change_max_iter(key, fractal);
	else if (key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN)
		move(key, fractal);
	else if (key == MAIN_PAD_C)
		change_color_shift(fractal);
	else if (key == MAIN_PAD_SPACE)
		fractal->julia_block = !fractal->julia_block;
	return (0);
}
