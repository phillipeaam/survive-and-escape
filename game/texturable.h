#pragma once
#include <raylib.h>

class texturable
{
protected:
	Texture2D tex{ };
public:
	void set_texture(Texture2D texture);
};
