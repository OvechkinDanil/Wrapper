#pragma once
#include <functional>
#include <vector>
#include <map>
#include <iostream>
#include <functional>




class Wrapper
{
public:
	template<typename baseClass, class... Arguments>
	Wrapper(baseClass* instance, int(baseClass::* meth)(Arguments...), const std::vector<std::pair<std::string, int>> argVec);
	template<class... Arguments>
	Wrapper(int(*meth)(Arguments...), const std::vector<std::pair<std::string, int>> argVec);

	int useFunction(std::map<std::string, int> MapArguments);

private:

	template<typename baseClass, typename Meth, size_t... Is>
	int call(baseClass* bc, Meth method, std::vector<int>& argVec, std::index_sequence<Is...>);

	template<typename Func, size_t... Is>
	int call(Func func, std::vector<int>& argVec, std::index_sequence<Is...>);

	void AddArguments(const std::vector<std::pair<std::string, int>> argVec);

	std::vector<std::string> argName;
	std::vector<int> argDefaultValues;
	std::function<int(const std::vector<int>& v)> func;
};