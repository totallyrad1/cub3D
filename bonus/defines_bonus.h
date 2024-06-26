/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:35:17 by mozennou          #+#    #+#             */
/*   Updated: 2024/05/02 16:02:12 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

# define WIDTH 1280
# define HEIGHT 960

# define E 0
# define S 1.57079632679
# define W 3.14159265359
# define N 4.71238898038

# define FOV 1.0471975512 

# define TILE_SIZE 512

# define DISPROJ 1108.5125

//keys
# define KEY_ESC 53
# define RLEFT_KEY 124
# define RRIGHT_KEY 123
# define UP_KEY 13
# define DOWN_KEY 1
# define LEFT_KEY 0
# define RIGHT_KEY 2
# define MOVE_SPEED 25

//events defines
enum
{
	ON_KEYDOWN = 2,
	ON_KEYRELEASE = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
}	;

#endif