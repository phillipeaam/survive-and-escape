#pragma once
#include <raylib.h>
#include "displayable.h"

class message : public displayable
{
	const char* msg { };
	int pos_x { 0 };
	int pos_y { 0 };
	int font_size { 0 };
	Color color { GRAY };
public:
	void config(const char* message, int x, int y, int size, Color text_color);
	void update_message(const char* message);
	void draw() const override;
};
