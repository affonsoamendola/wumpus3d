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
#include <VGA.H>

void main()
{
	float point_coordinates[] = {100.0f, 3.0f, 10.0f};

	float * projected_coordinates;

	int game_running = 1;
	char key;

	float current_velocity = 0.0f;
	float acceleration = 0.01f;

	float movement[3];

	char text_char[10];

	float * position;

	set_graphics_mode(GRAPHICS_MODEX);

	while(game_running)
	{
		if(kbhit())
		{
			key =  getch();

			movement[0] = 0.0f;
			movement[1] = 0.0f;
			movement[2] = 0.0f;

			if(key == 'w')
			{
				current_velocity += acceleration;
				movement[cart_z] = current_velocity;
				translate_camera(movement);
			}
			if(key == 's')
			{
				current_velocity += acceleration;
				movement[cart_z] = -current_velocity;
				translate_camera(movement);
			}
			if(key == 'a')
			{
				current_velocity += acceleration;
				movement[cart_x] = -current_velocity;
				translate_camera(movement); 
			}
			if(key == 'd')
			{
				current_velocity += acceleration;
				movement[cart_x] = current_velocity;
				translate_camera(movement);
			}
		}

		draw_page(!get_current_frame_page());

		fill_screen(0);

		projected_coordinates = world_to_screen_coordinates(point_coordinates);
		set_pixel(	(int)projected_coordinates[0] + SCREEN_WIDTH/2, 
					(int)projected_coordinates[1] + SCREEN_HEIGHT/2, 
					40	);

		position = get_camera_position();

		inttostring((int)*position, text_char);
		print_string(0,1,40,text_char,1);
		inttostring((int)*(position+2), text_char);
		print_string(0,9,40,text_char,1);

		frame_page(get_current_draw_page());
	}
		
	free(projected_coordinates);
}