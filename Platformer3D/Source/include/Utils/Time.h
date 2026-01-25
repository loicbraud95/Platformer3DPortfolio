#pragma once
#include <chrono>

class Time
{
public:
    static void Update();
    static float DeltaTime();
	static float FixedDeltaTime();

	static float timer;

private:
	static std::chrono::steady_clock::time_point currentTime;
	static float deltaTime;
	static float fixedDeltaTime;
};