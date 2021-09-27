#include "../includes/fractol.h"
#include "../includes/control.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

t_complex complex_square(t_complex num)
{
	t_complex result;
	result.re = num.re * num.re - num.im * num.im;
	result.im = 2 * num.re * num.im;
	return result;
}

double complex_module(t_complex num)
{
	double result;
	result = sqrt(num.re * num.re + num.im * num.im);
	return result;
}

t_complex complex_sum(t_complex num1, t_complex num2)
{
	t_complex result;
	result.re = num1.re + num2.re;
	result.im = num1.im + num2.im;
	return result;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
// int	handle_keypress(int keysym, t_fractal *fractal)
// {
// 	if (keysym == XK_Escape)
// 		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
// 	return (0);
// }

// int	handle_keyrelease(int keysym, void *fractal)
// {
// 	return (0);
// }
int mandelbrot(t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int color = 0xFFFFFF;
	double		x = 0;
	double		y = 0;
	double		a = 0;
	double		b = 0;
	int			iter = 50;
	int calibrate = 100;

	while(x < 600)
	{
		while(y < 600)
		{
			b = (x - 600/2)/calibrate;
			a = (600/2 - y)/calibrate;
			z.im = 0;
			z.re = 0;
			c.re = b;
			c.im = a;
			while(iter--)
			{
				z = complex_square(z);
				z = complex_sum(z, c);
				if (complex_module(z) > 2)
					break ;
			}
			if (iter <= 0)
			{
				my_mlx_pixel_put(fractal->img, x, y, 0xFFFFFF);
			}
			else
			{
				my_mlx_pixel_put(fractal->img, x, y, 0xFE3D43);
			}
			iter = 50;
			y++;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, fractal->img->img, 0, 0);
	return (0);
}



int	main(void)
{
	t_fractal	fractal;
	t_data		img;

	fractal.calibr = 100;

	fractal.mlx_ptr = mlx_init();
	fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx_test");
	img.img = mlx_new_image(fractal.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	fractal.img = &img;
	// if (fractal.mlx_ptr == NULL)
	// 	return (MLX_ERROR);
	// if (fractal.win_ptr == NULL)
	// {
	// 	free(fractal.win_ptr);
	// 	return (MLX_ERROR);
	// }
	//mlx_hook(fractal.mlx_ptr, &my_mlx_pixel_put, &fractal);
	// mlx_hook(fractal.win_ptr, WHEEL, MASK_WHEEL, &wheel_hook, &fractal);
	// mlx_hook(fractal.win_ptr, KEY_PRESS, MASK_KEY_PRESS, &keyboard_hook, &fractal);
	mandelbrot(&fractal);
	mlx_loop(fractal.mlx_ptr);
	//mlx_destroy_display(fractal.mlx_ptr);
	//free(fractal.mlx_ptr);
}
