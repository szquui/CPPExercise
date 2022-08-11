// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationBlueprintLibrary.h"
#include "AnimBlueprintFunctionLibrary.generated.h"

USTRUCT()
struct FAnimDataStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	double Time = 0;

	UPROPERTY()
	double X = 0;

	UPROPERTY()
	double Y = 0;

	UPROPERTY()
	double Z = 0;

	UPROPERTY()
	double Yaw = 0;
};

USTRUCT()
struct FAnimExportStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	FString Path;

	UPROPERTY()
	FString AnimName;

	UPROPERTY()
	TArray<FAnimDataStruct> Data;
};


UCLASS()
class IRONDESERTEDITOR_API UAnimBlueprintFunctionLibrary : public UAnimationBlueprintLibrary
{
	GENERATED_BODY()

public:
	// Export root location and yaw to json
	UFUNCTION(BlueprintCallable, Category = "AnimationBlueprintLibrary|Curves")
	static void ExportRootLocationAndYawToJSON(UAnimSequence* InAnimSequence, FString InFilePath);
};
