# ifndef CUB_CAST_H
# define CUB_CAST_H

// int		keyhook(int keycode, t_raycast *raycast);
void	init_st_rc(t_data *main, t_raycast *raycast);
int		free_all(void);
void	calc(t_raycast *raycast, t_data *main);
int		render(t_data *main);
void	key_event(t_raycast *raycast, t_keys *keys);

// init.c
void	init_st_rc2(t_data *main, t_raycast *raycast);
void	init_st_rc(t_data *main, t_raycast *raycast);
void	init_txt(t_data *main);
void	open_txt(t_data *main, t_textures *txt, char *path);
void	load_txt(t_data *main);

//keyhook.c
int		free_all(void);
int		keypress(int keycode, t_keys *keys);
int		keyrelease(int keycode, t_keys *keys);
int		keyhook(int keycode, t_raycast *raycast);

//move.c
void	move_a(t_raycast *raycast);
void	move_s(t_raycast *raycast);
void	move_d(t_raycast *raycast);
void	move_w(t_raycast *raycast);

//rotate.c
void	rotate_l(t_raycast *raycast);
void	rotate_r(t_raycast *raycast);

#endif
