#pragma once
#include "Wrapper.h"
class Engine
{
public:
	Engine() {};

	void register_command(Wrapper* wrapper, std::string command_name);
	int execute(std::string command_name, std::map<std::string, int> args);
private:
	std::map<std::string, Wrapper*> MapCommand;
};
