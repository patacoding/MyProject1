// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyMaterialEUW.h"

#include "AssetToolsModule.h"
#include "EditorUtilityLibrary.h"
#include "EditorAssetLibrary.h"
#include "Factories/MaterialFactoryNew.h"

#include "LevelEditor.h"

#include "LevelSequenceActor.h"
#include "MovieSceneSequencePlayer.h"
#include "Kismet/GameplayStatics.h"

#include "Editor/MovieSceneTools/Public/KeyframeTrackEditor.h"
#include "LevelSequence.h"
#include "MovieScene.h"
#include "MovieSceneTrack.h"
#include "MovieSceneSection.h"
#include "Tracks/MovieScene3DTransformTrack.h"


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

void UMyMaterialEUW::InitLevelEditorExtension()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(TEXT("LevelEditor"));

	TArray<FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors> LevelEditorMenuExtenders = LevelEditorModule.GetAllLevelViewportContextMenuExtenders();

	LevelEditorMenuExtenders.Add(FLevelEditorModule::FLevelViewportMenuExtender_SelectedActors::CreateUObject(this, &UMyMaterialEUW::MyCustomLevelEditorMenuExtender));

	
}

TSharedRef<FExtender> UMyMaterialEUW::MyCustomLevelEditorMenuExtender(const TSharedRef<FUICommandList> UICommandList, const
	TArray<AActor*> SelectedActors)
{
	UE_LOG(LogTemp, Warning, TEXT("SelectedActors"));
	TSharedRef<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension(
		FName("MyActorOptions"),
		EExtensionHook::Before,
		UICommandList,
		FMenuExtensionDelegate::CreateUObject(this, &UMyMaterialEUW::AddLevelEditorMenuEntry)
		);
	
	if(SelectedActors.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("SelectedActors.Num() > 0"));
		MenuExtender->AddMenuExtension(
			FName("MyActorOptions"),
			EExtensionHook::Before,
			UICommandList,
FMenuExtensionDelegate::CreateUObject(this, &UMyMaterialEUW::AddLevelEditorMenuEntry)
			);
	}
	return MenuExtender;
}

void UMyMaterialEUW::AddLevelEditorMenuEntry(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		FText::FromString(TEXT("My Custom OP 1")),
		FText::FromString(TEXT("op1 meomoe")),
		FSlateIcon(),
		FExecuteAction::CreateUObject(this, &UMyMaterialEUW::OnMyMenuBtnClicked)
		);
}


void UMyMaterialEUW::OnMyMenuBtnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("OnMyMenuBtnClicked"));
}

void UMyMaterialEUW::TestKeyFrame()
{
	UE_LOG(LogTemp, Warning, TEXT("TestKeyFrame1"));

	
	UObject* mySequenceObject = UEditorAssetLibrary::LoadAsset("/Game/NewLevelSequence2");
	UMovieSceneSequence* myMovieSceneSequence = Cast<UMovieSceneSequence>(mySequenceObject);
	UMovieScene* myMovieScene = myMovieSceneSequence->GetMovieScene();

	//

	TSubclassOf<AActor> ClassToFind = AActor::StaticClass();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

	UE_LOG(LogTemp, Warning, TEXT("FoundActors.Num() %d"), FoundActors.Num());

	// for (auto Actor : FoundActors)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("Actor %s"), *Actor->GetName());
	// }

	UE_LOG(LogTemp, Warning, TEXT("actor 70 name %s"), *FoundActors[70]->GetName());

	
	// get guid of actor
	// FGuid Guid = FoundActors[0]->GetUniqueID();
	// UMovieSceneTrack* MovieSceneTrack = myMovieScene->FindTrack(UMovieScene3DTransformTrack::StaticClass(), Guid);
	// UMovieScene3DTransformTrack* MovieScene3DTransformTrack = myMovieScene->AddTrack(UMovieScene3DTransformTrack::StaticClass(), Guid);
	// UMovieSceneTrack* myTrack = myMovieScene->AddTrack(UMovieScene3DTransformTrack::StaticClass(), Guid);
	//
	// UMovieScene3DTransformTrack* my3DTransformTrack = Cast<UMovieScene3DTransformTrack>(myTrack);


	
}