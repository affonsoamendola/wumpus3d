
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "fflibvga.h"
#include "keyb.h"
#include "fftime.h"

#define WALL_HEIGHT 10.0f

#define WALL_COLOR 40
#define CEILING_COLOR 2
#define GROUND_COLOR 1

#define PI 3.14159265

typedef float ANGLE_RAD;

typedef struct VECTOR3_
{
	float x;
	float y;
	float z;
} 
VECTOR3;

typedef struct VECTOR2_
{
	float x;
	float y;
} 
VECTOR2;

typedef struct MATRIX_
{
	int sizeX;
	int sizeY;
	float * contents;
} 
MATRIX;

typedef struct CAMERA_
{
	VECTOR2 position;

	ANGLE_RAD pointing;

	float z_plane_near;
	float z_plane_far;
	float horizontal_fov;
	float aspect_ratio;
} 
CAMERA;

typedef struct WALL_
{
	VECTOR2 pointA;
	VECTOR2 pointB;
} 
WALL;

void set_matrix(MATRIX matrix, int posX, int posY, float value);

float get_matrix(MATRIX matrix, int posX, int posY);

VECTOR2 mult_v2(VECTOR2 vector, float scalar);
VECTOR2 sub_v2(VECTOR2 vectorA, VECTOR2 vectorB);
VECTOR2 sum_v2(VECTOR2 vectorA, VECTOR2 vectorB);
VECTOR2 neg_v2(VECTOR2 vector);

VECTOR2 translate_v2(VECTOR2 point, VECTOR2 amount);
VECTOR2 rotate_v2(VECTOR2 point, VECTOR2 origin, ANGLE_RAD amount);

float norm_v2(VECTOR2 vector);
VECTOR2 unit_v2(VECTOR2 vector);
float dot_v2(VECTOR2 vectorA, VECTOR2 vectorB);

MATRIX create_matrix(int sizeX, int sizeY);

MATRIX identity_matrix(int sizeX, int sizeY);
MATRIX rotation_matrix_v2(ANGLE_RAD angle);

MATRIX scale_marix(MATRIX matrix, float scalar);
VECTOR2 multiply_v2_by_matrix(VECTOR2 vector, MATRIX matrix);

VECTOR3 project_point_to_camera_space(VECTOR2 point, float height, CAMERA camera);

POINT2 convert_camera_space_to_screen_space(VECTOR2 camera_space);

void set_matrix(MATRIX matrix, int posX, int posY, float value)
{

	*(matrix.contents + posX + posY*matrix.sizeX) = value; 
}

float get_matrix(MATRIX matrix, int posX, int posY)
{

	return *(matrix.contents + posX + posY*matrix.sizeX);
}

VECTOR2 vector2(float x, float y)
{
	VECTOR2 to_return;

	to_return.x = x;
	to_return.y = y;

	return to_return;
}

VECTOR3 vector3(float x, float y, float z)
{
	VECTOR3 to_return;

	to_return.x = x;
	to_return.y = y;
	to_return.z = z;

	return to_return;
}

VECTOR2 zero_v2()
{
	VECTOR2 new_vector;

	new_vector.x = 0.0f;
	new_vector.y = 0.0f;

	return new_vector;
}

VECTOR2 mult_v2(VECTOR2 vector, float scalar)
{	
	VECTOR2 new_vector;

	new_vector.x = vector.x * scalar;
	new_vector.y = vector.y * scalar;

	return new_vector;
}

VECTOR2 intersect_v2_horizontal(VECTOR2 vectorA, VECTOR2 vectorB, float horz_line_y)
{
	VECTOR2 above_line;
	VECTOR2 below_line;

	VECTOR2 to_return;

	float dx;
	float dy;
	float Dx;
	float Dy;

	if(vectorA.y > horz_line_y)
	{
		above_line = vectorA;
		below_line = vectorB;
	}
	else
	{
		below_line = vectorA;
		above_line = vectorB;
	}

	Dy = above_line.y - below_line.y;
	Dx = below_line.x - above_line.x;

	dy = above_line.y - horz_line_y;

	dx = dy*(Dx/Dy);

	return vector2(above_line.x + dx, horz_line_y);
}

VECTOR2 sub_v2(VECTOR2 vectorA, VECTOR2 vectorB)
{	
	VECTOR2 new_vector;

	new_vector.x = vectorA.x - vectorB.x;
	new_vector.y = vectorA.y - vectorB.y;

	return new_vector;
}

VECTOR2 sum_v2(VECTOR2 vectorA, VECTOR2 vectorB)
{
	VECTOR2 new_vector;

	new_vector.x = vectorA.x + vectorB.x;
	new_vector.y = vectorA.y + vectorB.y;

	return new_vector;
}

VECTOR2 neg_v2(VECTOR2 vector)
{
	VECTOR2 new_vector;

	new_vector.x = -vector.x;
	new_vector.y = -vector.y;

	return new_vector;
}

