// Fill out your copyright notice in the Description page of Project Settings.


#include "ALazyActor.h"

#include "TestCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

AALazyActor::AALazyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Body Mesh"));
	BodyMesh->SetupAttachment(RootComponent);

	BodyLoadRadius = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger to load mesh"));

}

void AALazyActor::BeginPlay()
{
	Super::BeginPlay();
	BodyLoadRadius->OnComponentBeginOverlap.AddDynamic(this, &AALazyActor::BeginOverlap);
}

void AALazyActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (Cast<ACharacter>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(10, 2, FColor::Yellow, " BEGIN OVERLAP ");

		BodyMesh->SetStaticMesh(LoadBodyMesh());

	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 10, FColor::Red, " Cast Failed ");
		
	}
}

void AALazyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMesh* AALazyActor::LoadBodyMesh()
{

	if (BodyMeshRef.IsPending())
	{
		const FSoftObjectPath& AssetRef = BodyMeshRef.ToStringReference();
		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		BodyMeshRef = Cast<UStaticMesh>(StreamableManager.LoadSynchronous(AssetRef));
	}
	return BodyMeshRef.Get();
}