#pragma once
#include <string>
#include <map>

typedef void (* pFunc)(const std::string&);

class Command
{
public:
	void Call(std::string &InStr);
	void RegisterFunc(pFunc InFunc, const std::string& FuncName);

private:
	void GetNameAndParams(const std::string &InStr, std::string &OutFuncName, std::string& OutParams);

private:
	std::map<std::string, pFunc> CommandList;
};

