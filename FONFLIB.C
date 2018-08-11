/*  Copyright 2018 Affonso Amendola
    
    This file is part of WumpusVGA.
    WumpusVGA is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    WumpusVGA is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with WumpusVGA.  If not, see <https://www.gnu.org/licenses/>
*/

#include <bios.h>
#include <dos.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <FONFLIB.H>

char* inttostring(int i, char b[])
{
	char const digit[] = "0123456789";
	char* p = b;
	int shifter = i;

	if(i<0)
	{
		*p++ = '-';
		i*= -1;
	}

	do
	{
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do
	{
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}

int pow_int(int number, int to_the_power_of)
{
	int i = 0;
	int holder = 0;

	if(to_the_power_of == 0)
	{
		return 1;
	}

	holder = number;
	for(i = 0; i< (to_the_power_of-1); i++)
	{
		holder = holder * number;
	}

	return holder;
}

void fputi(int number, int size, FILE * file)
{
	int i;

	int current_char;

	int middle_of_number = 0;

	for(i = (size-1); i>=0; i--)
	{
		current_char = number;
		current_char = (current_char/pow_int(10,i))%10;
		if(current_char != 0 || i == 0 || middle_of_number)
		{
			middle_of_number = 1;
			fputc(current_char+48, file);	
		}
	}
}


void * create_pointer_list()
{
	// Pointer list format in memory:
	// byte 1 = info of the current node, namely:
	// least significant bit = is this node occupied, 0 = false 1 = true
	// next bits = this node index
	// next 4 bytes = pointer to next node
	// last 4 bytes = pointer to object

	void * pointer_list_address;

	pointer_list_address = malloc(1+2*sizeof(void*));

	*(pointer_list_address) = (char)0x0;
	 
	return &pointer_list_address;
}

void pointer_list_add(void * pointer_list, void * object)
{
	void * current_node;

	char current_info;

	current_node = pointer_list;
	current_info = *current_node;

	while((current_info & 0x1) == 1)
	{
		current_node = *(current_node + 1);
		current_info = *(current_node);
	}

	*(current_node) = (char)0x1;
	*(current_node+1+sizeof(void*)) = object;
	*(current_node+1) = malloc(1+2*sizeof(void*));
} 

void * pointer_list_remove(void * pointer_list, int index)
{
	int i = 0;

	void * current_node;

	current_node = pointer_list;

	for(i=1; i<=index; i++)
	{
		current_node = *(current_node+1);
	}

	*current_node = (char) 0x0;
}

void * pointer_list_access(void * pointer_list, int index)
{
	int i = 0;

	void * current_node;

	current_node = pointer_list;

	for(i=1; i<=index; i++)
	{
		current_node = *(current_node+1);
	}

	return *(current_node + sizeof(void*) + 1);
}


