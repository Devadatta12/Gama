#include "Timelines.h"
#include "iostream"

int64_t gama::Timeline::getTime() {
    std::lock_guard<std::recursive_mutex> lock(m_Mutex);
    if (m_Paused){
        return (m_LastPausedTime - m_StartTime - m_ElapsedPausedTime)/m_Tic;
    }
    else if (m_Anchor == nullptr){
        return (time() - m_StartTime - m_ElapsedPausedTime)/m_Tic;
    } else {
        return (m_Anchor->getTime() - m_StartTime - m_ElapsedPausedTime)/m_Tic;
    }
}

int64_t gama::Timeline::getGlobalTime() {
    std::lock_guard<std::recursive_mutex> lock(m_Mutex);
    if (m_Anchor == nullptr){
        return getTime();
    } else {
        return m_Anchor->getGlobalTime();
    }
}


void gama::Timeline::pause() {
    std::lock_guard<std::recursive_mutex> lock(m_Mutex);
    m_Paused = true;
    if (m_Anchor == nullptr){
        m_LastPausedTime = time();
    } else{
        m_LastPausedTime = m_Anchor->getTime();
    }
}

void gama::Timeline::unpause() {
    std::lock_guard<std::recursive_mutex> lock(m_Mutex);
    m_Paused = false;
    if (m_Anchor == nullptr){
        m_ElapsedPausedTime += (time() - m_LastPausedTime);
    } else{
        m_ElapsedPausedTime += (m_Anchor->getTime() - m_LastPausedTime);
    }
}

void gama::Timeline::changeTic(int tic) {
    std::lock_guard<std::recursive_mutex> lock(m_Mutex);
    std::cout<<"SPEED CHANGE = "<<tic<<std::endl;
    m_Tic += tic;
    std::cout<<"TIC SIZE = "<<m_Tic<<std::endl;
    if (m_Tic <= 0){
        m_Tic = 1;
    }
}

bool gama::Timeline::isPaused() {
    std::lock_guard<std::recursive_mutex> lock(m_Mutex);
    bool isPaused = m_Paused;
    return isPaused;
}