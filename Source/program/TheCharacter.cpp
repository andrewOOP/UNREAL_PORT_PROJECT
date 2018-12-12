// Fill out your copyright notice in the Description page of Project Settings.

#include "TheCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "PaperSprite.h"

// Sets default values
ATheCharacter::ATheCharacter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComponent"));
	USphereComponent* SpriteRoot = CreateDefaultSubobject<USphereComponent>(TEXT("SpriteRoot"));

	FRotator DefaultRot;
	DefaultRot.Yaw = 90.0;

	SpriteComponent->SetWorldRotation(DefaultRot);

	SpriteRoot->SetupAttachment(GetRootComponent());
	SpriteComponent->SetupAttachment(SpriteRoot);

	SpriteComponent->SetSprite(TheSprite);
}

// Called when the game starts or when spawned
void ATheCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATheCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), PlayerLoc);
	FRotator NewRot = FMath::RInterpTo(GetRootComponent()->GetComponentRotation(), PlayerRot, DeltaTime, 10);

	NewRot.Roll = 0;
	NewRot.Pitch = 0;

	GetRootComponent()->SetWorldRotation(NewRot);
}

void ATheCharacter::SetSprite(FString folder, FString filename) {
	FString CompleteFilePath = "Characters/" + folder;

	TArray<UObject*> allSprites = DynamicLoadContentFromPath(CompleteFilePath, UPaperSprite::StaticClass(), false);

	SpriteComponent->SetSprite(GetSpriteByName(allSprites, filename));
}

TArray<UObject*> ATheCharacter::DynamicLoadContentFromPath(FString PathFromContentFolder, UClass* AssetClass, bool LoadFromSubfolders)
{
	TArray<UObject*> Array;

	FString RootFolderFullPath = FPaths::ConvertRelativePathToFull(FPaths::GameDir()) + "Content/" + PathFromContentFolder + "/";

	IFileManager& FileManager = IFileManager::Get();

	TArray<FString> Files;

	FString Ext;

	if (LoadFromSubfolders)
	{
		if (!Ext.Contains(TEXT("*")))
		{
			if (Ext == "")
			{
				Ext = "*.*";
			}
			else
			{
				Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
			}
		}

		FileManager.FindFilesRecursive(Files, *RootFolderFullPath, *Ext, true, false);
	}
	else
	{
		if (!Ext.Contains(TEXT("*")))
		{
			if (Ext == "")
			{
				Ext = "*.*";
			}
			else
			{
				Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
			}
		}

		FileManager.FindFiles(Files, *(RootFolderFullPath + Ext), true, false);
	}

	for (int32 i = 0; i < Files.Num(); i++)
	{
		FString Path;
		if (LoadFromSubfolders)
		{
			int32 LastForwardSlash = Files[i].Find("/", ESearchCase::IgnoreCase, ESearchDir::FromEnd);
			FString File = Files[i].RightChop(LastForwardSlash + 1);
			FString Folder = Files[i].RightChop(Files[i].Find(PathFromContentFolder, ESearchCase::CaseSensitive, ESearchDir::FromEnd) + PathFromContentFolder.Len());
			Folder = Folder.LeftChop(File.Len() + 1);
			File = File.Left(File.Find(".", ESearchCase::IgnoreCase, ESearchDir::FromEnd));
			Path = AssetClass->GetFName().ToString() + "'/Game/" + PathFromContentFolder + Folder + "/" + File + "." + File + "'";
		}
		else
		{
			Path = AssetClass->GetFName().ToString() + "'/Game/" + PathFromContentFolder + "/" + Files[i].LeftChop(7) + "." + Files[i].LeftChop(7) + "'";
		}
		UObject* LoadedObj = StaticLoadObject(AssetClass, NULL, *Path);

		Array.Add(LoadedObj);
	}

	return Array;
}

UPaperSprite* ATheCharacter::GetSpriteByName(TArray<UObject*> sprites, FString name)
{

	for (int i = 0; i < sprites.Num(); i++)
	{
		if (sprites[i]->GetFName().ToString().Equals(name)) {
			return Cast<UPaperSprite>(sprites[i]);
		}
	}

	return Cast<UPaperSprite>(sprites[0]);
}