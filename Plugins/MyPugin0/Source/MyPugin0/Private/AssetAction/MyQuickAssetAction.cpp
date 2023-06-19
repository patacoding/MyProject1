// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyQuickAssetAction.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "Misc/MessageDialog.h"

void UMyQuickAssetAction::TestFunc0()
{
	// MyPrintLog(TEXT("working"));
}

void UMyQuickAssetAction::DuplicateAsset()
{
	TArray<FAssetData> SelectedAssets = UEditorUtilityLibrary::GetSelectedAssetData();
	if (SelectedAssets.Num() == 0)
	{
		// MyPrintLog(TEXT("No assets selected"));
		const FText MsgTitle = FText::FromString(TEXT("Warning"));
		EAppReturnType::Type UserInputResult = FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("No assets selected")), &MsgTitle);

		if(UserInputResult == EAppReturnType::Type::Ok)
		{
			UE_LOG(LogTemp, Warning, TEXT("User pressed Ok"));
		}
		
		return;
	}

	for (const FAssetData& AssetData : SelectedAssets)
	{
		const FString SourceAssetPath = AssetData.GetSoftObjectPath().ToString();
		const FString NewDuplicateAssetName = AssetData.AssetName.ToString() + TEXT("_Duplicate");

		const FString NewPathName = FPaths::Combine(AssetData.PackagePath.ToString(), NewDuplicateAssetName);


		if(UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
		{
			UEditorAssetLibrary::SaveAsset(NewPathName, false);
		};
	}

	// MyPrintLog("Successfully duplicated ");
}
