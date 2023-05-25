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


	UE_LOG(LogTemp, Warning, TEXT("SelectedActors.Num() = %d"), SelectedActors.Num());

	for (AActor* SelectedActor:SelectedActors)
	{
		if(!SelectedActor) continue;
		UE_LOG(LogTemp, Warning, TEXT("SelectedActor->GetLabelName() = %s"), *SelectedActor->GetActorLabel());

		// update selection state after operation
		// or for new created ators too
		EditorActorSubsystem->SetActorSelectionState(SelectedActor, true);
	}
	
}

bool UQuickActorActionWidget::GetEditorActorSubsystem()
{
	if(!EditorActorSubsystem)
	{
		EditorActorSubsystem = GEditor->GetEditorSubsystem<UEditorActorSubsystem>();

	}
	return EditorActorSubsystem != nullptr;
}
