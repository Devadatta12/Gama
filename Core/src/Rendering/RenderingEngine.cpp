#include "Rendering.h"

namespace gama {

    void RenderingEngine::Initialize(std::string game) {
        EventManager::GetInstance()->Register(this, RENDERING_EVENTS);
        m_Window = new sf::RenderWindow(sf::VideoMode(800,600),game,sf::Style::Default);
        m_Camera = new sf::View(sf::FloatRect(200.f, 0.f, 400.f, 600.f));
        m_Window->setView(*m_Camera);
        m_LastRenderedTime = m_RenderingTimeline->getTime();
    }

    bool RenderingEngine::PollWindow() {
        if (m_Window != nullptr){
            sf::Event event = {};
            while (m_Window->pollEvent(event)){
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed)
                {
                    m_Window->close();
                    Event leaveEvent(Event::EventCharacterLeaves, m_RenderingTimeline->getGlobalTime());
                    EventManager::GetInstance()->Raise(leaveEvent);
                    return false;
                }
                else if (event.type == sf::Event::Resized)
                {
                if (m_ResizeMode){
                    m_Camera->setSize(static_cast<float>(event.size.width),
                                 static_cast<float>(event.size.height));
                    m_Window->setView(*m_Camera);
                }
                else {
                    m_Window->setView(m_Window->getDefaultView());
                }
                }
                else if(event.type == sf::Event::GainedFocus){
                    std::cout<<"FOCUS GAINED"<<std::endl;
                    Event gainedFocus(Event::EventFocusGained, m_RenderingTimeline->getGlobalTime());
                    EventManager::GetInstance()->Raise(gainedFocus);
                }
                else if(event.type == sf::Event::LostFocus){
                    std::cout<<"FOCUS LOST"<<std::endl;
                    Event lostFocus(Event::EventFocusLost, m_RenderingTimeline->getGlobalTime());
                    EventManager::GetInstance()->Raise(lostFocus);
                }
            }
            return true;
        }
        return false;
    }

    void RenderingEngine::Render() {
        int64_t currTime = m_RenderingTimeline->getTime();
        int64_t delta = currTime - m_LastRenderedTime;
        if (delta < 1){
            return;
        }
        m_LastRenderedTime = currTime;
        // RENDERING -------------------------
        // clear the window with blue color
        m_Window->clear(sf::Color::Black);
        m_Window->setView(*m_Camera);
        for (auto mesh: m_RenderMeshes) {
            mesh.second->Draw(*m_Window);
        }
        m_Window->display();
    }

    void RenderingEngine::OnEvent(Event& event) {
        switch(event.type){
            case Event::EventRespawn:
            {
                long characterId = event.renderingEvent.mainUUID;
                Mesh* characterMesh = m_RenderMeshes.find(characterId)->second;
                float currPosX = (event.renderingEvent.focus) ? m_Camera->getCenter().x :
                                                                characterMesh->GetPosition().x;
                float delta = 0;
                sf::Vector2f location;
                location.x = event.renderingEvent.spawnX;
                location.y = event.renderingEvent.spawnY;
                characterMesh->Place(Mesh::ABSOLUTE, location);
                delta = location.x - currPosX;
                sf::Vector2f cameraShift(delta, 0);
                m_Camera->move(cameraShift);
                for (auto boundary: m_CameraUUIDs) {
                    Mesh* bMesh = m_RenderMeshes.find(boundary)->second;
                    if (bMesh->GetPosition().x < m_Camera->getCenter().x){
                        // Left Boundary.
                        float leftBoundary = m_Camera->getCenter().x - (m_Camera->getSize().x/2);
                        sf::Vector2f newLocation(leftBoundary, 0);
                        bMesh->Place(Mesh::ABSOLUTE, newLocation);
                    } else {
                        // Right Boundary.
                        float rightBoundary = m_Camera->getCenter().x + (m_Camera->getSize().x/2);
                        sf::Vector2f newLocation(rightBoundary, 0);
                        bMesh->Place(Mesh::ABSOLUTE, newLocation);
                    }
                }
                //std::cout<<"Respawn done "<<std::endl;
                break;
            }
            case Event::EventCameraFollow:
                {
                    long boundaryId = event.renderingEvent.otherUUID;
                    long characterId = event.renderingEvent.mainUUID;
                    Mesh* boundaryMesh = m_RenderMeshes.find(boundaryId)->second;
                    Mesh* characterMesh = m_RenderMeshes.find(characterId)->second;
                    sf::FloatRect currBoundary = boundaryMesh->GetBoundingBox();
                    float windowWidth = static_cast<float>(m_Window->getSize().x);
                    sf::Vector2f cameraSize = m_Camera->getSize();

                    if (currBoundary.left > m_Camera->getCenter().x &&
                            (currBoundary.left+currBoundary.width)!=windowWidth){
                        // The right boundary.
                        float delta = characterMesh->GetPosition().x - m_Camera->getCenter().x;
                        sf::Vector2f cameraShift = sf::Vector2f(delta, 0);
                        m_Camera->move(cameraShift);
                        float cameraEnd = (m_Camera->getCenter().x + cameraSize.x/2);
                        float cameraStart = (m_Camera->getCenter().x - cameraSize.x/2);
                        float rightBoundary = (cameraEnd > windowWidth) ?
                                (windowWidth - currBoundary.width) : (cameraEnd - currBoundary.width);
                        float leftBoundary = (cameraEnd > windowWidth) ?
                                             (cameraStart):
                                             (rightBoundary - cameraSize.x + currBoundary.width);
                        sf::Vector2f rightBLoc = sf::Vector2f(rightBoundary, 0);
                        sf::Vector2f leftBLoc = sf::Vector2f(leftBoundary, 0);
                        boundaryMesh->Place(Mesh::ABSOLUTE, rightBLoc);
                        for (auto boundary: m_CameraUUIDs) {
                            if (boundary != boundaryId){
                                Mesh* bMesh = m_RenderMeshes.find(boundary)->second;
                                bMesh->Place(Mesh::ABSOLUTE, leftBLoc);
                            }
                        }
                    } else{
                        // The left boundary.
                        float delta = m_Camera->getCenter().x - characterMesh->GetPosition().x;
                        sf::Vector2f cameraShift = sf::Vector2f(-delta, 0);
                        m_Camera->move(cameraShift);
                        float cameraEnd = (m_Camera->getCenter().x + cameraSize.x/2);
                        float cameraStart = (m_Camera->getCenter().x - cameraSize.x/2);
                        float leftBoundary = (cameraStart < 0) ? 0 : (cameraStart);
                        float rightBoundary = cameraEnd;
                        sf::Vector2f rightBLoc = sf::Vector2f(rightBoundary, 0);
                        sf::Vector2f leftBLoc = sf::Vector2f(leftBoundary, 0);
                        boundaryMesh->Place(Mesh::ABSOLUTE, rightBLoc);
                        for (auto boundary: m_CameraUUIDs) {
                            if (boundary != boundaryId){
                                Mesh* bMesh = m_RenderMeshes.find(boundary)->second;
                                bMesh->Place(Mesh::ABSOLUTE, leftBLoc);
                            }
                        }
                    }
                    break;
                }
            case Event::EventAddRendering:
            {
                long objectUUID = event.renderingEvent.mainUUID;
                Mesh* objectMesh = event.renderingEvent.mesh;
                if (objectMesh != nullptr)
                    m_RenderMeshes.insert({objectUUID, objectMesh});
                break;
            }
            case Event::EventWindowMode:
            {
                m_ResizeMode = !m_ResizeMode;
                break;
            }
            case Event::EventPinCamera:
            {
                long cameraObjUUID = event.renderingEvent.mainUUID;
                m_CameraUUIDs.push_back(cameraObjUUID);
                break;
            }
            case Event::EventRemoveRendering:
            {
                long removeUUID = event.renderingEvent.mainUUID;
                m_RenderMeshes.erase(removeUUID);
                break;
            }
            case Event::EventStartRecording:
            {
                for (auto renderMesh: m_RenderMeshes) {
                    m_Saved.insert({renderMesh.first, sf::Vector2f(renderMesh.second->GetPosition())});
                }
                m_CamSaved.x = m_Camera->getCenter().x;
                m_CamSaved.y = m_Camera->getCenter().y;
                break;
            }
            case Event::EventStartReplay:
            {
                for (auto renderMesh: m_RenderMeshes) {
                    auto pCopy = m_Saved.find(renderMesh.first);
                    if (pCopy == m_Saved.end()){
                        continue;
                    }
                    renderMesh.second->Place(Mesh::ABSOLUTE, pCopy->second);
                }
                m_Camera->setCenter(m_CamSaved.x, m_CamSaved.y);
                m_Saved.clear();
            }
            default:
                break;
        }
    }

    void RenderingEngine::Shutdown() {

    }
}