// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyEUW0.h"
#include "EditorAssetLibrary.h"
#include "Tracks/MovieSceneEventTrack.h"
#include "MovieSceneTrack.h"
#include "Sections/MovieSceneEventSection.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"

#include "Kismet/GameplayStatics.h"

#pragma region MyEUW0
void UMyEUW0::TestFun()
{
	UE_LOG(LogTemp, Warning, TEXT("TestFun"));

	TArray<AActor*> sequences;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), sequences);

	UE_LOG(LogTemp, Display, TEXT("sequences.Num() = %d"), sequences.Num());

	if (sequences.Num() == 0)
	{
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("sequnces[0] = %s"), *sequences[0]->GetName());
	

	UEditorAssetLibrary::CheckoutAsset("/Game/NewLevelSequence");
	UObject* mySequenceObject = UEditorAssetLibrary::LoadAsset("/Game/NewLevelSequence");
	UMovieSceneSequence* myMovieSceneSequence = Cast<UMovieSceneSequence>(mySequenceObject);
	UMovieScene* myMovieScene = myMovieSceneSequence->GetMovieScene();

	// Fetch blueprint and add as spawnable in sequence
	UObject* myBlueprintObject = UEditorAssetLibrary::LoadAsset("/Game/Test/BP_EventCubo0Pawn");
	FGuid mySpanwableGuid = myMovieSceneSequence->CreateSpawnable(myBlueprintObject);
	
	// Add an event track to the spawnable
	UMovieSceneTrack* myTrack = myMovieScene->AddTrack(UMovieSceneEventTrack::StaticClass(), mySpanwableGuid);
	
	// Add a section to the event track
	UMovieSceneSection* mySection = myTrack->CreateNewSection();
	myTrack->AddSection(*mySection);
	UMovieSceneEventSection* myEventSection = Cast<UMovieSceneEventSection>(mySection);
	
	
}



#pragma endregion