# include "../cub.h"
# include "../../mlx/mlx.h"

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}				t_mlx;

int	free_all(t_mlx *mlx_str)
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_mlx *mlx_st)
{
	if (keycode == ESC)
		free_all(mlx_st);
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx	mlx_st;

	mlx_st.mlx = mlx_init();
	mlx_st.win = mlx_new_window(mlx_st.mlx, 2200, 1200, "ny privet");
	mlx_hook(mlx_st.win, 17, 0, free_all, &mlx_st);
	mlx_hook(mlx_st.win, 02, 0, key_hook, &mlx_st);
	mlx_loop(mlx_st.mlx);
}
