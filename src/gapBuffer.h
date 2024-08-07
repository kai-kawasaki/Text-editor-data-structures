#include <cassert>
#include <string>

#ifndef GAPBUFFER_H
#define GAPBUFFER_H


class GapBuffer
{
private: 
	char* buff_head; 
	char* buff_tail;
	char* gap_head;
	char* gap_tail;
	size_t gap_size;
	size_t buff_size;

	bool allocate();

public:
	GapBuffer();
	~GapBuffer();
	bool insert_char(const char c);
	bool from_file(const std::string file_name);
	bool delete_char();
	bool move_left();
	bool move_right();
	void print();
};
#endif
