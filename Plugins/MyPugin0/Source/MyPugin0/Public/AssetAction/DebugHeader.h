#pragma once
#include "Misc/MessageDialog.h"
#include "Widgets/Notifications/SNotificationBackground.h"
#include "Framework/Notifications/NotificationManager.h"
#include "Widgets/Notifications/SNotificationList.h"

void MyPrint(const FString& Message, const FColor& Color)
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, Color, *Message);
		
	}
}

void MyPrintLog(const FString& Message)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Message);
}


void MyNotifyInfo(const FString& Message)
{
	FNotificationInfo NotifyInfo(FText::FromString(Message));
	NotifyInfo.bUseLargeFont = true;
	NotifyInfo.FadeInDuration = 8.0f;
	FSlateNotificationManager::Get().AddNotification(NotifyInfo);
	
}