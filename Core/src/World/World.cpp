#include "World.h"
#include "Utils.h"
#include "set"

namespace gama {


    void World::game1() {
        if (m_Peer != 0){
            EventManager::GetInstance()->Register(this, PEER_WORLD_EVENTS);

            Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 13,true, m_Anchor,
                                                       new sf::Vector2f(0.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                       new sf::Vector2f(266.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 12, true, m_Anchor,
                                                       new sf::Vector2f(532.f, 500.f),
                                                       new sf::Vector2f(268.f, 100.f));

            auto* platformTimeline = new Timeline(nullptr, 17);


            Entity* movingPlatform1 = new MovingPlatform(++SEQ, 5, true, platformTimeline, false,
                                                         new sf::Vector2f(300.f, 350.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* movingPLatform2 = new MovingPlatform(++SEQ, 5, true, platformTimeline, true,
                                                         new sf::Vector2f(450.f, 200.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                    new sf::Vector2f(2.f, 600.f));
            Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                     new sf::Vector2f(2.f, 600.f));
            Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));
            Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));

            Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(600.f, 1.f));

            sf::Vector2f spawnLoc = m_Specs.spawnObjects[m_Peer-1];

            Entity* character = nullptr;
            Entity* spawnObj = nullptr;
            character = new Character(++SEQ+10*m_Peer, true,
                                      m_Anchor,
                                      new sf::Vector2f(spawnLoc.x, spawnLoc.y), 1, true);
            spawnObj = new SpawnPoint(++SEQ, true, spawnLoc.x, spawnLoc.y);



            m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                               {movingPLatform2->GetUUID(), movingPLatform2},
                               {fixedPlatform1->GetUUID(), fixedPlatform1},
                               {fixedPlatform2->GetUUID(), fixedPlatform2},
                               {fixedPlatform3->GetUUID(), fixedPlatform3},
                               {sideBoundary1->GetUUID(), sideBoundary1},
                               {sideBoundary2->GetUUID(), sideBoundary2},
                               {deathZone1->GetUUID(), deathZone1},
                               {deathZone2->GetUUID(), deathZone2},
                               {deathZone3->GetUUID(), deathZone3},
                               {spawnObj->GetUUID(), spawnObj},
                               {character->GetUUID(), character}});

        } else{
            if (m_IsServer){
                EventManager::GetInstance()->Register(this, SERVER_WORLD_EVENTS);

                Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 13,true, m_Anchor,
                                                           new sf::Vector2f(0.f, 500.f),
                                                           new sf::Vector2f(266.f, 100.f));
                Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                           new sf::Vector2f(266.f, 500.f),
                                                           new sf::Vector2f(266.f, 100.f));
                Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 12, true, m_Anchor,
                                                           new sf::Vector2f(532.f, 500.f),
                                                           new sf::Vector2f(268.f, 100.f));

                Entity* movingPlatform1 = new MovingPlatform(++SEQ, 5, true, m_Anchor, false,
                                                             new sf::Vector2f(300.f, 350.f),
                                                             new sf::Vector2f(20.f, 60.f));
                Entity* movingPLatform2 = new MovingPlatform(++SEQ, 5, true, m_Anchor, true,
                                                             new sf::Vector2f(450.f, 200.f),
                                                             new sf::Vector2f(20.f, 60.f));


