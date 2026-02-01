// Fill out your copyright notice in the Description page of Project Settings.


#include "UMInteractionComponent.h"
#include "GameplayInterface.h"
#include "UnmaskCharacter.h"

// Sets default values for this component's properties
UUMInteractionComponent::UUMInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UUMInteractionComponent::PrimaryInteract()
{
	if (AUnmaskCharacter* owner = Cast<AUnmaskCharacter>(GetOwner()))
	{
		if (AActor* hitActor = owner->GetCurrentLookAtActor())
		{
			if (hitActor->Implements<UGameplayInterface>())
			{
				IGameplayInterface::Execute_Interact(hitActor, owner);
			}
		}
	}
}
