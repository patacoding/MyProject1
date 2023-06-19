// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyQuickAssetAction.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetToolsModule.h"
#include "Misc/MessageDialog.h"

void UMyQuickAssetAction::TestFunc0()
{
	// MyPrintLog(TEXT("working"));

	// get selected assets as objects
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	// get selected assets as asset data
	TArray<FAssetData> SelectedAssets = UEditorUtilityLibrary::GetSelectedAssetData();
	

	// check if assets is used by check ref number for asset path
	TArray<FString> AssetRefrencers = UEditorAssetLibrary::FindPackageReferencersForAsset(SelectedAssets[0].GetSoftObjectPath().ToString());
	
	if(AssetRefrencers.Num() == 0)
	{
		
	}


	//fix up refrencers after operation on assets
	


	TArray<UObjectRedirector*> RedirectorsToFixArray;
	// TODO only one not an instanced object, use & to ref
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::Get().LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));

	FARFilter Filter;
	Filter.bRecursivePaths = true;
	Filter.PackagePaths.Emplace("/Game");
	Filter.ClassPaths.Emplace("ObjectRedirector");

	TArray<FAssetData> OutRedirectors;
	AssetRegistryModule.Get().GetAssets(Filter, OutRedirectors);

	for (const FAssetData& RedirectorsData:OutRedirectors)
	{
		if(UObjectRedirector* RedirectorToFix = Cast<UObjectRedirector>(RedirectorsData.GetAsset()))
		{
			RedirectorsToFixArray.Add(RedirectorToFix);
		}
	}


	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	AssetToolsModule.Get().FixupReferencers(RedirectorsToFixArray);
	
	

	
	
	
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
			// UE_LOG(LogTemp, Warning, TEXT("User pressed Ok"));
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
