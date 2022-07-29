#pragma once
#include "player.h"

class checkpoint : public texturable, displayable
{
	const int width{ 64 };
	const int height{ 64 };
	const int x_offset{ 6 };
	int x_position{ 0 };
	int y_position{ 0 };
	int x_left_edge{ 0 };
public:
	checkpoint(int screen_width, int screen_height);
	bool has_collision(const player& user_ref) const;
	void draw() const override;
};