VECTOR2 translate_v2(VECTOR2 point, VECTOR2 amount)
{

	return sum_v2(point, amount);
}

VECTOR2 rotate_v2(VECTOR2 point, VECTOR2 origin, ANGLE_RAD amount)
{
	//Rotates a point around an origin by angle_rad radians on the CLOCKWISE direction

	VECTOR2 translated_point;

	translated_point = translate_v2(point, neg_v2(origin));

	translated_point = multiply_v2_by_matrix(translated_point, rotation_matrix_v2(amount));

	translated_point = translate_v2(translated_point, origin);

	return translated_point;
}

float norm_v2(VECTOR2 vector)
{
	return (float)sqrt(	((double)vector.x)*((double)vector.x) + 
						((double)vector.y)*((double)vector.y));
}

VECTOR2 unit_v2(VECTOR2 vector)
{
	VECTOR2 return_vector;

	float norm;

	norm = norm_v2(vector);

	return_vector.x = vector.x/norm;
	return_vector.y = vector.y/norm;

	return return_vector;
}

float dot_v2(VECTOR2 vectorA, VECTOR2 vectorB)
{

	return (((double)vectorA.x)*((double)vectorB.x) + ((double)vectorA.y)*((double)vectorB.y));
}

MATRIX create_matrix(int sizeX, int sizeY)
{
	MATRIX matrix;

	matrix.sizeX = sizeX;
	matrix.sizeY = sizeY;
	matrix.contents = malloc(sizeof(float)*(sizeX*sizeY));

	return matrix;
}

MATRIX identity_matrix(int sizeX, int sizeY)
{
	MATRIX matrix;
	int i, j;

	if(sizeX == sizeY)
	{
		matrix = create_matrix(sizeX, sizeY);
		return matrix;
	}

	for(i = 0; i < sizeX; i++)
	{
		for(j = 0; j < sizeY; j++)
		{
			if(i == j)
			{
				set_matrix(matrix, i, j, 1.0f);
			}
			else
			{
				set_matrix(matrix, i, j, 0.0f);
			}
		}
	}
	return matrix;	
}

MATRIX rotation_matrix_v2(ANGLE_RAD angle)
{
	MATRIX matrix;

	matrix = create_matrix(2, 2);

	set_matrix(matrix, 0, 0,  cos(angle));
	set_matrix(matrix, 1, 0,  sin(angle));
	set_matrix(matrix, 0, 1, -sin(angle));
	set_matrix(matrix, 1, 1,  cos(angle));

	return matrix;
}

MATRIX scale_marix(MATRIX matrix, float scalar)
{
	int i, j;

	MATRIX scaled_matrix;

	scaled_matrix = create_matrix(matrix.sizeX, matrix.sizeY);

	for(i = 0; i < matrix.sizeX; i++)
	{
		for(j = 0; j < matrix.sizeY; j++)
		{
			set_matrix(scaled_matrix, i, j, get_matrix(matrix, i, j)*scalar);
		}
	}

	return scaled_matrix;
}

VECTOR2 multiply_v2_by_matrix(VECTOR2 vector, MATRIX matrix)
{
	VECTOR2 multiplied;

	if(matrix.sizeX != 2 || matrix.sizeY != 2)
	{
		return vector;
	}
	else
	{
		multiplied.x = get_matrix(matrix, 0, 0)*vector.x + get_matrix(matrix, 1, 0)*vector.y;
		multiplied.y = get_matrix(matrix, 0, 1)*vector.x + get_matrix(matrix, 1, 1)*vector.y;
	}

	return multiplied;
}

VECTOR2 camera_transform(VECTOR2 vector, CAMERA camera)
{
	VECTOR2 transformed_vector;

	transformed_vector = translate_v2(vector, neg_v2(camera.position));
	transformed_vector = rotate_v2(transformed_vector, zero_v2(), -camera.pointing);

	return transformed_vector;
}

VECTOR3 screen_space_projection(VECTOR3 vector, CAMERA camera)
{
	VECTOR3 projected_point;

	projected_point.x = vector.x * camera.aspect_ratio * (camera.z_plane_near / vector.z);
	projected_point.y = vector.y * (camera.z_plane_near / vector.z);
	projected_point.z = (vector.z - camera.z_plane_near)/(camera.z_plane_far - camera.z_plane_near);

	return projected_point;
}

