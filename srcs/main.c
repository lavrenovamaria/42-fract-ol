#include "../includes/fractol.h"
#include "../includes/control.h"

// int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
// {
// 	return (red << 16 | green << 8 | blue);
// }

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

int mandelbrot(t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	t_fractal fr;
	int color = 0xFFFFFF; //норм строчка
	// int color2 = ft_color(fr->color);
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
			b = ((x - 600/2) + fractal->right_left)/calibrate;
			a = ((600/2 - y) + fractal->up_down)/calibrate;
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
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			}
			else
			{
				color = iter * 225; //норм строчка, работает
				my_mlx_pixel_put(fractal->img, x, y, color);
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

int	close_win(t_fractal *fractal)
{
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	exit(0);
	return (0);
}

int keyboard_hook(int key, t_fractal *fractal)
{
	// printf("%drbggr", key);
	if (key == KEY_ESC)
		close_win(fractal);
	if (key == KEY_UP)
	{
		fractal->up_down -= MOVE_UD;
		mandelbrot(fractal);
	}
	if (key == KEY_DOWN)
	{
		fractal->up_down += MOVE_UD;
		mandelbrot(fractal);
	}
	if (key == KEY_RIGHT)
	{
		fractal->right_left -= MOVE_RL;
		mandelbrot(fractal);
	}
	if (key == KEY_LEFT)
	{
		fractal->right_left += MOVE_RL;
		mandelbrot(fractal);
	}
	return (0);
}

int wheel_hook(int wheel, int x, int y, t_fractal *fractal)
{
	//printf("%drbggr", wheel);
	if (wheel == SCROLL_UP || wheel == SCROLL_DOWN)
	{
		if(wheel == SCROLL_DOWN)
		{
			fractal->calibr += C_CHNG_ST + (fractal->calibr / C_CHNG_ST);
			//fractal->right_left += WINDOW_WIDTH/2 - (x + (fractal->calibr/ZOOM_PAR));
			//fractal->up_down -= (y + (fractal->calibr/ZOOM_PAR)) - WINDOW_HEIGHT/2;
		}
		else
		{
			fractal->calibr -= C_CHNG_ST + (fractal->calibr / C_CHNG_ST);
			//fractal->right_left -= WINDOW_WIDTH/2 - (x + (fractal->calibr/ZOOM_PAR));
			//fractal->up_down += (y + (fractal->calibr/ZOOM_PAR)) - WINDOW_HEIGHT/2;
			if (fractal->calibr < C_CHNG_ST)
			{
				fractal->calibr = C_CHNG_ST;
				//fractal->right_left = 0;
				//fractal->up_down = 0;
			}
		}
		mandelbrot(fractal);
	}
	return (0);
}

// static void	print_names_fractals(void)
// {
// 	ft_putendl("╔════════════════════════════════════════════════════╗");
// 	ft_putendl("║                       Fact'ol                      ║");
// 	ft_putendl("╠════════════════════════════════════════════════════╣");
// 	ft_putendl("║                   *1- Mandelbrot                   ║");
// 	ft_putendl("║                   *2- Julia                        ║");
// 	ft_putendl("║                   *3- Burning Ship                 ║");
// 	ft_putendl("╚════════════════════════════════════════════════════╝");
// 	exit(0);
// }

int	main(void)
{
	t_fractal	fractal;
	t_data		img;

	fractal.calibr = 100;
	// fractal.right_left = 0;
	// fractal.up_down = 0;
	// if (argc != 2)
	// 	print_names_fractals();
	fractal.mlx_ptr = mlx_init();
	fractal.win_ptr = mlx_new_window(fractal.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx_test");
	if (fractal.win_ptr == NULL)
	{
		free(fractal.win_ptr);
		return (MLX_ERROR);
	}
	img.img = mlx_new_image(fractal.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	fractal.img = &img;
	mandelbrot(&fractal);
	mlx_hook(fractal.win_ptr, WHEEL, MASK_WHEEL, wheel_hook, &fractal);
	mlx_hook(fractal.win_ptr, KEY_PRESS, MASK_KEY_PRESS, keyboard_hook, &fractal);
	mlx_loop(fractal.mlx_ptr);
	// free(data.mlx_ptr);
}
