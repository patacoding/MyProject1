// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EditorUtilityWidget.h"
#include "MyMaterialEUW.generated.h"

/**
 * 
 */


class FJsonObject;

USTRUCT(BlueprintType, Category="MyJsonStruct")
struct FMyJsonStruct
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MyJsonStruct")
	FString MyJsonStrName = "Nelson";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MyJsonStruct")
	int32 MyJsonInt32 = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MyJsonStruct")
	float MyJsonFloat = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="MyJsonStruct")
	bool MyJsonBool = true;
	
};



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
#pragma endregion

#pragma region TestPyRun
	
	UFUNCTION(BlueprintCallable)
	void TestRunPy();

#pragma endregion 


#pragma region TestJson

	static void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool bOutSuccess, FString& OutInfoMessage);
#pragma endregion
};
