// Fill out your copyright notice in the Description page of Project Settings.


#include "UMInteractableEvidence.h"
#include "UnmaskPlayerController.h"

// Sets default values
AUMInteractableEvidence::AUMInteractableEvidence()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AUMInteractableEvidence::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUMInteractableEvidence::Interact_Implementation(APawn* InstigatorPawn)
{
    if (!InstigatorPawn) return;

    if (APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController()))
    {
        if (AUnmaskPlayerController* UMPC = Cast<AUnmaskPlayerController>(PC))
        {
         //   UMPC->ShowEvidencePopup(EvidenceText);
        }
    }
};


