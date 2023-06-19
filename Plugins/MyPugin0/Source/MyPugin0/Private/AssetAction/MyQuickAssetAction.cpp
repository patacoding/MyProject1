// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyQuickAssetAction.h"

void UMyQuickAssetAction::TestFunc0()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TestFunc0"));
		
	}
}
