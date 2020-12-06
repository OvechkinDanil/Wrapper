#include "Wrapper.h"

template<typename baseClass, class... Arguments>
Wrapper::Wrapper(baseClass* instance, int(baseClass::*meth)(Arguments...), const std::vector<std::pair<std::string, int>> argVec)
{
	if (sizeof...(Arguments) != argVec.size())
		return;

	AddArguments(argVec);

	func = [this, instance, meth](const std::vector<int>& v)
	{
		return (call(instance, meth, v, std::make_index_sequence<sizeof...(Arguments)>{}));
	};
}

template<class... Arguments>
Wrapper::Wrapper(int(*meth)(Arguments...), const std::vector<std::pair<std::string, int>> argVec)
{
	if (sizeof...(Arguments) != argVec.size())
		return;

	AddArguments(argVec);

	func = [this, meth](const std::vector<int>& v)
	{
		return (call(meth, v, std::make_index_sequence<sizeof...(Arguments)>{}));
	};
}

void Wrapper::AddArguments(const std::vector<std::pair<std::string, int>> argVec)
{
	for (auto& arg : argVec)
	{
		argName.push_back(arg.first);
		argDefaultValues.push_back(arg.second);
	}
}

int Wrapper::useFunction(std::map<std::string, int> MapArguments)
{
	std::vector<int> args;
	
	if (MapArguments.size() != argName.size())
		return func(argDefaultValues);

	for (auto& name : argName)
	{
		if (MapArguments.find(name) == MapArguments.end())
		{
			return func(argDefaultValues);
		}
		
		args.push_back(MapArguments.find(name)->second);
	}

	return func(args);
}

template<typename baseClass, typename Meth, size_t... Is>
int Wrapper::call(baseClass* bc, Meth method, std::vector<int>& argVec, std::index_sequence<Is...>)
{
	return ((bc->*method)(argVec[Is]...));
}

template<typename Func, size_t... Is>
int Wrapper::call(Func func, std::vector<int>& argVec, std::index_sequence<Is...>)
{
	return ((*func)(argVec[Is]...));
}
	