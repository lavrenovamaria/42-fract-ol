# 42-fract-ol
## Discover 2D programming and the psychedelic universe of fractals in this project, using minilibX.

<p align="center">
	<img  src="https://user-images.githubusercontent.com/84707645/132736988-dbdd08fe-eef1-4c0d-8e70-c6401aab27c6.gif" width="400" height="400" />
</p>

Subject is presented in the [en.subject.pdf](https://github.com/lavrenovamaria/42-fract-ol/files/7128672/en.subject.pdf)

## Credits 

* [Veritasium: this equation will change how you see the world](https://www.youtube.com/watch?v=ovJcsL7vyrk)

* [Vsauce: the Mandelbrot Set](https://www.youtube.com/watch?v=MwjsO6aniig)
* [The Mandelbrot Set Explained](https://www.youtube.com/watch?v=7MotVcGvFMg)

* [42Docs. MiniLibX. Getting started](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)

* [MiniLibX. Basic introduction, tutorials, tips & tricks.](https://gontjarow.github.io/MiniLibX/mlx-tutorial-create-image.html) 

* [RGBA color model](https://en.wikipedia.org/wiki/RGBA_color_model#Representation)

## Knowledge of fractol. The Mandelbrot Set

<img width="746" alt="Screen Shot 2021-09-20 at 12 29 05 PM" src="https://user-images.githubusercontent.com/84707645/133981535-b4c77c88-b3ff-4c00-aa5d-eb98a145ec19.png">

The Mandelbrot set with the real and imaginary axes labeled.


```c
typedef struct		s_complex
{
	double			re;
	double			im;
}			t_complex;
```

## Let's draw a pixel on the screen!

1. Initializing
Before doing anything, we need to include <mlx.h> library. To init MinilibX, let's start with this:

```c
#include <mlx.h>

int main(void)
{
	void *mlx;
	
	mlx = mlx_init();
}
```

```c
typedef struct		s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}			t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
```
We will use `my_mlx_pixel_put` because `mlx_pixel_put` is very, very slow. This is because when you put a pixel on the window, it immidiately loads the frame before it is fully rendered. For this reason we will buffer all pixels before loading them into the window. 



## Usage 

* `make` to compile this project.
* `./fractol_name`