//        Entity* spawnPoint = new SpawnPoint(++SEQ, true, 120, 350);
                Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                        new sf::Vector2f(2.f, 600.f));
                Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                         new sf::Vector2f(2.f, 600.f));
                Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));
                Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));

                Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(600.f, 1.f));

                m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                                   {movingPLatform2->GetUUID(), movingPLatform2},
                                   {fixedPlatform1->GetUUID(), fixedPlatform1},
                                   {fixedPlatform2->GetUUID(), fixedPlatform2},
                                   {fixedPlatform3->GetUUID(), fixedPlatform3},
                                   {sideBoundary1->GetUUID(), sideBoundary1},
                                   {sideBoundary2->GetUUID(), sideBoundary2},
                                   {deathZone1->GetUUID(), deathZone1},
                                   {deathZone2->GetUUID(), deathZone2},
                                   {deathZone3->GetUUID(), deathZone3}});
            } else {
                EventManager::GetInstance()->Register(this, CLIENT_WORLD_EVENTS);
            }
        }
    }

    void World::game2(){
        if (m_Peer != 0){
            EventManager::GetInstance()->Register(this, PEER_WORLD_EVENTS);

            Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 13,true, m_Anchor,
                                                       new sf::Vector2f(0.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                       new sf::Vector2f(266.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 12, true, m_Anchor,
                                                       new sf::Vector2f(532.f, 500.f),
                                                       new sf::Vector2f(268.f, 100.f));

            auto* platformTimeline = new Timeline(nullptr, 17);


            Entity* movingPlatform1 = new MovingPlatform(++SEQ, 5, true, platformTimeline, false,
                                                         new sf::Vector2f(300.f, 350.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* movingPLatform2 = new MovingPlatform(++SEQ, 5, true, platformTimeline, true,
                                                         new sf::Vector2f(450.f, 200.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                    new sf::Vector2f(2.f, 600.f));
            Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                     new sf::Vector2f(2.f, 600.f));
            Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));
            Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));

            Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(600.f, 1.f));

            sf::Vector2f spawnLoc = m_Specs.spawnObjects[m_Peer-1];

            Entity* character = nullptr;
            Entity* spawnObj = nullptr;
            character = new Character(++SEQ+10*m_Peer, true,
                                      m_Anchor,
                                      new sf::Vector2f(spawnLoc.x, spawnLoc.y), 1, true);
            spawnObj = new SpawnPoint(++SEQ, true, spawnLoc.x, spawnLoc.y);



            m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                               {movingPLatform2->GetUUID(), movingPLatform2},
                               {fixedPlatform1->GetUUID(), fixedPlatform1},
                               {fixedPlatform2->GetUUID(), fixedPlatform2},
                               {fixedPlatform3->GetUUID(), fixedPlatform3},
                               {sideBoundary1->GetUUID(), sideBoundary1},
                               {sideBoundary2->GetUUID(), sideBoundary2},
                               {deathZone1->GetUUID(), deathZone1},
                               {deathZone2->GetUUID(), deathZone2},
                               {deathZone3->GetUUID(), deathZone3},
                               {spawnObj->GetUUID(), spawnObj},
                               {character->GetUUID(), character}});

        } else{
            if (m_IsServer){
                EventManager::GetInstance()->Register(this, SERVER_WORLD_EVENTS);

                Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 23,true, m_Anchor,
                                                           new sf::Vector2f(0.f, 0.f),
                                                           new sf::Vector2f(20.f, 600.f));
                Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(60.f, 0.f),
                                                           new sf::Vector2f(680.f, 20.f));

                Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(780.f, 0.f),
                                                           new sf::Vector2f(20.f, 600.f));
                Entity* fixedPlatform4 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(60.f, 580.f),
                                                           new sf::Vector2f(680.f, 20.f));

                Entity* fixedPlatform5 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(60.f, 20.f),
                                                           new sf::Vector2f(20.f, 200.f));
                Entity* fixedPlatform6 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(60.f, 380.f),
                                                           new sf::Vector2f(20.f, 200.f));

                Entity* fixedPlatform7 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(720.f, 20.f),
                                                           new sf::Vector2f(20.f, 200.f));
                Entity* fixedPlatform8 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(720.f, 380.f),
                                                           new sf::Vector2f(20.f, 200.f));


                // The Platforms in between:
                Entity* fixedPlatform9 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(150.f, 200.f),
                                                           new sf::Vector2f(500.f, 20.f));
                Entity* fixedPlatform10 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(150.f, 380.f),
                                                           new sf::Vector2f(500.f, 20.f));

                Entity* fixedPlatform11 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(150.f, 100.f),
                                                           new sf::Vector2f(20.f, 100.f));
                Entity* fixedPlatform12 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(630.f, 100.f),
                                                           new sf::Vector2f(20.f, 100.f));
                Entity* fixedPlatform13 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                            new sf::Vector2f(390.f, 100.f),
                                                            new sf::Vector2f(20.f, 100.f));

                // The lower layer.

                Entity* fixedPlatform14 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                           new sf::Vector2f(220.f, 100.f),
                                                           new sf::Vector2f(360.f, 10.f));

                Entity* fixedPlatform15 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                            new sf::Vector2f(150.f, 400.f),
                                                            new sf::Vector2f(20.f, 100.f));
                Entity* fixedPlatform16 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                            new sf::Vector2f(630.f, 400.f),
                                                            new sf::Vector2f(20.f, 100.f));
                Entity* fixedPlatform17 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                            new sf::Vector2f(390.f, 400.f),
                                                            new sf::Vector2f(20.f, 100.f));

                Entity* fixedPlatform18 = new FixedPlatform(++SEQ, 23, true, m_Anchor,
                                                            new sf::Vector2f(220.f, 490.f),
                                                            new sf::Vector2f(360.f, 10.f));

                Entity* movingPlatform1 = new MovingPlatform(++SEQ, 22, true, m_Anchor, false,
                                                             new sf::Vector2f(300.f, 25.f),
                                                             new sf::Vector2f(20.f, 60.f));
                Entity* movingPLatform2 = new MovingPlatform(++SEQ, 24, true, m_Anchor, false,
                                                             new sf::Vector2f(300.f, 280.f),
                                                             new sf::Vector2f(20.f, 60.f));
                Entity* movingPLatform3 = new MovingPlatform(++SEQ, 22, true, m_Anchor, false,
                                                             new sf::Vector2f(300.f, 510.f),
                                                             new sf::Vector2f(20.f, 60.f));

                Entity* coin1 = new CollectibleItem(++SEQ, 21, true,
                                                             new sf::Vector2f(300.f, 150.f),
                                                             new sf::Vector2f(20.f, 30.f));

                Entity* coin2 = new CollectibleItem(++SEQ, 21, true,
                                                    new sf::Vector2f(300.f, 420.f),
                                                    new sf::Vector2f(20.f, 30.f));
                Entity* coin3 = new CollectibleItem(++SEQ, 21, true,
                                                    new sf::Vector2f(470.f, 150.f),
                                                    new sf::Vector2f(20.f, 30.f));
                Entity* coin4 = new CollectibleItem(++SEQ, 21, true,
                                                    new sf::Vector2f(470.f, 420.f),
                                                    new sf::Vector2f(20.f, 30.f));
                Entity* coin5 = new CollectibleItem(++SEQ, 21, true,
                                                    new sf::Vector2f(400.f, 290.f),
                                                    new sf::Vector2f(20.f, 30.f));


