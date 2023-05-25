// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorActions/QuickActorActionWidget.h"
#include "Subsystems/EditorActorSubsystem.h"

void UQuickActorActionWidget::MySelectAllActors()
{
	if(!GetEditorActorSubsystem()) return;

	const TArray<AActor*> SelectedActors = EditorActorSubsystem->GetSelectedLevelActors();

	uint32 SelectionCounter = 0;
	if(SelectedActors.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No actors selected"));
		return;
	}

	FString SelectedActorName = SelectedActors[0]->GetActorLabel();

	UE_LOG(LogTemp, Warning, TEXT("SelectedActors.Num() = %d"), SelectedActors.Num());
	
}

bool UQuickActorActionWidget::GetEditorActorSubsystem()
{
	if(!EditorActorSubsystem)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();

	}
	return EditorActorSubsystem != nullptr;
}