void render_wall(WALL wall, CAMERA camera)
{
	VECTOR2 start_point;
	VECTOR2 end_point;

	VECTOR3 projected_start_point;
	VECTOR3 projected_end_point;

	POINT2 start_point_h;
	POINT2 start_point_l;

	POINT2 end_point_h;
	POINT2 end_point_l;

	VECTOR2 temp;

	start_point = wall.pointA;
	end_point = wall.pointB;

	start_point = camera_transform(start_point, camera);
	end_point = camera_transform(end_point, camera);

	if(start_point.y < camera.z_plane_near && end_point.y < camera.z_plane_near)
	{
		return;
	} 

	if(start_point.y < camera.z_plane_near)
	{
		temp = start_point;
		start_point = end_point;
		end_point = temp;
	}

	print_int(point2(0, 0), (int)(end_point.x*100), COLOR_YELLOW, 0, 0);
	print_int(point2(0, 8), (int)(end_point.y*100), COLOR_YELLOW, 0, 0);

	if(end_point.y < camera.z_plane_near)
	{
		end_point = intersect_v2_horizontal(start_point, end_point, camera.z_plane_near);
	}

	projected_start_point = screen_space_projection(vector3(start_point.x, WALL_HEIGHT, start_point.y), camera);
	projected_end_point = screen_space_projection(vector3(end_point.x, WALL_HEIGHT, end_point.y), camera);

	print_int(point2(0, 24), (int)(projected_end_point.x*100), COLOR_YELLOW, 0, 0);
	print_int(point2(0, 32), (int)(projected_end_point.y*100), COLOR_YELLOW, 0, 0);

	start_point_h = point2(	(int)(projected_start_point.x * get_res_x()/2) + get_res_x()/2, 
						   	(int)(projected_start_point.y * get_res_y()/2) + get_res_y()/2 );	
	
	start_point_l = point2(	(int)(projected_start_point.x * get_res_x()/2) + get_res_x()/2, 
							(int)((-projected_start_point.y) * get_res_y()/2) + get_res_y()/2);	


	end_point_h = point2(	(int)(projected_end_point.x * get_res_x()/2) + get_res_x()/2, 
							(int)(projected_end_point.y * get_res_y()/2) + get_res_y()/2);	

	end_point_l = point2(	(int)(projected_end_point.x * get_res_x()/2) + get_res_x()/2, 
							(int)((-projected_end_point.y) * get_res_y()/2) + get_res_y()/2);	


	//set_pixel(start_point_l, COLOR_ORANGE);
	//set_pixel(start_point_h, COLOR_ORANGE);
	//set_pixel(end_point_l, COLOR_ORANGE);
	//set_pixel(end_point_h, COLOR_ORANGE);

	draw_line(start_point_l, start_point_h, COLOR_ORANGE);
	draw_line(start_point_h, end_point_h, COLOR_ORANGE);
	draw_line(end_point_h, end_point_l, COLOR_ORANGE);
	draw_line(end_point_l, start_point_l, COLOR_ORANGE);
}	

void main()
{
	CAMERA camera;
	WALL wall;

	float walk_velocity;

	wall.pointA.x = 10.0f;
	wall.pointA.y = -10.0f;

	wall.pointB.x = 20.0f;
	wall.pointB.y = -15.0f;

	camera.position.x = 10.0f;
	camera.position.y = -20.0f;

	camera.pointing = 0.0f;

	camera.horizontal_fov = 90.0f;
	camera.aspect_ratio = (float)get_res_x()/(float)get_res_y();

	camera.z_plane_near = 1.0f;
	camera.z_plane_far = 100.0f;

	init_vga();
	set_graphics_mode(VGA_GRAPHICS_MODE_X);
	Keyboard_Install_Driver();

	while(!Get_Key(MAKE_ESC))
	{
		if(Get_Key(MAKE_LEFT_SHIFT))
		{
			walk_velocity = 0.1f;
		}
		else
		{
			walk_velocity = 0.06f;
		}

		if(Get_Key(MAKE_D))
		{
			camera.position = sum_v2(camera.position, rotate_v2(vector2(walk_velocity, 0.0f), zero_v2(), camera.pointing));
		}

		if(Get_Key(MAKE_A))
		{
			camera.position = sum_v2(camera.position, rotate_v2(vector2(-walk_velocity, 0.0f), zero_v2(), camera.pointing));
		}

		if(Get_Key(MAKE_W))
		{
			camera.position = sum_v2(camera.position, rotate_v2(vector2(0.0f, walk_velocity), zero_v2(), camera.pointing));
		}

		if(Get_Key(MAKE_S))
		{
			camera.position = sum_v2(camera.position, rotate_v2(vector2(0.0f, -walk_velocity), zero_v2(), camera.pointing));
		}

		if(Get_Key(MAKE_E))
		{
			camera.pointing += 0.0075f;
		}

		if(Get_Key(MAKE_Q))
		{
			camera.pointing -= 0.0075f;
		}

		fill_screen(0);

		print_int(point2(270, 0), (int)camera.position.x, COLOR_PINK, 0, 0);
		print_int(point2(270, 8), (int)camera.position.y, COLOR_PINK, 0, 0);
		print_int(point2(270, 16), (int)(camera.pointing*1000), COLOR_PINK, 0, 0);

		render_wall(wall, camera);
		
		flip_front_page();
	}
}