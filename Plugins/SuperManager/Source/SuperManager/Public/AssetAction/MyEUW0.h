// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "MyEUW0.generated.h"

/**
 * 
 */
UCLASS()
class SUPERMANAGER_API UMyEUW0 : public UEditorUtilityWidget
{
	GENERATED_BODY()
public:

#pragma region MyEUW0

	UFUNCTION(BlueprintCallable)
	void TestFun();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEUW0")
	FString TestStr = TEXT("TestStr");
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEUW0")
	bool bMark = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MyEUW0")
	class ALevelSequenceActor* LevelSequenceActor;

	
#pragma endregion 
	
};
