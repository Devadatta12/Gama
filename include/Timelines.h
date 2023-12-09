#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

namespace gama {

    class Timeline{
    public:
        static int64_t time(){
            auto now = std::chrono::high_resolution_clock::now();
            auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
            auto epoch = now_ms.time_since_epoch();
            return epoch.count();
        };
        explicit Timeline(Timeline* anchor, int64_t tic):m_Anchor(anchor), m_Tic(tic), m_Paused(false){
            if (anchor == nullptr){
                m_StartTime = time();
            } else{
                m_StartTime = 0;
            }
        };
        explicit Timeline():m_Anchor(nullptr), m_Tic(1), m_Paused(false){
            m_StartTime = time();
        };
        int64_t getTime();
        int64_t getGlobalTime();
        void pause();
        void unpause();
        void changeTic(int tic);
        bool isPaused();
    private:
        std::recursive_mutex m_Mutex;
        int64_t m_StartTime;
        int64_t m_ElapsedPausedTime = 0;
        int64_t m_LastPausedTime = 0;
        int64_t m_Tic;
        bool m_Paused;
        Timeline* m_Anchor;
    };

//    class TimeMgr{
//    public:
//    private:
//    };
}