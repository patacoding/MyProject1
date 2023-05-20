// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPawn.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("hello world from my pawn 1"));

	pos = GetActorLocation();
	UE_LOG(LogTemp, Log, TEXT("Actor location: %s"), *pos.ToString());
	


}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// UE_LOG(LogTemp, Log, TEXT("pos %s"), *pos.ToString());
	// SetActorLocation(pos);
	
	
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

