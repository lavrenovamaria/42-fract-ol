#include "../includes/fractol.h"
#include "../includes/control.h"

t_complex	init_complex(double re, double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

t_complex	complex_abs(t_complex num)
{
	if (num.re < 0)
		num.re *= -1;
	if (num.im < 0)
		num.im *= -1;
	return num;
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

unsigned int	set_color(int iter, t_fractal *fractal)//не забудь потом назвать rainbow
{
	t_color	s;
	(void)fractal;

	s.red = 0;
	s.green = 0;
	s.blue = 0;
	int i = iter;
	s.red = sin(0.3 * (double)i + 0.0) * 127.0 + 128.0;
	s.green = sin(0.3 * (double)i + 2.0) * 127.0 + 128.0;
	s.blue = sin(0.3 * (double)i + 4.0) * 127.0 + 128.0;
	return ((UI)s.red << 16 | (UI)s.green << 8 | (UI)s.blue);
}
//rainbow

unsigned int	aqua_blue(int iter, t_fractal *fractal)
{
	t_color	s;
	(void)fractal;

	s.red = 0;
	s.green = 0;
	s.blue = 0;
	int i = iter;
	s.red = sin(0.3 * (double)i);
	s.green = sin(0.3 * (double)i + 3) * 127 + 128;
	s.blue = sin(0.3 * (double)i + 3) * 127 + 128;
	return ((UI)s.red << 16 | (UI)s.green << 8 | (UI)s.blue);
}
//blue


//this WORKS DONT YOU DARE TOUCH IT
int	random_color(int iter, t_fractal *fractal)
{
	t_color color;

	color.color = 0;
	color.red = (iter * fractal->color.red) % 255;
	color.green = (iter * fractal->color.green) % 255;
	color.blue = (iter * fractal->color.blue) % 255;
	return (color.color);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int julia(t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int color;
	double		x = 0;
	double		y = 0;
	double		a = 0;
	double		b = 0;
	fractal->it = 10;
	int calibrate = fractal->calibr;

	while(x < WINDOW_WIDTH)
	{
		while(y < WINDOW_HEIGHT)
		{
			b = ((x - WINDOW_WIDTH/2) + fractal->right_left)/calibrate;
			a = ((WINDOW_HEIGHT/2 - y) + fractal->up_down)/calibrate;
			z.im = a;
			z.re = b;
			c.re = fractal->mouse_ud;
			c.im = fractal->mouse_rl;
			while(fractal->it--)
			{
				z = complex_square(z);
				z = complex_sum(z, c);
				if (complex_module(z) > 2)
					break ;
			}
			if (fractal->it <= 0)
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			else
			{
				//color = aqua_blue(fractal->it, fractal);
				color = set_color(fractal->it, fractal);
				my_mlx_pixel_put(fractal->img, x, y, color);
			}
			fractal->it = 50;
			y++;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, fractal->img->img, 0, 0);
	return (0);
}
//dont forget to uncomment!!!!
int	motion_hook(int x, int y, t_fractal *fractal)
{
	fractal->mouse_rl = ((double)x - WINDOW_WIDTH / 2)/JULIA_P;
	fractal->mouse_ud = (WINDOW_HEIGHT / 2 - (double)y)/JULIA_P;
	julia(fractal);
	return 0;
}

int mandelbrot(t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int color; //норм строчка
	double		x = 0;
	double		y = 0;
	double		a = 0;
	double		b = 0;
	fractal->it = 10;
	int calibrate = fractal->calibr;

	while(x < WINDOW_WIDTH)
	{
		while(y < WINDOW_HEIGHT)
		{
			b = ((x - WINDOW_WIDTH/2) + fractal->right_left)/calibrate;
			a = ((WINDOW_HEIGHT/2 - y) + fractal->up_down)/calibrate;
			z.im = 0;
			z.re = 0;
			c.re = b;
			c.im = a;
			while(fractal->it--)
			{
				z = complex_square(z);
				z = complex_sum(z, c);
				if (complex_module(z) > 2)
					break ;
			}
			if (fractal->it <= 0)
			{
				//printf("%d", iter);
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			}
			else
			{

				color = aqua_blue(fractal->it, fractal);
				//color = set_color(fractal->it, fractal);
				//get_color(iter, fractal); //норм строчка, работает
				my_mlx_pixel_put(fractal->img, x, y, color);
			}
			fractal->it = 50;
			y++;
		}
		y = 0;
		x++;
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, fractal->img->img, 0, 0);
	return (0);
}
//мандельброт рабочий, оставь его в покое, пожалуйста

int burning_ship(t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int color; //норм строчка
	double		x = 0;
	double		y = 0;
	double		a = 0;
	double		b = 0;
	fractal->it = 10;
	int calibrate = fractal->calibr;

	while(x < WINDOW_WIDTH)
	{
		while(y < WINDOW_HEIGHT)
		{
			b = ((x - WINDOW_WIDTH/2) + fractal->right_left)/calibrate;
			a = ((WINDOW_HEIGHT/2 - y) + fractal->up_down)/calibrate;

			z.im = 0;
			z.re = 0;
			c.re = b;
			c.im = -a;
			while (fractal->it--)
			{
				z = complex_abs(z);
				z = complex_square(z);
				z = complex_sum(z, c);
				if (complex_module(z) > 2)
					break ;
			}
			if (fractal->it <= 0)
			{
				//printf("%d", iter);
				my_mlx_pixel_put(fractal->img, x, y, 0x000000);
			}
			else
			{
				color = set_color(fractal->it, fractal);
				//get_color(iter, fractal); //норм строчка, работает
				my_mlx_pixel_put(fractal->img, x, y, color);
			}
			fractal->it = 50;
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

void reset_all(t_fractal *fractal)
{
	printf("%f ", fractal->it);
	fractal->calibr = 100;
	fractal->it = 50;
	fractal->color.color = 20;
	fractal->right_left = 0;
	fractal->up_down = 0;
	fractal->mouse_rl = 0;
	fractal->mouse_ud = 0;
}

void	exit_window(int key, t_fractal *fractal)
{
	if (key == KEY_ESC)
		close_win(fractal);
}

void	keyboard_hook_rlud(int key, t_fractal *fractal)
{
	if (key == KEY_UP)
	{
		fractal->up_down -= MOVE_UD;
		mandelbrot(fractal);
	}
	else if (key == KEY_DOWN)
	{
		fractal->up_down += MOVE_UD;
		mandelbrot(fractal);
	}
	else if (key == KEY_RIGHT)
	{
		fractal->right_left -= MOVE_RL;
		mandelbrot(fractal);
	}
	else if (key == KEY_LEFT)
	{
		fractal->right_left  += MOVE_RL;
		mandelbrot(fractal);
	}
}

// static void keyboard_hook_change_color(int key, t_fractal *fractal)
// {
// 	fractal->palette = key;
// 	fractal->palette +=1;
// 	if (fractal->palette == 1)
// 		rainbow(fractal->max_it, fractal);
// 	else if (fractal->palette == 2)
// 		aqua_blue(fractal->max_it, fractal);
// 	else if (fractal->palette == 3)
// 		random_color(fractal->max_it, fractal);
// 	if (fractal->palette >=4)
// 		fractal->palette = 0;
// }

int keyboard_hook(int key, t_fractal *fractal)
{
	// if (key == KEY_C)
	// 	keyboard_hook_change_color(key, fractal);
	if (key == KEY_Z)
	{
		reset_all(fractal);
		mandelbrot(fractal);
	}
	if (key == KEY_ESC)
		exit_window(key, fractal);
	if (key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
		keyboard_hook_rlud(key, fractal);
	return (0);
}

int wheel_hook(int wheel, int x, int y, t_fractal *fractal)
{
	//printf("%drbggr", wheel);
	(void)x;
	(void)y;
	if (wheel == SCROLL_UP || wheel == SCROLL_DOWN)
	{
		if(wheel == SCROLL_DOWN)
		{
			fractal->calibr += C_CHNG_ST + (fractal->calibr / C_CHNG_ST);
			fractal->right_left += WINDOW_WIDTH/2 - (x + (fractal->calibr/ZOOM_PAR));
			fractal->up_down -= (y + (fractal->calibr/ZOOM_PAR)) - WINDOW_HEIGHT/2;
		}
		else
		{
			fractal->calibr -= C_CHNG_ST + (fractal->calibr / C_CHNG_ST);
			fractal->right_left -= WINDOW_WIDTH/2 - (x + (fractal->calibr/ZOOM_PAR));
			fractal->up_down += (y + (fractal->calibr/ZOOM_PAR)) - WINDOW_HEIGHT/2;
			if (fractal->calibr < C_CHNG_ST)
			{
				fractal->calibr = C_CHNG_ST;
				fractal->right_left = 0;
				fractal->up_down = 0;
			}
		}
		julia(fractal);
		//mandelbrot(fractal);
		//burning_ship(fractal);
	}
	return (0);
}

int	main(void)
{
	t_fractal	fractal;
	t_data		img;

	fractal.calibr = 100;
	fractal.right_left = 0;
	fractal.up_down = 0;
	fractal.mouse_rl = 0;
	fractal.mouse_ud = 0;
	fractal.max_it = 100;
	//fractal->color.red = 0;
	//fractal->color.green = 0;
	//fractal->color.blue = 0;
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
	//mandelbrot(&fractal);
	julia(&fractal);
	//burning_ship(&fractal);
	mlx_hook(fractal.win_ptr, WHEEL, MASK_WHEEL, wheel_hook, &fractal);
	mlx_hook(fractal.win_ptr, KEY_PRESS, MASK_KEY_PRESS, keyboard_hook, &fractal);
	mlx_hook(fractal.win_ptr, MOTION_NOTIFY, MASK_POINTER_MOTION, motion_hook, &fractal);
	mlx_loop(fractal.mlx_ptr);
	// free(data.mlx_ptr);
}
