#pragma once
#include "limiter.h"
#include "player.h"

class trap : public restartable, public movable, public texturable, limiter, displayable
{
	int y_pos_max{ 0 };
	const int length{ 50 };
public:
	int y_direction_step{ 0 };
	trap(int pos_x, int pos_y, int y_step, int screen_height);
	void update_edges();
	bool has_collision(const player& user_ref) const;
	void draw() const override;
	void update_position() override;
};
