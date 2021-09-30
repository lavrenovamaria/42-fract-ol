#ifndef FRACTOL_H
# define FRACTOL_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define MOVE_UD 50
#define MOVE_RL 50

#define MLX_ERROR -1

typedef struct	s_complex
{
	double re;
	double im;
}				t_complex;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef union s_color
{
	int color;
	struct
	{
		uint8_t green: 8;
		uint8_t red: 8;
		uint8_t blue: 8;
		uint8_t alpha: 8;
	};
}	t_color;


typedef struct	s_fractal
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_data		*img;
	int			calibr;
	int			rgb;
	int			right_left;
	int			up_down;
	double		max_it;
	double		it;
	t_color		color;
	// int (*fractol_func) (struct s_fractal *);
}				t_fractal;



#endif
