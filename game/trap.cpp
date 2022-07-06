#include "trap.h"
#include "player.h"
#include <raylib.h>

trap::trap(const int pos_x, const int pos_y, const int y_step, const int screen_height)
{
	initial_x_position = pos_x;
	initial_y_position = pos_y;
	
	restart_to_declaration_values();

	y_direction_step = y_step;
	y_pos_max = screen_height;
}

void trap::set_texture(const Texture2D texture)
{
	tex = texture;
}

void trap::update_edges()
{
	x_left_edge = x_position;
	x_right_edge = x_position + length;
	y_upper_edge = y_position;
	y_bottom_edge = y_position + length;
}

bool trap::has_collision(const player& user_ref) const
{
	return
		y_bottom_edge >= user_ref.y_upper_edge &&
		y_upper_edge <= user_ref.y_bottom_edge &&
		x_left_edge <= user_ref.x_right_edge &&
		x_right_edge >= user_ref.x_left_edge;
}

void trap::draw() const
{
	DrawTexture(tex, x_position, y_position, WHITE);
}

void trap::update_position()
{
	y_position += y_direction_step;
	
	if (y_position > y_pos_max - length || y_position < 0)
	{
	    y_direction_step = -y_direction_step;
	}
}
