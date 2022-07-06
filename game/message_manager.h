#pragma once
#include "string"
#include "message.h"

class message_manager
{
	int screen_width{ 0 };
	int screen_height{ 0 };
	int tries_counter{ 0 };
	std::string tries_amount{ "0" };
	message success_message{};
	message game_over_message{};
	message restart_option_message{};
	message tries_label{};
	message tries_amount_label{};
	void set_tries_label();
	void set_tries_amount_label();
	void set_success_message();
	void set_game_over_message();
	void set_restart_option_message();
	void update_tries_amount_message();
public:
	message_manager(int screen_width, int screen_height);
	void reset_tries_counter();
	void increase_tries_counter();
	void display_tries() const;
	void display_success() const;
	void display_game_over() const;
	void display_restart_option() const;
};
