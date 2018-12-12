// Fill out your copyright notice in the Description page of Project Settings.

#include "ThePlayer.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TheCharacter.h"
#include "SceneController.h"

// Sets default values
AThePlayer::AThePlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AThePlayer::BeginPlay()
{
	Super::BeginPlay();
	playerController = GetWorld()->GetFirstPlayerController();
}

// Called every frame
void AThePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AThePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AThePlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AThePlayer::MoveLeft);
	PlayerInputComponent->BindAxis("Turn", this, &AThePlayer::AddControllerYawInput);

	InputComponent->BindAction("Click", IE_Pressed, this, &AThePlayer::MouseDown);
}

void AThePlayer::MoveForward(float value) {
	FVector direction = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, value);
}

void AThePlayer::MoveLeft(float value) {
	FVector direction = FRotationMatrix(playerController->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, value);
}

void AThePlayer::MouseDown() {
	TWeakObjectPtr<AActor> FoundActor = TraceForActor();

	if (FoundActor.IsValid()) {
		if (ATheCharacter* TheCharacter = Cast<ATheCharacter>(FoundActor.Get())) {

			if (!sceneController->sceneRunning) {
				sceneController->LoadScene(TheCharacter->script, TheCharacter);
			}

			UE_LOG(LogTemp, Warning, TEXT("Here!! %s"), *(TheCharacter->script));
		}
	}
}

TWeakObjectPtr<AActor> AThePlayer::TraceForActor()
{
	FHitResult HitResult;
	TArray<AActor*> actorsToIgnore;

	const FVector& ActorLocation = GetActorLocation();
	const FRotator& ActorRotation = GetActorRotation();

	if (UKismetSystemLibrary::LineTraceSingle(this, ActorLocation, ActorLocation + PlayerInteractionDistance * ActorRotation.Vector(), UEngineTypes::ConvertToTraceType(ECC_Camera), false, actorsToIgnore, EDrawDebugTrace::None, HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.0f))
	{
		return HitResult.Actor;
	}

	return nullptr;
}
