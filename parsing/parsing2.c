#include "../header.h"

int fill_forkey(t_data **data, char *key, char *value, t_strct **mlx)
{
	if (!ft_strcmp(key, "SO"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "EA"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "NO"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "WE"))
		return (settextures_value(key, data, mlx, value));
	if (!ft_strcmp(key, "C"))
		return (setcolors_value(key, value, data));
	if (!ft_strcmp(key, "F"))
		return (setcolors_value(key, value, data));
	return (-1);
}