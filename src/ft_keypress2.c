/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hesong <hesong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 18:12:11 by hyungyoo          #+#    #+#             */
/*   Updated: 2022/09/13 23:11:55 by hesong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	keypress_event(int keycode, t_info *all)
{
	static int	flag;

	if (flag == 0)
		all->count_movement = 0;
	flag++;
	if (keycode == 65307)
		exit(0);
	else if (keycode == 119)
		ft_player_move(all, 'U');
	else if (keycode == 115)
		ft_player_move(all, 'D');
	else if (keycode == 97)
		ft_player_move(all, 'L');
	else if (keycode == 100)
		ft_player_move(all, 'R');
	return (0);
}

int	keypress(t_info *all)
{
	ft_free(all);
	ft_destroy(all);
	exit(0);
}
