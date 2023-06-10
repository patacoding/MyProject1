// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetAction/MyEUW0.h"

#include <LevelSequenceActor.h>
#include <LevelSequencePlayer.h>
#include <MovieSceneSequencePlayer.h>

#include "Kismet/GameplayStatics.h"

#pragma region MyEUW0
void UMyEUW0::TestFun()
{
	UE_LOG(LogTemp, Warning, TEXT("TestFun"));

	TArray<AActor*> sequences;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), sequences);

	UE_LOG(LogTemp, Display, TEXT("sequences.Num() = %d"), sequences.Num());

	
}



#pragma endregion