// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnmaskPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "UnmaskCameraManager.h"
#include "Blueprint/UserWidget.h"
#include "Unmask.h"
#include "Widgets/Input/SVirtualJoystick.h"

AUnmaskPlayerController::AUnmaskPlayerController()
{
	// set the player camera manager class
	PlayerCameraManagerClass = AUnmaskCameraManager::StaticClass();
}

void AUnmaskPlayerController::BeginPlay()
{
	Super::BeginPlay();

	
	// only spawn touch controls on local player controllers
	if (SVirtualJoystick::ShouldDisplayTouchInterface() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogUnmask, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AUnmaskPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!SVirtualJoystick::ShouldDisplayTouchInterface())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}
		}
	}
	
}
void AUnmaskPlayerController::OpenChat(AActor* NPC)
{
	if (!ChatWidgetClass) return;

	CurrentNPC = NPC;

	if (!ChatWidgetInstance)
	{
		ChatWidgetInstance = CreateWidget<UUserWidget>(this, ChatWidgetClass);
		if (!ChatWidgetInstance) return;
	}

	if (!bChatOpen)
	{
		ChatWidgetInstance->AddToViewport(1000);

		FInputModeGameAndUI Mode;
		Mode.SetWidgetToFocus(ChatWidgetInstance->TakeWidget());
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		SetInputMode(Mode);

		bShowMouseCursor = true;
		SetIgnoreMoveInput(true);
		SetIgnoreLookInput(true);

		bChatOpen = true;
	}

	// Optional: if your widget has an input box, call a BP event like FocusInput()
	// via a widget subclass or BlueprintImplementableEvent.
}

void AUnmaskPlayerController::CloseChat()
{
	if (!bChatOpen) return;

	if (ChatWidgetInstance)
	{
		ChatWidgetInstance->RemoveFromParent();
	}

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	SetIgnoreMoveInput(false);
	SetIgnoreLookInput(false);

	bChatOpen = false;
}
