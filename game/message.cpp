#include "message.h"

void message::config(const char* message, const int x, const int y, const int size, const Color text_color)
{
	msg = message;
	pos_x = x;
	pos_y = y;
	font_size = size;
	color = text_color;
}

void message::update_message(const char* message)
{
	msg = message;
}

void message::draw() const
{
	DrawText(msg, pos_x, pos_y, font_size, color);
}
