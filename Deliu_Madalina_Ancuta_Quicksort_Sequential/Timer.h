#pragma once

#include <chrono>
#include <iostream>

class Timer {
public:
    Timer() : m_elapsed_time(0.0), m_is_running(false) {}

    // Start the timer
    void start() {
        m_start_time = std::chrono::high_resolution_clock::now();
        m_is_running = true;
    }

    // Stop the timer
    void stop() {
        if (m_is_running) {
            m_end_time = std::chrono::high_resolution_clock::now();
            m_elapsed_time += std::chrono::duration_cast<std::chrono::duration<double>>(m_end_time - m_start_time).count();
            m_is_running = false;
        }
    }

    // Reset the timer
    void reset() {
        m_elapsed_time = 0.0;
        m_is_running = false;
    }

    // Return the elapsed time in seconds
    double elapsed() const {
        if (m_is_running) {
            auto current_time = std::chrono::high_resolution_clock::now();
            return m_elapsed_time + std::chrono::duration_cast<std::chrono::duration<double>>(current_time - m_start_time).count();
        }
        else {
            return m_elapsed_time;
        }
    }

private:
    std::chrono::high_resolution_clock::time_point m_start_time;
    std::chrono::high_resolution_clock::time_point m_end_time;
    double m_elapsed_time;
    bool m_is_running;
};
