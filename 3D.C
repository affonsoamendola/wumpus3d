/*  Copyright 2018 Affonso Amendola
    
    This file is part of Wumpus3D.

    Wumpus3D is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Wumpus3D is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Wumpus3D.  If not, see <https://www.gnu.org/licenses/>
*/

#include <bios.h>
#include <dos.h>
#include <memory.h>
#include <math.h>
#include <time.h>

#include <conio.h>
#include <io.h>

#include <3D.H>

float near_clipping_plane_z  = 1.0f;
float far_clipping_plane_z = 10.0f;

float horizontal_fov = 110.0f;

static float camera_position[3] = {0.0f, 0.0f, 0.0f};

float * world_to_screen_coordinates(float * world_coordinates)
{
    float * projection;

    projection = malloc(2*sizeof(float));

    projection[cart_x] =    ((world_coordinates[cart_x] - camera_position[cart_x]) * near_clipping_plane_z )/
                            (world_coordinates[cart_z] - camera_position[cart_z]);

    projection[cart_y] =    ((world_coordinates[cart_y] - camera_position[cart_y]) * near_clipping_plane_z )/
                            (world_coordinates[cart_z] - camera_position[cart_z]);

    return projection;
}

void translate_camera(float * delta)
{
    camera_position[cart_x] += delta[cart_x];
    camera_position[cart_y] += delta[cart_y];
    camera_position[cart_z] += delta[cart_z];
}

float * get_camera_position()
{
    return &camera_position;
}


