#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Serialization/JsonSerializer.h"


class FJsonObject;

FString ReadStringFromFile(FString FilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	if(!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read string from file failed, file not exist: %s"), *FilePath);
	}

	FString RetString = "";
	// try to read string from file, output goes in RetString
	if(!FFileHelper::LoadFileToString(RetString, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Read string from file failed, file path: %s"), *FilePath);
		return "";
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Read string from file success, file path: %s"), *FilePath);
	return RetString;
}

void WriteStringToFile(FString FilePath, FString String, bool& bOutSuccess, FString& OutInfoMessage)
{
	// try to write string to file
	if(!FFileHelper::SaveStringToFile(String, *FilePath))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Write string to file failed, file path: %s"), *FilePath);
		return;
	}
	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Write string to file success, file path: %s"), *FilePath);
}

TSharedPtr<FJsonObject> ReadJson(FString JsonFilePath, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString = ReadStringFromFile(JsonFilePath, bOutSuccess, OutInfoMessage);

	if(!bOutSuccess)
	{
		return nullptr;
	}

	TSharedPtr<FJsonObject> RetJsonObject;
	if(!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(JsonString), RetJsonObject))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Json deserialize failed, file path: %s"), *JsonFilePath);
		return nullptr;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Json deserialize success, file path: %s"), *JsonFilePath);
	return RetJsonObject;
	
}

void WriteJson(FString JsonFilePath, TSharedPtr<FJsonObject> JsonObject, bool& bOutSuccess, FString& OutInfoMessage)
{
	FString JsonString;
	if(!FJsonSerializer::Serialize(JsonObject.ToSharedRef(), TJsonWriterFactory<>::Create(&JsonString, 0)))
	{
		bOutSuccess = false;
		OutInfoMessage = FString::Printf(TEXT("Json serialize failed, file path: %s"), *JsonFilePath);
		return;
	}

	WriteStringToFile(JsonFilePath, JsonString, bOutSuccess, OutInfoMessage);
	if(!bOutSuccess)
	{
		return;
	}

	bOutSuccess = true;
	OutInfoMessage = FString::Printf(TEXT("Json serialize success, file path: %s"), *JsonFilePath);
	
}