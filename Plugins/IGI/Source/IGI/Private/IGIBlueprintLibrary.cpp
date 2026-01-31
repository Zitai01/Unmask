// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: MIT
//

#include "IGIBlueprintLibrary.h"

#include "Async/Async.h"
#include "Async/TaskGraphInterfaces.h"
#include "Modules/ModuleManager.h"

#include "IGIGPT.h"
#include "IGILog.h"

std::atomic<bool> UIGIGPTEvaluateAsync::IsRunning = false;

UIGIGPTEvaluateAsync* UIGIGPTEvaluateAsync::GPTEvaluateAsync(const FString& SystemPrompt, const FString& UserPrompt, const FString& AssistantPrompt)
{
    if (IsRunning)
    {
        UE_LOG(LogIGISDK, Log, TEXT("%s: GPT is already running! Request was ignored."), ANSI_TO_TCHAR(__FUNCTION__));
        return nullptr;
    }

    UIGIGPTEvaluateAsync* BlueprintNode = NewObject<UIGIGPTEvaluateAsync>();
    BlueprintNode->SystemPrompt = SystemPrompt;
    BlueprintNode->UserPrompt = UserPrompt;
    BlueprintNode->AssistantPrompt = AssistantPrompt;
    BlueprintNode->AddToRoot();

    return BlueprintNode;
}



void UIGIGPTEvaluateAsync::Activate()
{
    const FString TrimmedSystemPrompt = SystemPrompt.TrimStartAndEnd();
    const FString TrimmedUserPrompt = UserPrompt.TrimStartAndEnd();
    const FString TrimmedAssistantPrompt = AssistantPrompt.TrimStartAndEnd();

    if (TrimmedUserPrompt.IsEmpty())
    {
        UE_LOG(LogIGISDK, Log, TEXT("%s: GPT called with empty user prompt!"), ANSI_TO_TCHAR(__FUNCTION__));
    }
    else
    {
        IsRunning = true;

        UE_LOG(LogIGISDK, Log, TEXT("%s: sending to GPT: %s"), ANSI_TO_TCHAR(__FUNCTION__), *TrimmedUserPrompt);

        AsyncTask(ENamedThreads::AnyBackgroundHiPriTask, [this, TrimmedSystemPrompt, TrimmedUserPrompt, TrimmedAssistantPrompt]()
            {
                FString result;
                FIGIGPT* GPT{ FModuleManager::GetModuleChecked<FIGIModule>(FName("IGI")).GetGPT()};
                if (GPT != nullptr)
                {
                    result = GPT->Evaluate(TrimmedSystemPrompt, TrimmedUserPrompt, TrimmedAssistantPrompt);

                    AsyncTask(ENamedThreads::GameThread, [this, result]()
                        {
                            OnResponse.Broadcast(result);
                        });

                    UE_LOG(LogIGISDK, Log, TEXT("%s: response from GPT: %s"), ANSI_TO_TCHAR(__FUNCTION__), *result);
                }

                IsRunning = false;
                this->RemoveFromRoot();
            });
    }
}
