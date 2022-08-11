// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintFunctionLibrary/AnimBlueprintFunctionLibrary.h"

#include "Animation/AnimSequence.h"
#include "Animation/AnimationAsset.h"
#include "Animation/AnimMetaData.h"
#include "Animation/AnimNotifies/AnimNotifyState.h" 
#include "Animation/Skeleton.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "BonePose.h" 

#include "AnimationRuntime.h"

#include "AnimationUtils.h"
#include "Animation/AnimSequenceHelpers.h"
#include "Misc/MessageDialog.h"

#include "Json.h"
#include "JsonObjectConverter.h"

DEFINE_LOG_CATEGORY_STATIC(LogAnimBlueprintLibrary, Verbose, All);

#define LOCTEXT_NAMESPACE "AnimBlueprintFunctionLibrary"
void UAnimBlueprintFunctionLibrary::ExportRootLocationAndYawToJSON(UAnimSequence* InAnimSequence, FString InFilePath)
{
	FAnimExportStruct ExportData;
	ExportData.AnimName = InAnimSequence->GetName();
	ExportData.Path = InAnimSequence->GetFullName();

	int32 AnimNumFrames = InAnimSequence->GetNumberOfFrames();
	const FName RootName = FName(TEXT("root"));
	for (int32 Frames = 0; Frames < AnimNumFrames; ++Frames)
	{
		FTransform PoseTransform;
		GetBonePoseForFrame(InAnimSequence, RootName, Frames, false, PoseTransform);
		float FramesTime = 0.0f;
		GetTimeAtFrame(InAnimSequence, Frames, FramesTime);
		FAnimDataStruct AnimData;
		AnimData.Time = FramesTime;
		FVector PoseLocation = PoseTransform.GetLocation();
		AnimData.X = PoseLocation.X;
		AnimData.Y = PoseLocation.Y;
		AnimData.Z = PoseLocation.Z;
		AnimData.Yaw = PoseTransform.Rotator().Yaw;
		ExportData.Data.Push(AnimData);
	}

	FString JSON;
	if (FJsonObjectConverter::UStructToJsonObjectString(ExportData, JSON))
	{
		FFileHelper::SaveStringToFile(JSON, *InFilePath);
	}
}
#undef LOCTEXT_NAMESPACE