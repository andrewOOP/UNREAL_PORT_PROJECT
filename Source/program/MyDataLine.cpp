// Fill out your copyright notice in the Description page of Project Settings.

#include "MyDataLine.h"

MyDataLine::MyDataLine(Type _type, TArray<FString> _data)
{
	type = _type;
	data = _data;
}

MyDataLine::~MyDataLine()
{
}