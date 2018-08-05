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

	float velocity = 1.0f;

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
				movement[cart_z] = velocity;
				translate_camera(movement);
			}
			if(key == 's')
			{
				movement[cart_z] = -velocity;
				translate_camera(movement);
			}
			if(key == 'a')
			{
				movement[cart_x] = -velocity;
				translate_camera(movement); 
			}
			if(key == 'd')
			{
				movement[cart_x] = velocity;
				translate_camera(movement);
			}
		}

		draw_page(!get_current_frame_page());

		fill_screen(0);

		projected_coordinates = world_to_screen_coordinates(point_coordinates);
		set_pixel((int)projected_coordinates[0]+SCREEN_WIDTH/2, (int)projected_coordinates[1]+SCREEN_HEIGHT/2, 40);

		position = get_camera_position();

		inttostring((int)*position, text_char);
		print_string(0,1,40,text_char,1);
		inttostring((int)*(position+2), text_char);
		print_string(0,9,40,text_char,1);

		frame_page(get_current_draw_page());

	}
		
	free(projected_coordinates);
}

void print_order_info()
{
	int i =0;

	textcolor(WHITE);
	cprintf("\n");
	cprintf("        ");
	textcolor(RED);
	for(i=0;i<64;i++)cprintf("%c",0xDB);
	cprintf("        ");
	cprintf("        ");
	cprintf("%c",0xDB);
	textcolor(WHITE);
	textbackground(RED);
	cprintf("FOFONSO'S WUMPUS HUNT");
	textcolor(YELLOW);
	cprintf(": The hottest new game for ");
	textbackground(LIGHTGRAY);
	textcolor(RED);
	cprintf("V");
	textcolor(GREEN);
	cprintf("G");
	textcolor(BLUE);
	cprintf("A");
	textcolor(YELLOW);
	textbackground(RED);
	cprintf(" PC's.      ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" ______________________________________________________________ ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf("                                                                ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" Explore a dark cave filled with ");
	textcolor(LIGHTCYAN);
	cprintf("TREASURE");
	textcolor(YELLOW);
	cprintf("... But... Be careful  ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" for you are not alone... The cave houses a ");
	textcolor(GREEN);
	cprintf("TERRIBLE");
	textcolor(YELLOW);
	cprintf(" and ");
	textcolor(GREEN);
	cprintf("SMELLY ");
	textcolor(YELLOW);
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" creature called ");
	textcolor(BROWN);
	cprintf("THE TERRIBLY SMELLY WUMPUS");
	textcolor(YELLOW);
	cprintf("... That and It is   ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" filled with bottomless pits of ");
	textcolor(MAGENTA);
	cprintf("DEATH");
	textcolor(YELLOW);
	cprintf(", but don`t worry, you     ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" came prepared.  Pretty ");
	textcolor(MAGENTA);
	cprintf("BADLY");
	textcolor(YELLOW);
	cprintf("... But prepared nonetheless.      ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf("                                                                ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" This game was created by ");
	textcolor(LIGHTCYAN);
	cprintf("Affonso Amendola");
	textcolor(YELLOW);
	cprintf(", a Brazilian         ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" undergrad student at the ");
	textcolor(MAGENTA);
	cprintf("Institute of Astronomy, Geophysics    ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" and Atmospheric Sciences");
	textcolor(YELLOW);
	cprintf(" of the University of Sao Paulo,       ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" after finding an old book on ");
	textbackground(LIGHTGRAY);
	textcolor(RED);
	cprintf("V");
	textcolor(GREEN);
	cprintf("G");
	textcolor(BLUE);
	cprintf("A");
	textcolor(YELLOW);
	textbackground(RED);
	cprintf(" game development at ");
	textcolor(GREEN);
	cprintf("Garoa     ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" Hacker Clube");
	textcolor(YELLOW);
	cprintf(", a hackerspace in Sao Paulo, and spending a       ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" a sleepless weekend making it.                                 ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" Thank you so much for playing. I hope you had fun.             ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf("                                                                ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" Affonso Amendola, affonso.gino.neto@usp.br                     ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" http://www.github.com/affonsoamendola/wumpusvga                ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf(" 1:21 AM, 11 July 2018, Sao Paulo, Brazil, Earth                ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(RED);
	cprintf("                                                                ");
	textbackground(BLACK);
	cprintf("        ");
	cprintf("        ");
	textbackground(BLACK);
	cprintf("                                                                ");
}





