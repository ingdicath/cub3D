/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lodev.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dsalaman <dsalaman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 16:40:57 by dsalaman      #+#    #+#                 */
/*   Updated: 2020/08/05 16:41:01 by dsalaman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <mlx.h>
#include <math.h>

#define screenWidth 640
#define screenHeight 480
#define mapWidth 24
#define mapHeight 24


int main(int argc, char **argv)
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double time;
	double oldTime;

	pos_x = 100;
	pos_y = 100;
	dir_x = -1;
	dir_y = 0;
	plane_x = 0;
	plane_y = 0.66;
	time = 0;
	oldTime = 0;

 	screen(screenWidth, screenHeight, 0, "Raycaster");
	return (0);

}