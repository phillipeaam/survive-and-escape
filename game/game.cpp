#include "player.h"
#include "checkpoint.h"
#include "game_state.h"
#include "message_manager.h"
#include "trap.h"
#include "raylib.h"
#include "vector"
#include "algorithm"
#include "functional"

using namespace std;

constexpr int fps = 60;
constexpr int screen_width{ 800 };
constexpr int screen_height{ 225 };

float endgame_delay_in_seconds{ 0.6f };
float endgame_fps_counter{ 0 };
bool is_endgame_delay_finished { false };

game_state state{ running };
player player_ref{ 0, 185, screen_width };
checkpoint checkpoint_ref{ screen_width, screen_height };
message_manager messages_ref{ screen_width, screen_height };

Texture2D gameplay_background_texture{ };
Texture2D game_over_background_texture{ };
Texture2D success_background_texture{ };
Rectangle background_texture_rectangle{ 0, 0, 64, 64 };
Rectangle background_rectangle{ 0, 0, screen_width, screen_height };
Vector2 background_origin{ 0, 0 };

vector<trap> traps
{
	trap{ 110, 0, 10, screen_height },
	trap{ 180, 0, 10, screen_height },
	trap{ 320, 0, 2, screen_height },
	trap{ 390, 0, 6, screen_height },
	trap{ 460, 0, 8, screen_height },
	trap{ 600, 0, 8, screen_height },
	trap{ 670, 0, 10, screen_height }
};

// Mid screen visual reference
void display_mid_ref()
{
	constexpr auto pos_x = screen_width / 2 - 1;
	DrawRectangle(pos_x, 0, 2, screen_height, RED);
}

bool is_game_over()
{
	return any_of(traps.cbegin(), traps.cend(), [](const trap& x) { return x.has_collision(player_ref); });
}

bool is_checkpoint_reached()
{
	return checkpoint_ref.has_collision(player_ref);
}

void update_game_state()
{
	if (is_game_over())
		state = game_over;
	else if (is_checkpoint_reached())
		state = success;
	else
		state = running;
}

void manage_tries_counter()
{
	if (state == game_over)
		messages_ref.increase_tries_counter();
	else if (state == success)
		messages_ref.reset_tries_counter();
}

void reset_game_refs()
{
	player_ref.restart_to_declaration_values();
	for (auto& trap_ref : traps) trap_ref.restart_to_declaration_values();

	is_endgame_delay_finished = false;
	
	state = running;
}

void display_session_finished()
{
	messages_ref.display_restart_option();
    		
	if (!IsKeyDown(KEY_SPACE))
		return;

	manage_tries_counter();
	reset_game_refs();
}

void draw_background(const Texture2D &texture)
{
	DrawTextureTiled(texture, background_texture_rectangle, background_rectangle, background_origin, 0, 1, WHITE);
}

void draw_gameplay_elements()
{	
	draw_background(gameplay_background_texture);
	
	messages_ref.display_tries_counter();
	
	player_ref.draw();
	for (auto& trap_ref : traps) trap_ref.draw();
	checkpoint_ref.draw();
}

void manage_endgame_delay()
{
	if (endgame_fps_counter <= fps * endgame_delay_in_seconds)
	{
		endgame_fps_counter++;
		draw_gameplay_elements();
	}
	else
	{
		endgame_fps_counter = 0;
		is_endgame_delay_finished = true;
	}
}

void manage_game_finished(const function<void()>& func)
{
	if (is_endgame_delay_finished)
	{
		func();
		display_session_finished();
	}
	else
	{
		manage_endgame_delay();
	}
}

void manage_game_over()
{
	manage_game_finished([]
	{
		draw_background(game_over_background_texture);
		messages_ref.display_game_over();
	});
}

void manage_success()
{
	manage_game_finished([]
	{
		draw_background(success_background_texture);
		messages_ref.display_success();
		messages_ref.display_tries();
	});
}

void manage_gameplay()
{
	player_ref.update_position();
	player_ref.update_edges();

	for (auto& trap_ref : traps)
	{
		trap_ref.update_position();
		trap_ref.update_edges();
	}

	draw_gameplay_elements();
	update_game_state();
}

void set_textures()
{
	gameplay_background_texture = LoadTexture("sprites/gameplay-background.png");
	game_over_background_texture = LoadTexture("sprites/game-over-background.png");
	success_background_texture = LoadTexture("sprites/success-background.png");
	
	const Texture2D player_texture = LoadTexture("sprites/player.png");
	player_ref.set_texture(player_texture);
	
	const Texture2D trap_texture = LoadTexture("sprites/trap.png");
	for (auto& trap_ref : traps) trap_ref.set_texture(trap_texture);

	const Texture2D checkpoint_texture = LoadTexture("sprites/checkpoint.png");
	checkpoint_ref.set_texture(checkpoint_texture);
	
	const Image icon = LoadImageFromTexture(player_texture); 
	SetWindowIcon(icon);
}

int main()
{
	InitWindow(screen_width, screen_height, "Survive & Escape");

	set_textures();
	SetTargetFPS(fps);

    while (WindowShouldClose() == false)
    {
	    BeginDrawing();
        ClearBackground(GOLD);

	    switch (state)
	    {
	    case running:
	    	manage_gameplay();
	    	break;
	    case game_over:
	    	manage_game_over();
	    	break;
	    case success:
	    	manage_success();
	    	break;
	    }
    	
        EndDrawing();
    }
}