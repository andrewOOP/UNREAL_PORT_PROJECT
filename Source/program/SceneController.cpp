// Fill out your copyright notice in the Description page of Project Settings.

#include "SceneController.h"
#include "MyScript.h"
#include "DefaultGameMode.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Kismet/GameplayStatics.h"
#include "TheListeningPlayer.h"
#include "GameFramework/PlayerController.h"
#include "MyDataLine.h"
#include "TheCharacter.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

// Sets default values
ASceneController::ASceneController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UClass> ListeningPlayerClassFinder(TEXT("/Game/Blueprints/TheListeningPlayer_BP.TheListeningPlayer_BP_C"));
	ListeningPlayerClass = ListeningPlayerClassFinder.Object;
}

// Called when the game starts or when spawned
void ASceneController::BeginPlay()
{
	Super::BeginPlay();

	playerController = GetWorld()->GetFirstPlayerController();
	UE_LOG(LogTemp, Warning, TEXT("%s"), *(playerController->GetActorLabel()));

	FVector Location = playerController->GetPawn()->GetActorLocation();
	FRotator Rotation = playerController->GetPawn()->GetActorRotation();

	FActorSpawnParameters SpawnInfo;
	listenPlayerPawn = GetWorld()->SpawnActor<ATheListeningPlayer>(ListeningPlayerClass, Location, Rotation, SpawnInfo);
	listenPlayerPawn->sceneController = this;
}

// Called every frame
void ASceneController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASceneController::LoadScene(FString filename, ATheCharacter* _currCharacter) {

	currCharacter = _currCharacter;

	if (!sceneRunning) {
		sceneRunning = true;
		currScript = new MyScript(filename);
		ADefaultGameMode* gameMode = (ADefaultGameMode*)(GetWorld()->GetAuthGameMode());
		gameMode->ChangeMenuWidget(talkingUI);

		main_tb = (UTextBlock*)(talkingUI->WidgetTree->FindWidget(TEXT("Main_TB")));
		name_tb = (UTextBlock*)(talkingUI->WidgetTree->FindWidget(TEXT("Name_TB")));

		if (playerController != nullptr) {

			FVector Location = playerController->GetPawn()->GetActorLocation();
			FRotator Rotation = playerController->GetPawn()->GetActorRotation();

			listenPlayerPawn->SetActorLocation(Location);
			listenPlayerPawn->SetActorRotation(Rotation);

			mainPawn = playerController->GetPawn();
			playerController->Possess(listenPlayerPawn);

			Next();
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("We got an error with null controller"));
		}
	}
}

void ASceneController::Next() {
	UE_LOG(LogTemp, Warning, TEXT("Let's Go!"));
	textToWrite = "";

	MyDataLine* line = currScript->GetNextLine();

	if (line != nullptr)
	{
		if (line->type == MyDataLine::Type::_choice)
		{
			if (line->data.Num() > 1)
			{
				for (int i = 1; i < line->data.Num(); i++)
				{
					//Choices will come later
					UE_LOG(LogTemp, Warning, TEXT("Choice"));
				}
			}
		}
		else
		{
			while (line->type != MyDataLine::Type::_break)
			{

				switch (line->type)
				{

				case MyDataLine::Type::_sprite:
					
					currCharacter->SetSprite(line->data[1], line->data[2]);
					
					break;

				case MyDataLine::Type::_talk:

					if (currScript->names.Contains(line->data[0]))
					{
						
						name_tb->SetText(FText::FromString(currScript->names[line->data[0]]));
					}
					else
					{
						name_tb->SetText(FText::FromString("Myself"));
					}
					
					break;
				case MyDataLine::Type::text:
					
					textToWrite += line->data[0] + "\n";
					break;
				default:
					break;
				}
				line = currScript->GetNextLine();
			}

			main_tb->SetText(FText::FromString(textToWrite));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *textToWrite);

		}

	}
	else
	{
		//If we are at the end of the script
		playerController->Possess(mainPawn);
		sceneRunning = false;

		ADefaultGameMode* gameMode = (ADefaultGameMode*)(GetWorld()->GetAuthGameMode());
		gameMode->ChangeMenuWidget(gameMode->StartingWidgetClass);
	}
}