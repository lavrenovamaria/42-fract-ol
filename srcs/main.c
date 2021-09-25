#include "../includes/fractol.h"
#include "../includes/control.h"

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
	return (red << 16 | green << 8 | blue);
}

int	handle_keypress(int keysym, t_img *img)
{
	if (keysym == XK_Escape)
		mlx_destroy_window(img->mlx_ptr, img->win_ptr);
	return (0);
}

int	handle_keyrelease(int keysym, void *img)
{
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	t_img	img;

	img.mlx_ptr = mlx_init();
	if (img.mlx_ptr == NULL)
		return (MLX_ERROR);
	img.win_ptr = mlx_new_window(img.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx_test");
	if (img.win_ptr == NULL)
	{
		free(img.win_ptr);
		return (MLX_ERROR);
	}
	mlx_loop_hook(img.mlx_ptr, &my_mlx_pixel_put, &img);
	mlx_hook(img.win_ptr, WHEEL, MASK_WHEEL, &wheel_hook, &img);
	mlx_hook(img.win_ptr, KEY_PRESS, MASK_KEY_PRESS, &keyboard_hook, &img);
	mlx_loop(img.mlx_ptr);
	mlx_destroy_display(img.mlx_ptr);
	free(img.mlx_ptr);
}
