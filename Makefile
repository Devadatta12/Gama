uname_s := $(shell uname -s)
INCLUDE =
LINKER =
STANDARD =
ifeq ($(uname_s),Darwin)
	INCLUDE = -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/cppzmq/4.10.0/include -I/opt/homebrew/Cellar/zeromq/4.3.4/include -I/opt/homebrew/Cellar/v8/11.7.439.16/include -I./include
	LINKER = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -L/opt/homebrew/Cellar/cppzmq/4.10.0/lib -L/opt/homebrew/Cellar/zeromq/4.3.4/lib
	STANDARD = -std=c++17
else ifeq ($(uname_s),Linux)
	INCLUDE = -I/usr/include -I./include -I/usr/include/v8
	LINKER = -L/usr/lib/aarch64-linux-gnu -pthread
	STANDARD = -std=c++17
endif

all: game SpaceJump SpaceJumpServer gamepeer TreasureHunt TreasureHuntServer GrandMotoTorque GrandMotoTorqueServer

GrandMotoTorque: ./build/GrandMotoTorque.o Core
	g++ ./build/ReplaySystem.o ./build/CollectibleItem.o ./build/GrandMotoTorque.o ./build/ScriptManager.o ./build/Projectile.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o GrandMotoTorque $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./GrandMotoTorque

GrandMotoTorqueServer: ./build/GrandMotoTorqueServer.o Core
	g++ ./build/GrandMotoTorqueServer.o ./build/CollectibleItem.o ./build/v8helpers.o ./build/ScriptManager.o ./build/EventManager.o ./build/Projectile.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o GrandMotoTorqueServer $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./GrandMotoTorqueServer

game: ./build/Game.o Core
	g++ ./build/Game.o ./build/CollectibleItem.o ./build/ScriptManager.o ./build/EventManager.o ./build/Projectile.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o game $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./game

gamepeer: ./build/GamePeer.o Core
	 g++ ./build/GamePeer.o ./build/CollectibleItem.o ./build/ScriptManager.o ./build/EventManager.o ./build/Projectile.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o gamepeer $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./gamepeer

SpaceJump: ./build/SpaceJump.o Core
	g++ ./build/ReplaySystem.o ./build/CollectibleItem.o ./build/SpaceJump.o ./build/ScriptManager.o ./build/Projectile.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o SpaceJump $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./SpaceJump

TreasureHunt: ./build/TreasureHunt.o Core
	g++ ./build/ReplaySystem.o ./build/CollectibleItem.o ./build/TreasureHunt.o ./build/ScriptManager.o ./build/Projectile.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o TreasureHunt $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./TreasureHunt

TreasureHuntServer: ./build/TreasureHuntServer.o Core
	g++ ./build/TreasureHuntServer.o ./build/CollectibleItem.o ./build/v8helpers.o ./build/ScriptManager.o ./build/EventManager.o ./build/Projectile.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o TreasureHuntServer $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./TreasureHuntServer

SpaceJumpServer: ./build/SpaceJumpServer.o Core
	g++ ./build/SpaceJumpServer.o ./build/CollectibleItem.o ./build/v8helpers.o ./build/ScriptManager.o ./build/EventManager.o ./build/Projectile.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o SpaceJumpServer $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system -lv8
	chmod +x ./SpaceJumpServer


./build/GrandMotoTorque.o: Core/src/Multiplayer/GrandMotoTorque/GrandMotoTorque.cpp
	g++ $(STANDARD) -c Core/src/Multiplayer/GrandMotoTorque/GrandMotoTorque.cpp -o ./build/GrandMotoTorque.o $(INCLUDE)

./build/GrandMotoTorqueServer.o: Core/src/Multiplayer/GrandMotoTorque/GrandMotoTorqueServer.cpp
	g++ $(STANDARD) -c Core/src/Multiplayer/GrandMotoTorque/GrandMotoTorqueServer.cpp -o ./build/GrandMotoTorqueServer.o $(INCLUDE)

./build/TreasureHuntServer.o: Core/src/Multiplayer/TreasureHunt/TreasureHuntServer.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/TreasureHunt/TreasureHuntServer.cpp -o ./build/TreasureHuntServer.o $(INCLUDE)

./build/TreasureHunt.o: Core/src/Multiplayer/TreasureHunt/TreasureHunt.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/TreasureHunt/TreasureHunt.cpp -o ./build/TreasureHunt.o $(INCLUDE)

./build/Game.o: ./Core/src/Game.cpp
	g++ $(STANDARD) -c ./Core/src/Game.cpp -o ./build/Game.o $(INCLUDE)

./build/GamePeer.o:Core/src/Multiplayer/SpaceJump/GamePeer.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/SpaceJump/GamePeer.cpp -o ./build/GamePeer.o $(INCLUDE)

