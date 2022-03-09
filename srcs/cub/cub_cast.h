# ifndef CUB_CAST_H
# define CUB_CAST_H

int		keyhook(int keycode, t_raycast *raycast);
void	init_st_rc(t_data *main, t_raycast *raycast);
int		free_all(void);
void	calc(t_raycast *raycast, t_data *main);
int		render(t_data *main);

#endif
