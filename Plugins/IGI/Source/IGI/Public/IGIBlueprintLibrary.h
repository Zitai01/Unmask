// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include <atomic>
#include "IGIBlueprintLibrary.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FIGIGPTEvaluateAsyncOutputPin, FString, Response);

UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncAction))
class IGI_API UIGIGPTEvaluateAsync : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()
public:

    UFUNCTION(BlueprintCallable, Category = "IGI|GPT", meta = (DisplayName = "Send text to GPT (Async)", BlueprintInternalUseOnly = "true"))
    static UIGIGPTEvaluateAsync* GPTEvaluateAsync(const FString& SystemPrompt, const FString& UserPrompt, const FString& AssistantPrompt);

    UPROPERTY(BlueprintAssignable)
    FIGIGPTEvaluateAsyncOutputPin OnResponse;

    UPROPERTY(BlueprintReadOnly, Category = "IGI|GPT", meta = (BBlueprintInternalUseOnly = "true"))
    FString SystemPrompt;

    UPROPERTY(BlueprintReadOnly, Category = "IGI|GPT", meta = (BBlueprintInternalUseOnly = "true"))
    FString UserPrompt;

    UPROPERTY(BlueprintReadOnly, Category = "IGI|GPT", meta = (BBlueprintInternalUseOnly = "true"))
    FString AssistantPrompt;

private:
    virtual void Activate() override;

    static std::atomic<bool> IsRunning;
};
