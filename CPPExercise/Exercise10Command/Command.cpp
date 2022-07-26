#include "Command.h"
#include <iostream>

void Command::Call(std::string& InStr)
{
	std::string FuncName, Params;
	GetNameAndParams(InStr, FuncName, Params);
	pFunc Func = CommandList[FuncName];
	Func(Params);
}

void Command::RegisterFunc(pFunc InFunc, const std::string& FuncName)
{
	CommandList[FuncName] = InFunc;
}

void Command::GetNameAndParams(const std::string& InStr, std::string& OutFuncName, std::string& OutParams)
{
	int Index = InStr.find(" ");
	if (Index == InStr.npos)
	{
		OutFuncName = InStr;
		OutParams = "";
	}
	else
	{
		OutFuncName = InStr.substr(0, Index);
		OutParams = InStr.substr(Index + 1, InStr.size());
	}
}


void PrintHelloAndNum(const std::string& InParams)
{
	std::cout << "Hello And " << InParams << "\n";
}

void CalNumFactorial(const std::string& InParams)
{
	int Num = atoi(InParams.c_str());
	int Result = 1;
	while (Num > 0)
	{
		Result = Result * Num;
		--Num;
	}
	std::cout << "Num " << InParams << " factorial value " << Result << "\n";
}

//int main()
//{
//	Command MyCommand;
//	MyCommand.RegisterFunc(PrintHelloAndNum, "PrintHelloAndNum");
//	MyCommand.RegisterFunc(CalNumFactorial, "CalNumFactorial");
//	std::string CommondLine;
//	std::cout << "Input Command:\n";
//	std::getline(std::cin, CommondLine);
//	MyCommand.Call(CommondLine);
//	return 1;
//}