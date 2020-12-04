#include "Engine.h"

void Engine::register_command(Wrapper* wrapper, std::string command_name)
{
	if (MapCommand.find(command_name) != MapCommand.end())
		return;

	MapCommand.insert(make_pair(command_name, wrapper));
	return;
}

int Engine::execute(std::string command_name, std::map<std::string, int> args)
{
	if (MapCommand.find(command_name) == MapCommand.end())
		return -1;

	return (MapCommand.find(command_name)->second->useFunction(args));
}