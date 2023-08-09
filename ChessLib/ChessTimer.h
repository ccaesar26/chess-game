#pragma once

#include "IPiece.h"

#include <chrono>
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

class ChessTimer
{
public:
	ChessTimer()
		: m_paused(false)
		, m_isTimerRunning(false)
		, m_turn(EColor::White)
	{

		
	}

	~ChessTimer()
	{
		Stop();
	}

	void Start()
	{
		m_timerThread = std::thread(&ChessTimer::StartTimer, this);
	}

	void Stop()
	{
		m_isTimerRunning = false;
		m_timerCV.notify_all();
		if (m_timerThread.joinable())
		{
			m_timerThread.join();
		}
	}

	void SetTime(std::chrono::seconds time)
	{
		m_whiteRemainingTime.store(time); 
		m_blackRemainingTime.store(time);
	}

	void SetNotify(std::function<void()> notifyUpdate, std::function<void()> notifyTimesUp)
	{
		NotifyUpdateTimer = notifyUpdate;
		NotifyTimesUp = notifyTimesUp;
	}

	int GetRemainingTime(EColor color) const
	{
		switch (m_turn)
		{
		case EColor::White:
			return m_whiteRemainingTime.load().count() / 1000;
			break;
		case EColor::Black:
			return m_blackRemainingTime.load().count() / 1000;
			break;
		}
	}

	void SwitchTurn()
	{
		m_turn.store(m_turn == EColor::White ? EColor::Black : EColor::White);
	}

	void Pause()
	{
		if (m_isTimerRunning && !m_paused)
		{
			m_paused = true;
			m_timerCV.notify_all();
		}
	}

	void Resume()
	{
		if (m_isTimerRunning && m_paused)
		{
			m_paused = false;
			m_timerCV.notify_all();
		}
	}

	bool IsPaused() const
	{
		return m_paused;
	}

private:

	void StartTimer()
	{
		m_isTimerRunning = true;
		while (m_isTimerRunning)
		{
			NotifyUpdateTimer();

			auto initialTime = std::chrono::steady_clock::now();

			std::unique_lock<std::mutex> lock(m_timerMutex);
			m_timerCV.wait_for(lock, std::chrono::milliseconds(1000), [&] { return !m_isTimerRunning || m_paused; });

			auto finalTime = std::chrono::steady_clock::now();

			if (m_paused)
			{
				m_timerCV.wait(lock, [&] { return !m_paused; });
			}

			switch (m_turn)
			{
			case EColor::White:
				m_whiteRemainingTime.store(m_whiteRemainingTime.load() - std::chrono::duration_cast<std::chrono::milliseconds>(finalTime - initialTime));
				if (m_whiteRemainingTime.load().count() <= 0)
				{
					m_isTimerRunning = false;
					NotifyUpdateTimer();
					NotifyTimesUp();
				}
				break;
			case EColor::Black:
				m_blackRemainingTime.store(m_blackRemainingTime.load() - std::chrono::duration_cast<std::chrono::milliseconds>(finalTime - initialTime));
				if (m_blackRemainingTime.load().count() <= 0)
				{
					m_isTimerRunning = false;
					NotifyUpdateTimer();
					NotifyTimesUp();
				}
				break;
			}
		}
	}

	std::thread m_timerThread;
	std::mutex m_timerMutex;
	std::condition_variable m_timerCV;

	std::atomic_bool m_isTimerRunning;
	std::atomic_bool m_paused;

	std::atomic<std::chrono::milliseconds> m_whiteRemainingTime;
	std::atomic<std::chrono::milliseconds> m_blackRemainingTime;

	std::atomic<EColor> m_turn;
	std::function<void()> NotifyUpdateTimer;
	std::function<void()> NotifyTimesUp;
};