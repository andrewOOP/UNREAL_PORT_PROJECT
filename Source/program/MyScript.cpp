// Fill out your copyright notice in the Description page of Project Settings.

#include "MyScript.h"
#include "MyDataLine.h"

MyScript::MyScript(FString filename)
{

	LoadFile(filename);
}

MyScript::~MyScript()
{
}

void MyScript::LoadFile(FString filename)
{

	FString CompleteFilePath = FPaths::ProjectDir() + "Content/Scripts/" + filename + ".script";

	FString FileData = "";
	FFileHelper::LoadFileToString(FileData, *CompleteFilePath);

	ParseData(FileData);
}


void MyScript::ParseData(FString data) {

	script.Empty();

	TArray<FString> dataArray;
	int32 dataArraySize = data.ParseIntoArray(dataArray, _T("\n"), true);


	for (int i = 0; i < dataArraySize; i++) {

		FString currLine = dataArray[i];

		FString MessageFormat = "\\((.*)\\)";
		FRegexPattern RegexPattern(MessageFormat);
		FRegexMatcher SymbolStripper(RegexPattern, currLine);

		FString passedData = "";

		if (SymbolStripper.FindNext()) {

			passedData = SymbolStripper.GetCaptureGroup(1);
		}

		if (dataArray[i].Mid(0,1).Equals(TEXT("_"))) {
			//this is code, not text

			FString typeStr = dataArray[i].Mid(1, 1);
			TArray<FString> splitData;

			if (typeStr.Equals(TEXT("s"))) {

				//someone will begin to talk
				passedData.ParseIntoArray(splitData, _T(","), true);

				script.Add(new MyDataLine(MyDataLine::Type::_sprite, splitData));
			}
			else if (typeStr.Equals(TEXT("c"))) {

				//someone will begin to talk
				passedData.ParseIntoArray(splitData, _T(","), true);

				script.Add(new MyDataLine(MyDataLine::Type::_choice, splitData));
			}
			else if (typeStr.Equals(TEXT("t"))) {
				TArray<FString> talkingCharID;

				if (passedData == "self")
				{
					talkingCharID = { "-1" };
				}
				else {
					talkingCharID = { passedData };
				}

				script.Add(new MyDataLine(MyDataLine::Type::_talk, talkingCharID));
			}
			else if (typeStr.Equals(TEXT("n"))) {

				passedData.ParseIntoArray(splitData, _T(","), true);

				names.Add(splitData[0], splitData[1]);
			}
			else if (typeStr.Equals(TEXT("b"))) {
				TArray<FString> blankArr = { "" };


				script.Add(new MyDataLine(MyDataLine::Type::_break, blankArr));
			}
		}
		else {
			//this is not code
			if (currLine != "\r")
			{

				TArray<FString> currLineArr = { currLine };
				script.Add(new MyDataLine(MyDataLine::Type::text, currLineArr));
			}
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Here!! %s"), *(script[0]->data[0]));
}

MyDataLine* MyScript::GetNextLine() {

	if (_counter < script.Num())
	{
		MyDataLine* returnLine = script[_counter];
		_counter++;
		
		return returnLine;
	}

	return nullptr;
}