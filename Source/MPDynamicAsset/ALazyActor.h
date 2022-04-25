// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "ALazyActor.generated.h"


UCLASS()
class MPDYNAMICASSET_API AALazyActor : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "BodyMesh Load Radius")
		USphereComponent* BodyLoadRadius;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSoftObjectPtr<UStaticMesh> BodyMeshRef;

public:
	// Sets default values for this actor's properties
	AALazyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMesh* LoadBodyMesh();


};
