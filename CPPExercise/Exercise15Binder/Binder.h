#pragma once
#include <string>
#include <map>

template <class T> 
class Binder
{
public:
	typedef void (T::* FuncType)(void*);
	typedef void (*StaticFuncType)(void*);

public:
	void BindVar(const std::string InName, int InOffset);
	void BindFunc(const std::string InName, FuncType InFunc);
	void BindStaticFunc(const std::string InName, StaticFuncType InStaticFunc);
	
	template <typename Type>
	Type* FindVar(T* InClass, const std::string InName);

	void CallFunc(T* InClass, const std::string InName, void* InParams);
	void CallStaticFunc(const std::string InName, void* InParams);

private:
	std::map<std::string, int> Vars;
	std::map<std::string, FuncType> Funcs;
	std::map<std::string, StaticFuncType> StaticFuncs;
};