//        Entity* spawnPoint = new SpawnPoint(++SEQ, true, 120, 350);
                Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                        new sf::Vector2f(2.f, 600.f));
                Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                         new sf::Vector2f(2.f, 600.f));
                Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));
                Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));

                Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(800.f, 1.f));
                Entity* deathZone4 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 599.f),
                                                   new sf::Vector2f(800.f, 1.f));

                m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                                   {movingPLatform2->GetUUID(), movingPLatform2},
                                   {movingPLatform3->GetUUID(), movingPLatform3},
                                   {fixedPlatform1->GetUUID(), fixedPlatform1},
                                   {fixedPlatform2->GetUUID(), fixedPlatform2},
                                   {fixedPlatform3->GetUUID(), fixedPlatform3},
                                   {fixedPlatform4->GetUUID(), fixedPlatform4},
                                   {fixedPlatform5->GetUUID(), fixedPlatform5},
                                   {fixedPlatform6->GetUUID(), fixedPlatform6},
                                   {fixedPlatform7->GetUUID(), fixedPlatform7},
                                   {fixedPlatform8->GetUUID(), fixedPlatform8},
                                   {fixedPlatform9->GetUUID(), fixedPlatform9},
                                   {fixedPlatform10->GetUUID(), fixedPlatform10},
                                   {fixedPlatform11->GetUUID(), fixedPlatform11},
                                   {fixedPlatform12->GetUUID(), fixedPlatform12},
                                   {fixedPlatform13->GetUUID(), fixedPlatform13},
                                   {fixedPlatform14->GetUUID(), fixedPlatform14},
                                   {fixedPlatform15->GetUUID(), fixedPlatform15},
                                   {fixedPlatform16->GetUUID(), fixedPlatform16},
                                   {fixedPlatform17->GetUUID(), fixedPlatform17},
                                   {fixedPlatform18->GetUUID(), fixedPlatform18},
                                   {sideBoundary1->GetUUID(), sideBoundary1},
                                   {sideBoundary2->GetUUID(), sideBoundary2},
                                   {deathZone1->GetUUID(), deathZone1},
                                   {deathZone2->GetUUID(), deathZone2},
                                   {deathZone3->GetUUID(), deathZone3},
                                   {deathZone4->GetUUID(), deathZone4},
                                   {coin1->GetUUID(), coin1},
                                   {coin2->GetUUID(), coin2},
                                   {coin3->GetUUID(), coin3},
                                   {coin4->GetUUID(), coin4},
                                   {coin5->GetUUID(), coin5}});
            } else {
                EventManager::GetInstance()->Register(this, CLIENT_WORLD_EVENTS);
            }
        }
    }

    void World::game3() {
        if (m_Peer != 0){
            EventManager::GetInstance()->Register(this, PEER_WORLD_EVENTS);

            Entity* fixedPlatform1 = new FixedPlatform(++SEQ, 13,true, m_Anchor,
                                                       new sf::Vector2f(0.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform2 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                       new sf::Vector2f(266.f, 500.f),
                                                       new sf::Vector2f(266.f, 100.f));
            Entity* fixedPlatform3 = new FixedPlatform(++SEQ, 12, true, m_Anchor,
                                                       new sf::Vector2f(532.f, 500.f),
                                                       new sf::Vector2f(268.f, 100.f));

            auto* platformTimeline = new Timeline(nullptr, 17);


            Entity* movingPlatform1 = new MovingPlatform(++SEQ, 5, true, platformTimeline, false,
                                                         new sf::Vector2f(300.f, 350.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* movingPLatform2 = new MovingPlatform(++SEQ, 5, true, platformTimeline, true,
                                                         new sf::Vector2f(450.f, 200.f),
                                                         new sf::Vector2f(20.f, 60.f));
            Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                    new sf::Vector2f(2.f, 600.f));
            Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                     new sf::Vector2f(2.f, 600.f));
            Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));
            Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                               new sf::Vector2f(1.f, 600.f));

            Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                               new sf::Vector2f(600.f, 1.f));

            sf::Vector2f spawnLoc = m_Specs.spawnObjects[m_Peer-1];

            Entity* character = nullptr;
            Entity* spawnObj = nullptr;
            character = new Character(++SEQ+10*m_Peer, true,
                                      m_Anchor,
                                      new sf::Vector2f(spawnLoc.x, spawnLoc.y), 1, true);
            spawnObj = new SpawnPoint(++SEQ, true, spawnLoc.x, spawnLoc.y);



            m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                               {movingPLatform2->GetUUID(), movingPLatform2},
                               {fixedPlatform1->GetUUID(), fixedPlatform1},
                               {fixedPlatform2->GetUUID(), fixedPlatform2},
                               {fixedPlatform3->GetUUID(), fixedPlatform3},
                               {sideBoundary1->GetUUID(), sideBoundary1},
                               {sideBoundary2->GetUUID(), sideBoundary2},
                               {deathZone1->GetUUID(), deathZone1},
                               {deathZone2->GetUUID(), deathZone2},
                               {deathZone3->GetUUID(), deathZone3},
                               {spawnObj->GetUUID(), spawnObj},
                               {character->GetUUID(), character}});

        } else{
            if (m_IsServer){
                EventManager::GetInstance()->Register(this, SERVER_WORLD_EVENTS);

                Entity* movingPlatform1 = new MovingPlatform(++SEQ, 36, true, m_Anchor, false,
                                                             new sf::Vector2f(0.f, 0.f),
                                                             new sf::Vector2f(800.f, 600.f));

                Entity* leftMostTrackMargin = new FixedPlatform(++SEQ, 31,true, m_Anchor,
                                                           new sf::Vector2f(0.f, 0.f),
                                                           new sf::Vector2f(30.f, 600.f));
                Entity* bottomMostTrackMargin = new FixedPlatform(++SEQ, 32,true, m_Anchor,
                                                                new sf::Vector2f(0.f, 570.f),
                                                                new sf::Vector2f(800.f, 30.f));
                Entity* rightMostTrackMargin = new FixedPlatform(++SEQ, 33, true, m_Anchor,
                                                           new sf::Vector2f(770.f, 0.f),
                                                           new sf::Vector2f(30.f, 600.f));
                Entity* topMostTrackMargin = new FixedPlatform(++SEQ, 34, true, m_Anchor,
                                                                 new sf::Vector2f(130.f, 0.f),
                                                                 new sf::Vector2f(670.f, 30.f));

                // Textures in between:

                Entity* racePavilion1 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                                 new sf::Vector2f(130.f, 160.f),
                                                                 new sf::Vector2f(100.f, 310.f));
                Entity* racePavilion2 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                               new sf::Vector2f(230.f, 160.f),
                                                               new sf::Vector2f(100.f, 110.f));
                Entity* racePavilion3 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                          new sf::Vector2f(330.f, 370.f),
                                                          new sf::Vector2f(100.f, 200.f));
                Entity* racePavilion4 = new FixedPlatform(++SEQ, 11, true, m_Anchor,
                                                          new sf::Vector2f(430.f, 260.f),
                                                          new sf::Vector2f(110.f, 310.f));

                // Tracks margins in between.
                Entity* hMiddleTrackMargin1 = new FixedPlatform(++SEQ, 32, true, m_Anchor,
                                                         new sf::Vector2f(130.f, 130.f),
                                                         new sf::Vector2f(540.f, 30.f));
                Entity* vMiddleTrackMargin1 = new FixedPlatform(++SEQ, 31, true, m_Anchor,
                                                          new sf::Vector2f(640.f, 130.f),
                                                          new sf::Vector2f(30.f, 340.f));

                Entity* raceFinishMargin = new FixedPlatform(++SEQ, 31, true, m_Anchor,
                                                                new sf::Vector2f(130.f, 0.f),
                                                                new sf::Vector2f(30.f, 130.f));

                Entity* finishLine = new CollectibleItem(++SEQ, 35, true,
                                                    new sf::Vector2f(160.f, 30.f),
                                                    new sf::Vector2f(60.f, 100.f));

                Entity* portal1 = new CollectibleItem(++SEQ, 38, true,
                                                         new sf::Vector2f(30.f, 480.f),
                                                         new sf::Vector2f(40.f, 50.f));
                Entity* portal2 = new CollectibleItem(++SEQ, 38, true,
                                                      new sf::Vector2f(550.f, 350.f),
                                                      new sf::Vector2f(40.f, 50.f));


