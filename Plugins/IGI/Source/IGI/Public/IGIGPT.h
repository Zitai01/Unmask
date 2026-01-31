// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "CoreMinimal.h"
#include "Templates/PimplPtr.h"

#include "IGIModule.h"

class IGI_API FIGIGPT
{
public:
    FIGIGPT(FIGIModule* IGIModule);
    virtual ~FIGIGPT();

    FString Evaluate(const FString& SystemPrompt, const FString& UserPrompt, const FString& AssistantPrompt);

private:
    class Impl;
    TPimplPtr<class Impl> Pimpl;
};
