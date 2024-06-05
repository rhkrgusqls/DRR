// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSessionRoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class DRR_API UCSessionRoomWidget : public UUserWidget
{
	GENERATED_BODY()
public:


	
};

/*
* 채팅채널 구현. 
enter을 누르면 채팅창 열림.
채팅창에 내용이 있는 상태에서enter을 누르면 송신,
없는 상태에서 enter을 누르면 채팅창 닫음

컨트롤러로부터 입력을 받으면 서버 RPC를통해 서버로 이동해 입력된 문자열을 서버의 채팅시스템으로 이동, 

채팅을 위해 송신하는구조체는 송신자, 송신타입(전체 , 수신자(귓속말타입일경우), 입력문자열로 구성.
각 컨트롤러에는 이때까지 들어온 채팅내용을 보관하는 배열과 출력을 위한 텍스트상자가 있음


*/
