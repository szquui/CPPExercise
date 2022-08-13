#pragma once
#include "CoreMinimal.h"
#include "Misc/FileHelper.h"
#include "Engine/DataTable.h"

#define TAB_FILE_DATA_SINGLE_KEY(T, Key)\
T GetKey(){return Key};\
typedef T TKeyType;\

#define TAB_FILE_DATA_REGISTER(Data, Name)\
Register(Data, Name);\

#define TAB_FILE_DATA(TabDataStruct) struct TabDataStruct : FTabData

#define TAB_FILE_WITH_PATH(TabFile, TabData, Path)\
struct TabFile\
{\
public:\
	TabFile()\
	{\
		FString FilePath = FPaths::ProjectDir() + FString(Path);\
		FString Content;\
		if (FFileHelper::LoadFileToString(Content, *FilePath))\
		{\
			TArray<FString> ContentLines;\
			Content.ParseIntoArray(ContentLines, TEXT("\r\n"), true);\
			TArray<FString> Columns; \
			ContentLines[0].ParseIntoArray(Columns, TEXT("\t"), true); \
\
			for (int i = 0; i < ContentLines.Num(); ++i)\
			{\
				TabData Line = TabData();\
				Line.RegisterParams(); \
				Line.Load(ContentLines[i], Columns);\
				Data.FindOrAdd(Line.GetKey(), Line); \
			}\
		}\
	}\
public:\
	TMap<TabData::TKeyType, TabData> Data; \
};\


struct FTabData
{
public:
	template<typename T>
	void Register(T& Value, const FString& Key);
	void Load(const FString& Line, const TArray<FString> Columns);
	virtual void RegisterParams() {};

private:
	TMap<FName, int*> IntData;
	TMap<FName, FString*> StringData;
};

void FTabData::Load(const FString& Line, const TArray<FString> Columns)
{
	TArray<FString> Values;
	Line.ParseIntoArray(Values, TEXT("\t"), true);

	for (int i = 0; i < Names.Num(); i++)
	{
		if (FString** Temp = StringData.Find(FName(Names[i])))
		{
			**Temp = Values[i];
		}
		else
		{
			*IntData.FindChecked(FName(Names[i])) = FCString::Atoi(*Values[i]);
		}
	}

}

template<typename T> inline void FTabData::Register(T& Value, const FString& Key)
{

}

template<> inline void FTabData::Register<FString>(FString& Value, const FString& Key)
{
	StringData.FindOrAdd(FName(Key), &Value);
}


template<> inline void FTabData::Register<int>(int& Value, const FString& Key)
{
	IntData.FindOrAdd(FName(Key), &Value);
}