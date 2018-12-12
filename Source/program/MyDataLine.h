// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class MyDataLine
{
public:
	enum Type {
		_sprite,
		_talk,
		_name,
		_choice,
		_break,
		text
	};

	MyDataLine(Type _type, TArray<FString> _data);
	~MyDataLine();

	Type type;
	TArray<FString> data;
};
