#include "message_manager.h"
#include "string"
#include "iostream"

message_manager::message_manager(const int screen_width, const int screen_height)
{
	message_manager::screen_width = screen_width;
	message_manager::screen_height = screen_height;

	set_tries_label();
	set_tries_amount_label();
	set_success_message();
	set_game_over_message();
	set_restart_option_message();	
}

void message_manager::reset_tries_counter()
{
	tries_counter = 0;
	update_tries_amount_message();
}

void message_manager::increase_tries_counter()
{
	tries_counter++;
	update_tries_amount_message();
}

void message_manager::set_tries_label()
{
	const auto msg = "Tries:";
	constexpr auto font_size = 20;
	constexpr auto pos_y = 10;
	constexpr auto pos_x = 10;

	tries_label.config( msg, pos_x, pos_y, font_size, BLACK );
}

void message_manager::set_tries_amount_label()
{
	const auto msg = "0";
	constexpr auto font_size = 20;
	constexpr auto pos_y = 30;
	constexpr auto pos_x = 26;

	tries_amount_label.config( msg, pos_x, pos_y, font_size, DARKBLUE );
}

void message_manager::set_success_message()
{
	const auto msg = "You've survived & escaped!\n   ~~ Congratulations! ~~";
	constexpr auto font_size = 40;
	constexpr auto line_space = font_size / 3;
	const auto pos_x = screen_width / 2 - 280;
	const auto pos_y = screen_height / 2 - font_size - line_space;

	success_message.config( msg, pos_x, pos_y, font_size, DARKGREEN );
}

void message_manager::set_game_over_message()
{
	const auto msg = "Game Over!"; 
	constexpr auto font_size = 40;
	const auto pos_x = screen_width / 2 - 112;
	const auto pos_y = screen_height / 2 - font_size / 2;

	game_over_message.config( msg, pos_x, pos_y, font_size, RED );
}

void message_manager::set_restart_option_message()
{
	const auto msg = "-> Press SPACEBAR to restart <-";
	constexpr auto font_size = 20;
	const auto pos_x = screen_width / 2 - 176;
	const auto pos_y_float = static_cast<float>(screen_height) * 0.86f;
	const auto pos_y = static_cast<int>(pos_y_float);
	
	restart_option_message.config( msg, pos_x, pos_y, font_size, DARKGRAY );
}

void message_manager::update_tries_amount_message()
{
	tries_amount = std::to_string(tries_counter);
	const auto message = tries_amount.c_str();
	tries_amount_label.update_message(message);
}

void message_manager::display_tries() const
{
	tries_label.draw();
	tries_amount_label.draw();
}

void message_manager::display_success() const
{
	success_message.draw();
}

void message_manager::display_game_over() const
{
	game_over_message.draw();
}

void message_manager::display_restart_option() const
{
	restart_option_message.draw();
}