./build/SpaceJump.o: Core/src/Multiplayer/SpaceJump/SpaceJump.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/SpaceJump/SpaceJump.cpp -o ./build/SpaceJump.o $(INCLUDE)

./build/SpaceJumpServer.o: Core/src/Multiplayer/SpaceJump/SpaceJumpServer.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/SpaceJump/SpaceJumpServer.cpp -o ./build/SpaceJumpServer.o $(INCLUDE)

Core: ./Core/src/World/Entities/CollectibleItem.cpp ./Core/src/Scripting/v8helpers.cpp ./Core/src/Scripting/ScriptManager.cpp ./Core/src/Replays/ReplaySystem.cpp ./Core/src/Events/EventManager.cpp ./Core/src/World/Entities/Projectile.cpp ./Core/src/World/Entities/SpawnPoints.cpp 	./Core/src/Physics/PhysicsEngine.cpp 	./Core/src/Rendering/RenderingEngine.cpp 	./Core/src/Rendering/WindowMgr.cpp 	./Core/src/Time/Timeline.cpp 	./Core/src/Networking/NetworkMgr.cpp	Core/src/Networking/Topologies/Cliserver	Core/src/Networking/Topologies/P2P/P2P.cpp ./Core/src/Networking/Topologies/P2P/Peer.cpp	Core/src/Networking/Topologies/Cliserver/Client.cpp	Core/src/Networking/Topologies/Cliserver/Server.cpp	./Core/src/Networking/Messages.cpp	./Core/src/Networking/MessageProcessor.cpp 	./Core/src/Time/TimeKeeper.cpp 	./Core/src/World/ScoringSystem.cpp 	./Core/src/Collisions/Solver.cpp 	./Core/src/Input/InputSystem.cpp 	./Core/src/World/ComponentFactory.cpp 	./Core/src/Collisions/CollisionSystem.cpp 	./Core/src/World/Entities/SideBoundary.cpp 	./Core/src/World/Entities/DeathZone.cpp 	./Core/src/World/Entities/Platforms.cpp 	./Core/src/World/Entities/Character.cpp 	./Core/src/World/Components.cpp 	./Core/src/World/World.cpp 	./Core/src/Utils/Utils.cpp 	./Core/src/Input/Keyboard.cpp 	./Core/src/Engine.cpp
	g++ $(STANDARD) -c ./Core/src/World/Entities/CollectibleItem.cpp -o ./build/CollectibleItem.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Scripting/v8helpers.cpp -o ./build/v8helpers.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Scripting/ScriptManager.cpp -o ./build/ScriptManager.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Replays/ReplaySystem.cpp -o ./build/ReplaySystem.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Events/EventManager.cpp -o ./build/EventManager.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/SpawnPoints.cpp -o ./build/SpawnPoints.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Physics/PhysicsEngine.cpp -o ./build/PhysicsEngine.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Rendering/RenderingEngine.cpp -o ./build/RenderingEngine.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Rendering/WindowMgr.cpp -o ./build/WindowMgr.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Time/Timeline.cpp -o ./build/Timeline.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/MessageProcessor.cpp -o ./build/MessageProcessor.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/Topologies/Cliserver/Client.cpp -o ./build/Client.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/Topologies/Cliserver/Server.cpp -o ./build/Server.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/Messages.cpp -o ./build/Messages.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/NetworkMgr.cpp -o ./build/NetworkMgr.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/Topologies/Cliserver/CliServerTopology.cpp -o ./build/CliServerTopology.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/Topologies/P2P/P2P.cpp -o ./build/P2P.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Networking/Topologies/P2P/Peer.cpp -o ./build/Peer.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Time/TimeKeeper.cpp -o ./build/TimeKeeper.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/ScoringSystem.cpp -o ./build/ScoringSystem.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Collisions/Solver.cpp -o ./build/Solver.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Input/InputSystem.cpp -o ./build/InputSystem.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/ComponentFactory.cpp -o ./build/ComponentFactory.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Collisions/CollisionSystem.cpp -o ./build/CollisionSystem.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/SideBoundary.cpp -o ./build/SideBoundary.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/DeathZone.cpp -o ./build/DeathZone.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/Projectile.cpp -o ./build/Projectile.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/Platforms.cpp -o ./build/Platforms.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/Character.cpp -o ./build/Character.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Components.cpp -o ./build/Components.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/World.cpp -o ./build/World.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Utils/Utils.cpp -o ./build/Utils.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Input/Keyboard.cpp -o ./build/Keyboard.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Engine.cpp -o ./build/Engine.o $(INCLUDE)



clean:
	rm ./build/* ./game ./SpaceJumpServer ./SpaceJump ./gamepeer ./TreasureHunt ./TreasureHuntServer ./GrandMotoTorque ./GrandMotoTorqueServer