#ifndef _FIREFLY_PROGRESSBAR_H
#define _FIREFLY_PROGRESSBAR_H

#include <cstdint>
#include <cstdio>

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
namespace Firefly
{
    class ProgressBar
    {
        public:
            
            explicit ProgressBar(const uint32_t maxSteps, const char* outputMessage, const uint8_t size);
            void Advance(const uint32_t numSteps = 1);
        private:
            uint32_t m_MaxSteps;
            uint32_t m_CurrentSteps;
            const char* m_OutputMessage;
            uint8_t m_Size;
    };

    inline ProgressBar::ProgressBar(const uint32_t maxSteps, const char* outputMessage, const uint8_t size){
        m_MaxSteps = maxSteps;
        m_CurrentSteps = 0; 
        m_OutputMessage = outputMessage;
        m_Size = size;
    }

    inline void ProgressBar::Advance(const uint32_t numSteps){
        //Increment the current steps by numSteps
        m_CurrentSteps += numSteps; 

        //Compute completion percentage
        const float completePercent = ((float)m_CurrentSteps / (float)m_MaxSteps) * 100.0f; 
    
        //Output to stdout
        int padLeft = (int)((completePercent / 100.0f) * m_Size);
        int padRight = (int)(m_Size - padLeft);
        printf("\r%s %3d%% (%d/%d) \t[%.*s%*s]", m_OutputMessage, (int)completePercent, m_CurrentSteps, m_MaxSteps, padLeft, PBSTR, padRight, "");
        fflush(stdout);
    }
}

#endif
