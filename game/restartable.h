#pragma once

class restartable
{
protected:
	int initial_x_position{ 0 };
	int initial_y_position{ 0 };
public:
	int x_position{};
	int y_position{};
	void restart_to_declaration_values();
};
