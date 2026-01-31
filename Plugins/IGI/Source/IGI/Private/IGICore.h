// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "CoreMinimal.h"

#include "nvigi.h"
#include "nvigi_ai.h"
#include "nvigi_struct.h"

class FIGICore
{
public:
    FIGICore(FString IGICoreLibraryPath);
    virtual ~FIGICore();

    bool IsInitialized() const { return bInitialized; }

    nvigi::Result LoadInterface(const nvigi::PluginID& Feature, const nvigi::UID& InterfaceType, nvigi::InferenceInterface** Interface, const UTF8CHAR* UTF8PathToPlugin = nullptr);
    nvigi::Result UnloadInterface(const nvigi::PluginID& Feature, nvigi::InferenceInterface* Interface);

private:
    void* IGICoreLibraryHandle;

    PFun_nvigiInit* Ptr_nvigiInit{};
    PFun_nvigiShutdown* Ptr_nvigiShutdown{};
    PFun_nvigiLoadInterface* Ptr_nvigiLoadInterface{};
    PFun_nvigiUnloadInterface* Ptr_nvigiUnloadInterface{};

    nvigi::PluginAndSystemInformation* IGIRequirements{};

    FString ModelDirectory;

    bool bInitialized{ false };
};
