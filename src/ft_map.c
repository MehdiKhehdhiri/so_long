
#include "../so_long.h"

/*
* ft_row_col
* check num_row, num_col
* return ret
*/
int	ft_row_col(t_info *all)
{
	char	*line;
	int		rd;
	int		count;
	int		flag;

	flag = 0;
	count = 0;
	rd = get_next_line(all->map.fd, &line);
	all->map.num_cols = (int)ft_strlen(line);
	while (rd > 0)
	{
		if (all->map.num_cols != (int)ft_strlen(line))
			flag = 1;
		free(line);
		rd = get_next_line(all->map.fd, &line);
		count++;
	}
	free(line);
	all->map.num_rows = count;
	if (flag == 1)
		return (0);
	return (1);
}

/*
* ft_map_array
* (char**)map_array
*/
void	ft_map_array(t_info *all)
{
	int		num_rows;
	int		i;
	char	*line;
	int		rd;

	i = 0;
	num_rows = all->map.num_rows;
	all->map.map_array = (char **)malloc(sizeof(char *) * (num_rows + 1));
	if (!all->map.map_array)
		return ;
	all->map.map_array[num_rows] = '\0';
	rd = get_next_line(all->map.fd2, &line);
	while (rd > 0)
	{
		all->map.map_array[i++] = ft_strdup(line);
		free(line);
		rd = get_next_line(all->map.fd2, &line);
	}
	free(line);
}

void	ft_map_init(t_map *map, char c, int i, int j)
{
	if (c == 'P')
	{
		map->p_x = i;
		map->p_y = j;
		map->num_player += 1;
	}
	else if (c == 'C')
		map->num_collectible += 1;
	else if (c == 'E')
		map->num_exit += 1;
	else if (c == 'k')
	{
		if (map->num_collectible == 0)
			ft_print_error2("Error: No collectible", map);
		else if (map->num_player != 1)
			ft_print_error2("Error: Player must be one", map);
		else if (map->num_exit == 0)
			ft_print_error2("Error: No Exit", map);
	}
}

void	ft_map_element(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->num_player = 0;
	map->num_collectible = 0;
	map->num_exit = 0;
	map->flag_exit = 0;
	while (map->map_array[i])
	{
		j = 0;
		while (map->map_array[i][j])
		{
			if (!ft_strchr("10PCE", map->map_array[i][j]))
				ft_print_error2("Error: pas de 10EPC", map);
			ft_map_init(map, map->map_array[i][j], i, j);
			j++;
		}
		i++;
	}
	ft_map_init(map, 'k', i, j);
}

/* //////ft_map/////////
* file_open , fd  ok
* check_map and parsing
* check rect, wall, 5 elements
*/
void	ft_map(char *filename, t_info *all)
{
	all->map.fd = open(filename, O_RDONLY);
	if (all->map.fd == -1)
		ft_print_error("Error: file open error.");
	all->map.fd2 = open(filename, O_RDONLY);
	if (all->map.fd2 == -1)
		ft_print_error("Error: file open error.");
	if (!ft_row_col(all))
		ft_print_error("Error: map is not rectangular");
	ft_map_array(all);
	ft_map_wall(all);
	ft_map_element(&(all->map));
	all->mlx.window_width = all->map.num_cols * TILE_SIZE;
	all->mlx.window_height = all->map.num_rows * TILE_SIZE;
}
