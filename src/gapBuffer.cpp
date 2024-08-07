#include "gapBuffer.h"
#include <iostream>
#include <fstream>

GapBuffer::GapBuffer()
{
	buff_size = 20;
	gap_size = buff_size;
	buff_head = new char[buff_size];
	gap_head = buff_head;
	buff_tail = buff_head + buff_size - 1;
	gap_tail = buff_tail;
}



GapBuffer::~GapBuffer()
{
	char* temp_buffer = buff_head;
	buff_head = nullptr;
	buff_tail = nullptr;
	gap_head = nullptr;
	gap_tail = nullptr;
	delete temp_buffer;
}


bool GapBuffer::move_left()
{
	if(gap_head == buff_head)
	{
		return false;
	}
	*gap_tail = *(gap_head - 1);
	gap_head --;
	gap_tail --;

	return true;
}

bool GapBuffer::move_right()
{
	if(gap_tail == buff_tail)
	{
		return false;
	}

	*gap_head = *(gap_head + 1);
	gap_head ++;
	gap_tail ++;
	
	return true;

}

bool GapBuffer::delete_char()
{
	if(gap_tail == buff_tail)
	{
		return false;
	}

	gap_head --;
	gap_size ++;
	return true;
}


bool GapBuffer::allocate()
{
	gap_size += 50;
	buff_size += gap_size;

	char* old_buffer = buff_head;
	char* copier = buff_head; 

	buff_head = new char[buff_size]; 
	char* temp_buf = buff_head;
	char* new_buff = buff_head;

	for(; copier != gap_head; copier ++)
	{
		*new_buff = *copier;
		new_buff ++;
	}

	*new_buff = *copier;
	copier = gap_tail;
	gap_head = new_buff;
	gap_tail = new_buff + gap_size;
	new_buff = gap_tail;

	for(; copier != buff_tail; copier++)
	{
		*new_buff = *copier;
		new_buff ++;
	}

	buff_tail = new_buff;
	delete old_buffer;

	return true;

}

bool GapBuffer::insert_char(const char c)
{
	*gap_head = c;
	gap_size --;

	if(gap_size == 0)
	{
		allocate();
	}

	gap_head ++;
	return true;
}

void GapBuffer::print()
{

	for(char* printer = buff_head; printer != gap_head; printer ++)
	{
		 std::cout<< *printer;
	}

	for(char* printer = gap_head; printer != gap_tail; printer ++)
	{
		 std::cout<< "_";
	}

	if(gap_head == gap_tail && gap_head == buff_tail && gap_size == 0)
	{
		std::cout<< *gap_head;
	}
	else
	{
		std::cout<< "_";
	}

	if(gap_tail == buff_tail)
	{
		std::cout<< '\n';
		return;
	}

	for(char* printer = gap_tail + 1; printer != buff_tail; printer ++)
	{
		 std::cout<< *printer;
	}
	std::cout<< *buff_tail<<'\n';
}

bool GapBuffer::from_file(const std::string file_name)
{
	std::ifstream file_reader(file_name);
	if(!file_reader)
	{
		std::cout << "Failed to open " << file_name << '\n';
		return false;
	}


	char c;

	while(file_reader.get(c))
	{
		insert_char(c);
	}
	return true;
}

