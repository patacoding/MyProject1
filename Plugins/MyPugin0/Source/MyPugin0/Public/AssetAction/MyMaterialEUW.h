// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MyMaterialEUW.generated.h"

/**
 * 
 */
UCLASS()
class MYPUGIN0_API UMyMaterialEUW : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void CreateMaterialTest();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="My Mat EUW")
	FString MatName = TEXT("M_");
	
};
