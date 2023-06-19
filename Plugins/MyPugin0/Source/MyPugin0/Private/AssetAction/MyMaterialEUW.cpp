// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyMaterialEUW.h"

#include "AssetToolsModule.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "Factories/MaterialFactoryNew.h"


void UMyMaterialEUW::CreateMaterialTest()
{
	// get selected assets as objects
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	// get selected assets as asset data
	TArray<FAssetData> SelectedAssets = UEditorUtilityLibrary::GetSelectedAssetData();

	

	UTexture2D* SelectedTexture = Cast<UTexture2D>(SelectedObjects[0]);
	
	if(!SelectedTexture)
	{
		// not valid texture asset as selected
		UE_LOG(LogTemp, Error, TEXT("not valid texture selected"));
		
		
		// return;
	}

	// create maetrial finally
	FString Assetname = TEXT("TestAssetName");

	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools"));

	UMaterialFactoryNew* MaterialFactory = NewObject<UMaterialFactoryNew>();
	UObject* CreatedMatObject = AssetToolsModule.Get().CreateAsset(Assetname, TEXT("/Game"), UMaterial::StaticClass(), MaterialFactory);

	UMaterial* CreatedMat = Cast<UMaterial>(CreatedMatObject);

	// connect socket in material editor
	CreatedMat->PostEditChange();
}
