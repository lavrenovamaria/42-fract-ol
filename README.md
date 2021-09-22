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

### 1. Initializing
Before doing anything, we need to include <mlx.h> library. To init MiniLibX, let's start with this:

```c
#include <mlx.h>

int main(void)
{
	void *mlx;
	
	mlx = mlx_init();
}
```
### 2. Open the window
When we run the previous code, nothing pops up and nothing is rendered, because we didn't create the window. Call `mlx_new_window` to open a window. This function returns a pointer to the window we just created. We can also give a height, width and a title to our window. And we need to call `mlx_loop` to render the window. 
```c
#include <mlx.h>

int main(void)
{
	void *mlx;
	void *mlx_win;
	
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "mlx_test");
	mlx_loop(mlx);
}
```
Now we have a window with 1920 width, 1080 height and "mlx_test" title.

### 3. Draw!

```c
typedef struct		s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}			t_data;

```
Since pixel is basically an int type, it is 4 bytes. But this can be different if we are dealing with small endian. `bits_per_pixel` is total number of bits stored for each pixel in a graphic image. We also need to understand that bytes are not aligned, so `line_length` may be different from the actual window width. So we need `mlx_get_data_addr` to compute the memory address offset with the line lenght set through.

We can get it with the following formula:
* int offset = (y * line_length + x * (bits_per_pixel / 8));

Since `line_length` is the number of bytes in one horizontal line of the image, it is moved to a memory address equal to the y-coordinate of the pixel coordinate as (line_length * y-coordinate). Since `bits_per_pixel` is the number of bits per pixel, dividing by 8 to convert to bytes gives bytes per pixel. (bits_per_pixel / 8 * y coordinate) You can finally get the memory address of the pixel at (x, y) coordinates by moving the memory address as much as the x coordinate.

`mlx_get_data_addr` returns the address of the starting point in memory where the image is stored as a char * type pointer. If mlx_get_data_addr() is called successfully, values are assigned to the following three parameters:
* The number of bits required to express the color of a pixel is entered in the `bits_per_pixel` parameter.
* In the `line_lenght` parameter, the number of bytes required to store one image line is entered.
* The `endian` parameter indicates whether the pixel color is stored in little endian (0 specified) or big endian (1 specified).




```c
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
```
We will use `my_mlx_pixel_put` because `mlx_pixel_put` is very, very slow. This is because when you put a pixel on the window, it immidiately loads the frame before it is fully rendered. For this reason we will buffer all pixels before loading them into the window. 

Finally, we can draw an image inside a specific window with a `mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);`
* The first three parameters specify the identifiers of the mlx, window, and image created, specify the coordinates of the image.

### 4. Using keyboard

In order to receive input from keyboard/mouse/etc. in MiniLibX, you need to know the concept of [events](https://en.wikipedia.org/wiki/Event_(computing))

## Usage 

* `make` to compile this project.
* `./fractol_name`
