// Fill out your copyright notice in the Description page of Project Settings.

#include "TheListeningPlayer.h"
#include "SceneController.h"

// Sets default values
ATheListeningPlayer::ATheListeningPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATheListeningPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheListeningPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATheListeningPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("Click", IE_Pressed, this, &ATheListeningPlayer::MouseDown);
}

void ATheListeningPlayer::MouseDown() {

	sceneController->Next();
}