int	ft_sign(double num)
{
	if (num < 0)
		return (-1);
	return (1);
}

void	strafe(t_raycast *raycast, int dir)
{
	float new_pos_y;
	float new_pos_x;

	new_pos_y = raycast->posY + raycast->dirX * raycast->moveSpeed * dir;
	new_pos_x = raycast->posX + raycast->dirY * raycast->moveSpeed * -dir;
	if ((raycast->main->map[(int)(new_pos_y + 0.1f * ft_sign(new_pos_y - raycast->posY))][(int)raycast->posX] ) == '0')
		raycast->posY = new_pos_y;
	if ((raycast->main->map[(int)raycast->posY][(int)(new_pos_x + 0.1f * ft_sign(new_pos_x - raycast->posX))] ) == '0')
		raycast->posX = new_pos_x;
}
