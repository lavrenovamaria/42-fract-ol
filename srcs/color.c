#include "../minilibx_opengl_20191021/mlx.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	*mlx_ptr;
void	*win_ptr;
void	*mlx;
void	*win;

int	press_esc_key(int key, void *p)
{
	if (key == 0xFF1B)
		exit(0);
	return 0;
}

int	color_map(void *win, int w, int h)
{
	int	x;
	int	y;
	int	color;
	x = w;
	while (x--)
	{
		y = h;
		while (y--)
		{
			color = (x * 255)/ w + ((((w - x) * 255)/w) << 16) + (((y * 255)/ h) << 8);
				mlx_pixel_put(mlx,win,x,y,color);
		}
	}
	return 0;
}

int main(void)
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx_test");
	color_map(win_ptr, 500, 500);
	mlx_key_hook(win_ptr, press_esc_key, win_ptr);
	mlx_loop(mlx_ptr);
	return 0;
}
