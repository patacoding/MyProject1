// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyAssetActionUtility.h"

#include "WorldPartition/ContentBundle/ContentBundleLog.h"

#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "Misc/MessageDialog.h"


void UMyAssetActionUtility::TestFunc()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Red, TEXT("TestFunc working!"));
	}
	
	UE_LOG(LogTemp, Log, TEXT("TestFunc log working!"));

	
}

void UMyAssetActionUtility::DuplicateAsset(int32 NumOfDuplicates)
{
	if(NumOfDuplicates <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("numOfDuplicates <= 0"));
		return;
	}

	TArray<FAssetData> SelectedAssetDatas =  UEditorUtilityLibrary::GetSelectedAssetData();
	if(SelectedAssetDatas.Num() <= 0)
	{
		UE_LOG(LogTemp, Log, TEXT("SelectedAssetData.Num() <= 0"));

		// FText MsgTitle = FText::FromString(TEXT("Warning!!"));
		// FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("No asset selected!")));
		return;
	}

	uint32 Counter = 0;

	for (const FAssetData& SelectedAssetData:SelectedAssetDatas)
	{
		for(int32 i=0; i<NumOfDuplicates;i++)
		{
			const FString SourceAssetPath = SelectedAssetData.GetSoftObjectPath().ToString();
			const FString NewDuplicatedName = SelectedAssetData.AssetName.ToString() + TEXT("_") + FString::FromInt(i+1);
			
			const FString NewPathName = FPaths::Combine( SelectedAssetData.PackagePath.ToString(),NewDuplicatedName);

			if(
			UEditorAssetLibrary::DuplicateAsset(SourceAssetPath, NewPathName))
			{
				UEditorAssetLibrary::SaveAsset(NewPathName, false
					);
				++Counter;
			};
		
			
		}
	}

	UE_LOG(LogTemp, Log, TEXT("duplicated selected assets: %d"), Counter);

	
}

