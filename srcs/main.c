#include "../minilibx_opengl_20191021/mlx.h"
#include <unistd.h>

typedef struct	s_data {
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
//основной мейник, выводящий ряд пикселей разных цветов
// int	main(void)
// {
// 	void	*mlx;
// 	void	*mlx_win;
// 	t_data	img;
// 	int count1 = 5;
// 	// int count2 = 5;
// 	int i = 0;
// 	int idx = 0;
// 	int color[3] = {0x00FF0000, 0x0000FF00, 0x000000FF};

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, 500, 500, "Galochka, ti schas umresh");
// 	img.img = mlx_new_image(mlx, 500, 500);
// 	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
// 								&img.endian);
// 	while(i++ < 150)
// 		my_mlx_pixel_put(&img, count1++, 15, color[idx++]);
// 	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
// 	mlx_loop(mlx);
// }

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, 640, 360, "Tutorial Window - Create Image");

    void *image = mlx_new_image(mlx, 640, 360);

    int pixel_bits;
	int line_bytes;
	int endian;
	char *buffer = mlx_get_data_addr(image, &pixel_bits, &line_bytes, &endian);

	int color = 0xABCDEF;

	if (pixel_bits != 32)
	    color = mlx_get_color_value(mlx, color);

	for(int y = 0; y < 360; ++y)
	for(int x = 0; x < 640; ++x)
{
	int pixel = (y * line_bytes) + (x * 4);

	if (endian == 1)        // Most significant (Alpha) byte first
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (endian == 0)   // Least significant (Blue) byte first
	{
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
}
	mlx_put_image_to_window(mlx, win, image, 0, 0);
    mlx_loop(mlx);
}
