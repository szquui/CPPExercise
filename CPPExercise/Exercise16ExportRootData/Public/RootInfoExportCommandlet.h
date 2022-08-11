#pragma once

#include "Commandlets/Commandlet.h"
#include "RootInfoExportCommandlet.generated.h"

UCLASS()
class URootInfoExportCommandlet : public UCommandlet
{
	GENERATED_UCLASS_BODY()

public:
	virtual int32 Main(const FString& Params) override;
};