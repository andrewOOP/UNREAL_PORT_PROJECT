// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SceneController.generated.h"

UCLASS()
class PROGRAM_API ASceneController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceneController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LoadScene(FString filename, class ATheCharacter* _currCharacter);

	UPROPERTY()
		bool sceneRunning = false;

	UPROPERTY(EditAnywhere)
		class UUserWidget* talkingUI;

	UPROPERTY()
		class ATheCharacter* currCharacter;

	UFUNCTION()
		void Next();

private:
		class MyScript* currScript;

		UPROPERTY()
		TSubclassOf<class ATheListeningPlayer> ListeningPlayerClass;

		UPROPERTY()
		APlayerController* playerController;

		UPROPERTY()
		APawn* mainPawn;

		UPROPERTY()
		class ATheListeningPlayer* listenPlayerPawn;

		UPROPERTY()
			FString textToWrite;

		UPROPERTY()
			class UTextBlock* main_tb;

		UPROPERTY()
			class UTextBlock* name_tb;

};
