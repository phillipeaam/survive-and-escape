#include "checkpoint.h"
#include <raylib.h>

checkpoint::checkpoint(const int screen_width, const int screen_height)
{
	x_position = screen_width - width;
	y_position = screen_height - height;
	x_left_edge = x_position + x_offset;
}

bool checkpoint::has_collision(const player& user_ref) const
{
	return x_left_edge <= user_ref.x_right_edge;
}

void checkpoint::draw() const
{
	DrawTexture(tex, x_position, y_position, WHITE);
}
