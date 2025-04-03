// Fill out your copyright notice in the Description page of Project Settings.


#include "CodingActor.h"

// Sets default values
ACodingActor::ACodingActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACodingActor::BeginPlay()
{
	Super::BeginPlay();

	// Hash
	TMap<FString, int32> map;

	map.Add(TEXT("Jacob"), 100000000);
	map.Add(TEXT("tom"), 5000000);

	for (auto& item : map)
	{
		UE_LOG(LogTemp, Warning, TEXT("key : %s, value : %d"), *item.Key, item.Value);
	}

	// 배열
	TArray<int32> list;
	
	list.Empty(50);
	
	list.Add(10);
	list.Add(20);
	if (false == list.Contains(30))
	{
		list.Add(30);
	}
	UE_LOG(LogTemp, Warning, TEXT("11111111111111111"));
	// for (int i = 0; i < list.Num(); i++)
	// {
	// 	UE_LOG(LogTemp, Warning, TEXT("%d"), list[i]);
	// }
	
	for (int& item : list)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), item);
	}
	
	list[0] = 100;
	list.Remove(20);
	list.RemoveAt(1);
	UE_LOG(LogTemp, Warning, TEXT("22222222222222222222"));
	for (int i = 0; i < list.Num(); i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), list[i]);
	}
	

	// int32 ymd = 19501219;
	// // 년 월 일을 각 각 출력하세요.
	// int32 year = ymd / 10000;
	// int32 month = (ymd / 100) % 100;
	// int32 day = ymd % 100;
	// UE_LOG(LogTemp, Warning, TEXT("year : %d, month : %d, day : %d"), year, month, day);
	// int32 year1 = 2025;
	// int32 month1 = 4;
	// int32 day1 = 3;
	// int32 ymd1 = year1 * 10000 + month1 * 100 + day1;
	//
	// int32 color = 0x2af47fff;
	// // color의 값에서 r,g,b,a를 각 각 분리해서 출력하세요. 
	// int32 r = color >> 24;
	// int32 g = (color >> 16) & 0xff;
	// int32 b = (color >> 8) & 0xff;
	// int32 a = color & 0xff;
	// UE_LOG(LogTemp, Warning, TEXT("r : %d, g : %d, b : %d, a : %d"), r, g, b, a);
	//
	// //r : 42, g : 244, b : 127, a : 255
	// color = (r << 24) | ((g << 16) & 0xff) | ((b << 8) & 0xff) | (a & 0xff);


	// UE_LOG(LogTemp, Warning, TEXT("Hello World!!"));
	// GEngine->AddOnScreenDebugMessage(0, 10, FColor::Cyan, TEXT("Hello World!!"));
	// // Num, Speed, bGood, MyName
	// UE_LOG(LogTemp, Warning, TEXT("Num : %d"), Num);
	// UE_LOG(LogTemp, Warning, TEXT("Speed : %.2f"), Speed);
	// UE_LOG(LogTemp, Warning, TEXT("bGood : %d"), bGood);
	// UE_LOG(LogTemp, Warning, TEXT("MyName : %s"), *MyName);
	//
	//
	// // 1~15 까지 3의 배수를 출력하세요.
	// for (int32 i = 1; i <= 15; i++)
	// {
	// 	if (i % 3 ==0)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("i : %d"), i);
	// 	}
	// }
}

// Called every frame
void ACodingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
