#include "World.h"

namespace gama{
    void ScoringSystem::Initialize(Timeline* anchor) {
        EventManager::GetInstance()->Register(this, SCORING_EVENTS);
        m_ScoringTimeline = new Timeline(anchor, 1);
    }

    bool once = true;
    bool once2 = true;

    void ScoringSystem::OnEvent(Event& event) {
        switch (event.type) {
            case Event::EventDeath:
            {
                Event phyReset(Event::EventResetPhysics, 0);
                phyReset.physicsEvent.characterUUID = event.scoringEvent.uuid;
                EventManager::GetInstance()->Raise(phyReset);

                //TODO CHANGE PRIORITY TO CURR TIME + 15.
                Event rEvent(Event::EventRespawn, 0);
                sf::Vector2f* spawnLoc = m_SpawnLocations.front();
                rEvent.renderingEvent.mainUUID = event.scoringEvent.uuid;
                rEvent.renderingEvent.spawnX = spawnLoc->x;
                rEvent.renderingEvent.spawnY = spawnLoc->y;
                m_SpawnLocations.pop_front();
                m_SpawnLocations.push_back(spawnLoc);
                EventManager::GetInstance()->Execute(rEvent);
                // TODO: DISPATCH EVENT TO THE NETWORK.
                break;
            }
            case Event::EventAddSpawn:
            {
                auto* spawnLoc = new sf::Vector2f(event.scoringEvent.spawnPointX,
                                                          event.scoringEvent.spawnPointY);
                m_SpawnLocations.push_back(spawnLoc);
                break;
            }
            default:
                break;
        }
    }

    void ScoringSystem::Shutdown() {

    }
}