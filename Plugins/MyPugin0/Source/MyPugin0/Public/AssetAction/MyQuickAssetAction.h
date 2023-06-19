// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "MyQuickAssetAction.generated.h"

/**
 * 
 */
UCLASS()
class MYPUGIN0_API UMyQuickAssetAction : public UAssetActionUtility
{
	GENERATED_BODY()

public:
	UFUNCTION(CallInEditor)
	void TestFunc0();

	UFUNCTION(CallInEditor)
	void DuplicateAsset();
};
