#pragma once
#include "displayable.h"
#include "limiter.h"
#include "movable.h"
#include "restartable.h"
#include "texturable.h"

class player : public limiter, public restartable, public movable, public texturable, displayable
{
	int x_pos_max{ 0 };
	const int length{ 40 };
public:
	int x_direction_step{ 8 };
	player(int pos_x, int pos_y, int screen_width);
	void update_edges();
	void draw() const override;
	void update_position() override;
};
