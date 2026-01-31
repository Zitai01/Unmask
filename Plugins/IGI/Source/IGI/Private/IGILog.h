// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
// SPDX-License-Identifier: MIT
//

#pragma once

#include "CoreMinimal.h"

#include "nvigi.h"

DEFINE_LOG_CATEGORY_STATIC(LogIGISDK, Log, All);

static void IGILogCallback(nvigi::LogType Type, const char* InMessage)
{
    FString Message(reinterpret_cast<const UTF8CHAR*>(InMessage));

    // AIM log messages end with newlines, so fix that
    Message.TrimEndInline();
    
    if (Type == nvigi::LogType::eInfo)
    {
        UE_LOG(LogIGISDK, Log, TEXT("IGI: %s"), *Message);
    }
    else if (Type == nvigi::LogType::eWarn)
    {
        UE_LOG(LogIGISDK, Warning, TEXT("IGI: %s"), *Message);
    }
    else if (Type == nvigi::LogType::eError)
    {
        UE_LOG(LogIGISDK, Error, TEXT("IGI: %s"), *Message);
    }
    else
    {
        UE_LOG(LogIGISDK, Error, TEXT("Received unknown IGI log type %d: %s"), Type, *Message);
    }
}