//        Entity* spawnPoint = new SpawnPoint(++SEQ, true, 120, 350);
                Entity* sideBoundary1= new SideBoundary(++SEQ, true, new sf::Vector2f(200.f, 0.f),
                                                        new sf::Vector2f(2.f, 600.f));
                Entity* sideBoundary2 = new SideBoundary(++SEQ, true, new sf::Vector2f(598.f, 0.f),
                                                         new sf::Vector2f(2.f, 600.f));
                Entity* deathZone1 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));
                Entity* deathZone2 = new DeathZone(++SEQ, true, new sf::Vector2f(799.f, 0.f),
                                                   new sf::Vector2f(1.f, 600.f));

                Entity* deathZone3 = new DeathZone(++SEQ, true, new sf::Vector2f(0.f, 0.f),
                                                   new sf::Vector2f(600.f, 1.f));

                m_Entities.insert({{movingPlatform1->GetUUID(), movingPlatform1},
                                   {leftMostTrackMargin->GetUUID(), leftMostTrackMargin},
                                   {rightMostTrackMargin->GetUUID(), rightMostTrackMargin},
                                   {topMostTrackMargin->GetUUID(), topMostTrackMargin},
                                   {bottomMostTrackMargin->GetUUID(), bottomMostTrackMargin},
                                   {racePavilion1->GetUUID(), racePavilion1},
                                   {racePavilion2->GetUUID(), racePavilion2},
                                   {racePavilion3->GetUUID(), racePavilion3},
                                   {racePavilion4->GetUUID(), racePavilion4},
                                   {vMiddleTrackMargin1->GetUUID(), vMiddleTrackMargin1},
                                   {hMiddleTrackMargin1->GetUUID(), hMiddleTrackMargin1},
                                   {raceFinishMargin->GetUUID(), raceFinishMargin},
                                   {finishLine->GetUUID(), finishLine},
                                   {sideBoundary1->GetUUID(), sideBoundary1},
                                   {sideBoundary2->GetUUID(), sideBoundary2},
                                   {deathZone1->GetUUID(), deathZone1},
                                   {deathZone2->GetUUID(), deathZone2},
                                   {deathZone3->GetUUID(), deathZone3},
                                   {portal1->GetUUID(), portal1},
                                   {portal2->GetUUID(), portal2}});
            } else {
                EventManager::GetInstance()->Register(this, CLIENT_WORLD_EVENTS);
            }
        }
    }

    void World::Initialize() {
        std::lock_guard<std::mutex> lock(*m_Mutex);
        if (m_GameName=="SpaceJump")
            game1();
        else if(m_GameName=="TreasureHunt")
            game2();
        else if(m_GameName=="GrandMotoTorque")
            game3();
        m_LastUpdateTime = m_Anchor->getTime();
    }

    void World::Update() {
        std::lock_guard<std::mutex> lock(*m_Mutex);
        int64_t currTime = m_Anchor->getTime();
        int64_t delta = currTime - m_LastUpdateTime;
        if (delta < 1){
            return;
        }
        m_LastUpdateTime = currTime;

        std::set<long> deletedEntities;
        for (auto entity: m_Entities) {
            if (entity.second->IsLocal()){
                entity.second->Update();

                if ((!m_IsServer || m_Peer!=0) && entity.second->GetType() == CHARACTER){
                    Event updateWorld(Event::EventLocalUpdate, 0);
                    std::string syncM = entity.second->Sync();
                    syncM = syncM.substr(0, syncM.size()-1);
                    updateWorld.networkEvent.message = new std::string(syncM);
                    EventManager::GetInstance()->Execute(updateWorld);
                    EventManager::curr_uuid = entity.second->GetUUID();
                    r_ScriptManager->runOne("Update", false, "object_context");
                    //std::cout<<"SCORE = "<<entity.second->GetScore()<<std::endl;
                }
            } else if((m_IsServer || m_Peer!=0) && entity.second->GetType() == CHARACTER){
                entity.second->IncHeartbeat();
                if (entity.second->GetHeartbeat() > 120){
                    std::cout<<"Heartbeat... "<< entity.second->GetHeartbeat()<<std::endl;
                    deletedEntities.insert(entity.first);
                }
            }
        }

        for (auto deletedId: deletedEntities){
            Entity* deletedEntity = m_Entities.find(deletedId)->second;
            deletedEntity->Release();
            m_Entities.erase(deletedId);
        }
    }

    void World::OnEvent(Event& event) {
        std::lock_guard<std::mutex> lock(*m_Mutex);
        switch (event.type) {
            case Event::EventIncreaseHealth:
            {
                std::cout<<"Increase Health Event"<<std::endl;
                Entity* entity = m_Entities.find(EventManager::curr_uuid)->second;
                entity->IncScore();
            }
            case Event::EventCharacterJoin:
            {
                std::string response;
                long newUUID = ++SEQ;
                // A Spawn Point attached to the Character.
                sf::Vector2f spawnLoc{0,0};
                if (m_GameName == "SpaceJump"){
                    spawnLoc = m_Specs.spawnObjects.front();
                    m_Specs.spawnObjects.pop_front();
                } else if(m_GameName == "TreasureHunt"){
                    spawnLoc = m_Specs.spawnObjects2.front();
                    m_Specs.spawnObjects2.pop_front();
                } else {
                    spawnLoc = m_Specs.spawnObjects3.front();
                    m_Specs.spawnObjects3.pop_front();
                }

                for (auto entity: m_Entities) {
                    response += *entity.second->Serialize();
                }
                Entity* character = nullptr;
                Entity* spawnObj = nullptr;
                std::cout<<"Reached Here"<<std::endl;
                if (m_GameName == "SpaceJump"){
                    character = new Character(newUUID, false,
                                              m_Anchor,
                                              new sf::Vector2f(spawnLoc.x, spawnLoc.y), 1, true);
                    // Create Script will run here to set gravity.
                    spawnObj = new SpawnPoint(++SEQ, false, spawnLoc.x, spawnLoc.y);
                    response = "L"+*character->Serialize()+*spawnObj->Serialize()+response;
                    response = response.substr(0, response.size() - 1);
                    m_Entities.insert({character->GetUUID(), character});
                    m_Entities.insert({spawnObj->GetUUID(), spawnObj});
                    event.worldEvent.message = new std::string(response);
                } else if(m_GameName == "TreasureHunt"){
                    character = new Character(newUUID, false,
                                              m_Anchor,
                                              new sf::Vector2f(spawnLoc.x, spawnLoc.y), 25, false);
                    // Create Script will run here to set gravity.
                    spawnObj = new SpawnPoint(++SEQ, false, spawnLoc.x, spawnLoc.y);
                    response = "L"+*character->Serialize()+*spawnObj->Serialize()+response;
                    response = response.substr(0, response.size() - 1);
                    m_Entities.insert({character->GetUUID(), character});
                    m_Entities.insert({spawnObj->GetUUID(), spawnObj});
                    event.worldEvent.message = new std::string(response);
                } else if(m_GameName == "GrandMotoTorque"){
                    character = new Character(newUUID, false,
                                              m_Anchor,
                                              new sf::Vector2f(spawnLoc.x, spawnLoc.y), 37, false);
                    // Create Script will run here to set gravity.
                    spawnObj = new SpawnPoint(++SEQ, false, spawnLoc.x, spawnLoc.y);
                    response = "L"+*character->Serialize()+*spawnObj->Serialize()+response;
                    response = response.substr(0, response.size() - 1);
                    m_Entities.insert({character->GetUUID(), character});
                    m_Entities.insert({spawnObj->GetUUID(), spawnObj});
                    event.worldEvent.message = new std::string(response);
                }
                break;
            }
            case Event::EventCreateWorld:
            {
                std::string* serializeWorld = event.worldEvent.message;
                std::vector<std::string> entities = tokenize(*serializeWorld, "+");
                for (auto entity: entities) {
                    Entity* newEntity = EntityFactory::Construct(m_Anchor, entity);
                    m_Entities.insert({newEntity->GetUUID(), newEntity});
                }
                break;
            }
            case Event::EventSyncWorld:
            {
                std::string* worldUpdates = event.worldEvent.message;
                std::vector<std::string> entityUpdates = tokenize(*worldUpdates, "+");
                std::set<long> uuids;
                std::set<long> deletedEntities;
                for (const auto& entityUpdate: entityUpdates) {
                    std::vector<std::string> tokens = tokenize(entityUpdate, "#");
                    long uuid = std::stol(tokens[0]);
                    float posX = std::stof(tokens[1]);
                    float posY = std::stof(tokens[2]);
                    uuids.insert(uuid);
                    // If the uuid is not there in m_Entities then this is a new character.
                    if (m_Entities.find(uuid) == m_Entities.end()){
                            if (m_GameName == "SpaceJump"){
                                Entity* character = new Character(uuid, false, m_Anchor,
                                                                  new sf::Vector2f(posX, posY), 1, true);
                                m_Entities.insert({character->GetUUID(), character});
                            } else if(m_GameName == "TreasureHunt"){
                                Entity* character = new Character(uuid, false, m_Anchor,
                                                                  new sf::Vector2f(posX, posY), 25, false);
                                m_Entities.insert({character->GetUUID(), character});
                            } else if(m_GameName == "GrandMotoTorque"){
                                Entity* character = new Character(uuid, false, m_Anchor,
                                                                  new sf::Vector2f(posX, posY), 37, false);
                                m_Entities.insert({character->GetUUID(), character});
                            }
                    } else {
                        Entity* entity = m_Entities.find(uuid)->second;
                        if (!entity->IsLocal()){
                            entity->OnEvent(posX, posY);
                        }
                    }
                }

                // If a character was deleted.
                for (auto entity: m_Entities) {
                    if (uuids.find(entity.first) == uuids.end() &&
                    (entity.second->GetType() == CHARACTER || entity.second->GetType() == PROJECTILE)){
                        deletedEntities.insert(entity.first);
                    }
                }
                for (auto deletedId: deletedEntities){
                    Entity* deletedEntity = m_Entities.find(deletedId)->second;
                    deletedEntity->Release();
                }
                break;
            }
            case Event::EventCharacterUpdate:
            {
                std::string* characterUpdate = event.worldEvent.message;
                std::vector<std::string> tokens = tokenize(*characterUpdate, "#");
                long uuid = std::stol(tokens[0]);
                float posX = std::stof(tokens[1]);
                float posY = std::stof(tokens[2]);
                auto entity = m_Entities.find(uuid);
                if (entity != m_Entities.end()){
                    entity->second->OnEvent(posX, posY);
                    if (m_IsServer || m_Peer!=0)
                        entity->second->ResetHeartbeat();
                } else if(m_Peer != 0){
                        // PEER TO PEER ONLY AVAILABLE ON ONE GAME.
                        Entity* character = new Character(uuid, false, m_Anchor,
                                                          new sf::Vector2f(posX, posY), 1, true);
                        m_Entities.insert({character->GetUUID(), character});
                }
                break;
            }
            case Event::EventSendWorld:
            {
                std::string response;
                for (auto entity: m_Entities) {
                    response += entity.second->Sync();
                }
                response = response.substr(0, response.size() - 1);

                event.worldEvent.message = new std::string(response);
                break;
            }
            case Event::EventCharacterLeaves:
            {
                for (auto entity: m_Entities) {
                    if (entity.second->IsLocal() && entity.second->GetType() == CHARACTER){
                        int64_t globalTime = m_Anchor->getGlobalTime();
                        std::string characterLeaves = std::to_string(entity.first);
                        Event characterEvent(Event::EventClientLeft, globalTime);
                        characterEvent.networkEvent.message = new std::string(characterLeaves);
                        EventManager::GetInstance()->Raise(characterEvent);
                        break;
                    }
                }
                break;
            }
            case Event::EventCharacterDelete:
            {
                std::string* characterUpdate = event.worldEvent.message;
                long uuid = std::stol(*characterUpdate);
                if (m_Entities.find(uuid) != m_Entities.end()){
                    m_Entities.find(uuid)->second->Release();
                }
                m_Entities.erase(uuid);
                break;
            }
            case Event::EventUpdateTime:
            {
                m_LastUpdateTime = m_Anchor->getTime();
            }
            default:
                break;
        }
    }

    void World::Shutdown() {

    }

    std::string World::Serialize() {
        return "nullptr";
    }

    void World::Bind(v8::Isolate *isolate, v8::Local<v8::Context> &object_context) {
        for (auto entity: m_Entities) {
            if (entity.second->IsLocal()){
                entity.second->ExposeToV8(isolate, object_context);
            }
        }
    }

}
