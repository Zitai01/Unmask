// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayInterface.h"
#include "GameFramework/Actor.h"
#include "UMInteractableEvidence.generated.h"

UCLASS()
class UNMASK_API AUMInteractableEvidence : public AActor, public IGameplayInterface
{
	GENERATED_BODY()
	
	void Interact_Implementation(APawn* InstigatorPawn);

public:	
	// Sets default values for this actor's properties
	AUMInteractableEvidence();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Evidence", meta = (MultiLine = true))
	FString EvidenceText;

};
