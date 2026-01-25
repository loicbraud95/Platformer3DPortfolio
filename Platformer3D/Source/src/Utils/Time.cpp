#include "Utils/Time.h"

std::chrono::steady_clock::time_point Time::currentTime = std::chrono::steady_clock::time_point();
float Time::deltaTime = 0.0;
float Time::fixedDeltaTime = 0.02;
float Time::timer = 0.0;

void Time::Update()
{
    std::chrono::duration<double> newEnd = std::chrono::steady_clock::now() - currentTime;
    currentTime = std::chrono::steady_clock::now();

    deltaTime = static_cast<float>(newEnd.count());
}

float Time::DeltaTime()
{
    return deltaTime;
}

float Time::FixedDeltaTime()
{
    return fixedDeltaTime;
}

