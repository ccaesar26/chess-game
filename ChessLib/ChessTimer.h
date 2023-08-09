#pragma once

#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

class ChessTimer
{
public:
	ChessTimer(std::chrono::seconds initialTime = std::chrono::seconds(-1));

	~ChessTimer();

	void SetTime(int seconds);

	void Start();

	void Stop();

	void SetNotify(std::function<void()> notifyFunction);

	std::chrono::seconds GetRemainingTime() const;

private:
	void Run();

	std::function<void()> m_notifyFunction;
	std::atomic<bool> m_isRunning;
	std::atomic<std::chrono::milliseconds> m_remainingTime;
	std::thread m_thread;
};
