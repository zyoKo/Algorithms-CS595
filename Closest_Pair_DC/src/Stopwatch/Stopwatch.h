#pragma once
#include <cassert>
#include <chrono>

namespace Utility
{
	class StopWatch
	{
	public:
		StopWatch()
			:	startTime(std::chrono::high_resolution_clock::now()),
				timeDuration(std::chrono::duration<double>::zero()),
				isRunning(false)
		{}

		void StartTimer()
		{
			assert(!isRunning);

			startTime = std::chrono::high_resolution_clock::now();
			isRunning = true;
		}

		double StopTimer()
		{
			assert(isRunning);

			const auto endTime = std::chrono::high_resolution_clock::now();
			timeDuration = endTime - startTime;
			isRunning = false;

			return timeDuration.count();
		}

		void ClearTimer()
		{
			isRunning = false;
			timeDuration = std::chrono::duration<double>::zero();
		}

		double GetElapsedTimeInMilliseconds() const
		{
			return timeDuration.count();
		}

		double GetElapsedTimeInSeconds() const
		{
			return timeDuration.count() * 0.01;
		}

	private:
		std::chrono::high_resolution_clock::time_point startTime;

		std::chrono::duration<double> timeDuration;

		bool isRunning;
	};
}
