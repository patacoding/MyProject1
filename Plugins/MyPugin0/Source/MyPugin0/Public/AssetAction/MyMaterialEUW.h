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


#pragma region LevelEditorMenuExtension

	void InitLevelEditorExtension();
	TSharedRef<FExtender> MyCustomLevelEditorMenuExtender(const TSharedRef<FUICommandList> UICommandList, const TArray<AActor*> SelectedActors);

	void AddLevelEditorMenuEntry(class FMenuBuilder& MenuBuilder);
	void OnMyMenuBtnClicked();

#pragma endregion

#pragma region KeyFrameOperation
	UFUNCTION(BlueprintCallable)
	void TestKeyFrame();

	UFUNCTION(BlueprintCallable)
	void TestRunPy();
#pragma endregion
	
};
