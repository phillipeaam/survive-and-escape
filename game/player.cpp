#include "player.h"
#include <raylib.h>

player::player(const int pos_x, const int pos_y, const int screen_width)
{
	initial_x_position = pos_x;
	initial_y_position = pos_y;
	
	restart_to_declaration_values();

	x_pos_max = screen_width;
}

void player::update_edges()
{
	x_left_edge = x_position;
	x_right_edge = x_position + length;
	y_upper_edge = y_position;
	y_bottom_edge = y_position + length;
}

void player::draw() const
{
	DrawTexture(tex, x_position, y_position, WHITE);
}

void player::update_position()
{
	if (IsKeyDown(KEY_D) && x_position < x_pos_max)
		x_position += x_direction_step;
	else if (IsKeyDown(KEY_A) && x_position > 0)
		x_position -= x_direction_step;
}
