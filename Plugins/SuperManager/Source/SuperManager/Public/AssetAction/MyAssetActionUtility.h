// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "MyAssetActionUtility.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UMyAssetActionUtility : public UAssetActionUtility
{
	GENERATED_BODY()
public:
	UFUNCTION(CallInEditor)
	void TestFunc();

	UFUNCTION(CallInEditor)
	void DuplicateAsset(int32 NumOfDuplicates);
};
