#include "ChessTimer.h"

ChessTimer::ChessTimer(std::chrono::seconds initialTime /*= std::chrono::seconds(-1)*/) : m_remainingTime(initialTime)
, m_isRunning(false)
{
}

ChessTimer::~ChessTimer()
{
	m_isRunning = false;
}

void ChessTimer::SetTime(int seconds)
{
	m_remainingTime.store(std::chrono::seconds(seconds));
}

void ChessTimer::Start()
{
	m_isRunning = true;
	m_thread = std::thread(&ChessTimer::Run, this);
	m_thread.detach();
}

void ChessTimer::Stop()
{
	m_isRunning = false;
}

void ChessTimer::SetNotify(std::function<void()> notifyFunction)
{
	m_notifyFunction = notifyFunction;
}

std::chrono::seconds ChessTimer::GetRemainingTime() const
{
	return std::chrono::duration_cast<std::chrono::seconds>(m_remainingTime.load());
}

void ChessTimer::Run()
{
	auto lastTickTime = std::chrono::system_clock::now();

	while (m_isRunning)
	{
		m_notifyFunction();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		auto currentTime = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTickTime);

		m_remainingTime.store(m_remainingTime.load() -= elapsed);
		lastTickTime = currentTime;
	}
}
