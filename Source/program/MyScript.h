// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


/**
 * 
 */

class MyScript
{
public:
	MyScript(FString filepath);
	~MyScript();
	TMap<FString, FString> names;
	class MyDataLine* GetNextLine();

private:
	void LoadFile(FString filepath);
	void ParseData(FString data);
	int32 _counter = 0;
	TArray<class MyDataLine*> script;

};
