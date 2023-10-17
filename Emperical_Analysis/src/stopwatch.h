#pragma once

#include <chrono>

class Stopwatch
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    bool is_running;

public:
    Stopwatch() : is_running(false) {}

    void start() {
        start_time = std::chrono::high_resolution_clock::now();
        is_running = true;
    }

    void clear() {
        is_running = false;
    }

    double elapsed_milliseconds() const {
        if (!is_running) {
            return 0.0;
        }

        const auto end_time = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end_time - start_time;
        return elapsed.count();
    }
};