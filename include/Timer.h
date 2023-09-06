#ifndef _FIREFLY_TIMER_H
#define _FIREFLY_TIMER_H

#include <chrono>

namespace Firefly{
    class Timer{
        public:
            void Start();
            template<typename T> 
            float Get();
            void Tick(); 
            void Reset();

        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> m_CurrentTime;
            std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
    };


    inline void Timer::Start(){
        m_StartTime  = std::chrono::high_resolution_clock::now(); 
        m_CurrentTime = std::chrono::high_resolution_clock::now(); 
    }

    inline void Timer::Tick(){
        m_CurrentTime = std::chrono::high_resolution_clock::now(); 
    }

    inline void Timer::Reset(){
        m_StartTime  = std::chrono::high_resolution_clock::now(); 
        m_CurrentTime = std::chrono::high_resolution_clock::now(); 
    }

    template<typename T>
    inline float Timer::Get(){
        float time = 0;
        time = std::chrono::duration_cast<T>(m_CurrentTime - m_StartTime).count(); 
        return time; 
    }
}

#endif
