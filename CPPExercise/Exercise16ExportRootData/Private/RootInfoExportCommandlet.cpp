#include "RootInfoExportCommandlet.h"
#include "Engine/ObjectLibrary.h"
#include "BlueprintFunctionLibrary/AnimBlueprintFunctionLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(ExportLog, Log, All);

URootInfoExportCommandlet::URootInfoExportCommandlet(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	LogToConsole = true;
}

int32 URootInfoExportCommandlet::Main(const FString& Params)
{
	UE_LOG(ExportLog, Display, TEXT("Start URootInfoExportCommandlet"));
	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(UAnimSequence::StaticClass(), false, GIsEditor);
	if (ObjectLibrary)
	{
		ObjectLibrary->AddToRoot();
	}

	FString Path = FString("/Game");
	FParse::Value(*Params, TEXT("path="), Path);
	UE_LOG(ExportLog, Display, TEXT("Export path: %s"), *Path);

	ObjectLibrary->LoadAssetDataFromPath(Path);
	TArray<FAssetData> AssetDatas;
	ObjectLibrary->GetAssetDataList(AssetDatas);

	int32 FileNum = 0;
	for (FAssetData& AssetData : AssetDatas)
	{
		FString FilePath = FPaths::ProjectSavedDir() + FString::FromInt(FileNum) + "RootMotionInfo.txt";
		UAnimBlueprintFunctionLibrary::ExportRootLocationAndYawToJSON((UAnimSequence*)AssetData.GetAsset(), FilePath);
		++FileNum;
	}

	return 0;
}
