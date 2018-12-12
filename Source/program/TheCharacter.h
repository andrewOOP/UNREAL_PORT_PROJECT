// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheCharacter.generated.h"

UCLASS()
class PROGRAM_API ATheCharacter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
		//Script File Name
		FString script;

	UPROPERTY(VisibleAnywhere)
		class UPaperSpriteComponent* SpriteComponent;

	UPROPERTY(VisibleAnywhere)
		class UPaperSprite* TheSprite;

	UFUNCTION()
	void SetSprite(FString folder, FString filename);

private:
	UFUNCTION()
		static TArray<UObject*> DynamicLoadContentFromPath(FString PathFromContentFolder = "Audio/Music", UClass* AssetClass = nullptr, bool LoadFromSubfolders = false);
	
	UFUNCTION()
		UPaperSprite* GetSpriteByName(TArray<UObject*> sprites, FString name);
};
