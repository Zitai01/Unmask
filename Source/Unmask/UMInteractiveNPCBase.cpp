// Fill out your copyright notice in the Description page of Project Settings.

#include "UnmaskPlayerController.h"
#include "UMInteractiveNPCBase.h"

// Sets default values
AUMInteractiveNPCBase::AUMInteractiveNPCBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AUMInteractiveNPCBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUMInteractiveNPCBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUMInteractiveNPCBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUMInteractiveNPCBase::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!InstigatorPawn) return;

	if (AUnmaskPlayerController* PC = Cast<AUnmaskPlayerController>(InstigatorPawn->GetController()))
	{
		PC->OpenChat(this);
	}
};

