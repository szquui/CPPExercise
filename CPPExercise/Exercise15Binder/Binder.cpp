#include "Binder.h"
#include <iostream>

template<class T>
void Binder<T>::BindVar(const std::string InName, int InOffset)
{
	Vars[InName] = InOffset;
}

template<class T>
void Binder<T>::BindFunc(const std::string InName, FuncType InFunc)
{
	Funcs[InName] = InFunc;
}

template<class T>
void Binder<T>::BindStaticFunc(const std::string InName, StaticFuncType InStaticFunc)
{
	StaticFuncs[InName] = InStaticFunc;
}

template<class T>
void Binder<T>::CallFunc(T* InClass, const std::string InName, void* InParams)
{
	auto Iter = Funcs.find(InName);
	if (Iter == Funcs.end())
		return;

	(*InClass.*Funcs[InName])(InParams);
}

template<class T>
void Binder<T>::CallStaticFunc(const std::string InName, void* InParams)
{
	auto Iter = StaticFuncs.find(InName);
	if (Iter == StaticFuncs.end())
		return;

	(*StaticFuncs[InName])(InParams);
}

template<class T>
template<typename Type>
Type* Binder<T>::FindVar(T* InClass, const std::string InName)
{
	auto Iter = Vars.find(InName);
	if (Iter == Vars.end())
		return nullptr;

	return (Type*)(InClass + Vars[InName]);
}