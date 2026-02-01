// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UMInteractiveNPCBase.h"
#include "UnmaskPlayerController.generated.h"

class UInputMappingContext;
class UUserWidget;

/**
 *  Simple first person Player Controller
 *  Manages the input mapping context.
 *  Overrides the Player Camera Manager class.
 */
UCLASS(abstract)
class UNMASK_API AUnmaskPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/** Constructor */
	AUnmaskPlayerController();

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> DefaultMappingContexts;

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category="Input|Input Mappings")
	TArray<UInputMappingContext*> MobileExcludedMappingContexts;

	/** Mobile controls widget to spawn */
	UPROPERTY(EditAnywhere, Category="Input|Touch Controls")
	TSubclassOf<UUserWidget> MobileControlsWidgetClass;

	/** Pointer to the mobile controls widget */
	TObjectPtr<UUserWidget> MobileControlsWidget;

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

public:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> ChatWidgetClass;

	UPROPERTY()
	UUserWidget* ChatWidgetInstance = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AUMInteractiveNPCBase> CurrentNPC;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> EvidencePopupClass;

	UPROPERTY()
	UUserWidget* EvidencePopupInstance = nullptr;


	bool bChatOpen = false;

	void OpenChat(AUMInteractiveNPCBase* NPC);
	void CloseChat();
};
