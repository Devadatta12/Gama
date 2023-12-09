uname_s := $(shell uname -s)
INCLUDE =
LINKER =
STANDARD =
ifeq ($(uname_s),Darwin)
	INCLUDE = -I/opt/homebrew/Cellar/sfml/2.6.0/include -I/opt/homebrew/Cellar/cppzmq/4.10.0/include -I/opt/homebrew/Cellar/zeromq/4.3.4/include -I./include
	LINKER = -L/opt/homebrew/Cellar/sfml/2.6.0/lib -L/opt/homebrew/Cellar/cppzmq/4.10.0/lib -L/opt/homebrew/Cellar/zeromq/4.3.4/lib
	STANDARD = -std=c++11
else ifeq ($(uname_s),Linux)
	INCLUDE = -I/usr/include -I./include
	LINKER = -L/usr/lib/aarch64-linux-gnu -pthread
	STANDARD = -std=c++11
endif

all: game gamecli gameserver gamepeer

game: ./build/Game.o Core
	g++ ./build/Game.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o game $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system
	chmod +x ./game

gamepeer: ./build/GamePeer.o Core
	 g++ ./build/GamePeer.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o gamepeer $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system
	chmod +x ./gamepeer

gamecli: ./build/GameClient.o Core
	g++ ./build/ReplaySystem.o ./build/GameClient.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o gamecli $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system
	chmod +x ./gamecli

gameserver: ./build/GameServer.o Core
	g++ ./build/GameServer.o ./build/EventManager.o ./build/SpawnPoints.o ./build/PhysicsEngine.o ./build/RenderingEngine.o ./build/WindowMgr.o ./build/Timeline.o ./build/NetworkMgr.o ./build/CliServerTopology.o ./build/P2P.o ./build/Peer.o ./build/Client.o ./build/Server.o ./build/Messages.o ./build/MessageProcessor.o ./build/TimeKeeper.o ./build/ScoringSystem.o ./build/Solver.o ./build/InputSystem.o ./build/ComponentFactory.o ./build/CollisionSystem.o ./build/SideBoundary.o ./build/DeathZone.o ./build/Platforms.o ./build/Character.o ./build/Components.o ./build/World.o ./build/Utils.o ./build/Keyboard.o ./build/Engine.o -o gameserver $(LINKER) -lzmq -lsfml-graphics -lsfml-window -lsfml-system
	chmod +x ./gameserver

./build/Game.o: ./Core/src/Game.cpp
	g++ $(STANDARD) -c ./Core/src/Game.cpp -o ./build/Game.o $(INCLUDE)

./build/GamePeer.o:./Core/src/Multiplayer/GamePeer.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/GamePeer.cpp -o ./build/GamePeer.o $(INCLUDE)

./build/GameClient.o: ./Core/src/Multiplayer/GameClient.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/GameClient.cpp -o ./build/GameClient.o $(INCLUDE)

./build/GameServer.o: ./Core/src/Multiplayer/GameServer.cpp
	g++ $(STANDARD) -c ./Core/src/Multiplayer/GameServer.cpp -o ./build/GameServer.o $(INCLUDE)

Core: ./Core/src/Replays/ReplaySystem.cpp ./Core/src/Events/EventManager.cpp ./Core/src/World/Entities/SpawnPoints.cpp 	./Core/src/Physics/PhysicsEngine.cpp 	./Core/src/Rendering/RenderingEngine.cpp 	./Core/src/Rendering/WindowMgr.cpp 	./Core/src/Time/Timeline.cpp 	./Core/src/Networking/NetworkMgr.cpp	Core/src/Networking/Topologies/Cliserver	Core/src/Networking/Topologies/P2P/P2P.cpp ./Core/src/Networking/Topologies/P2P/Peer.cpp	Core/src/Networking/Topologies/Cliserver/Client.cpp	Core/src/Networking/Topologies/Cliserver/Server.cpp	./Core/src/Networking/Messages.cpp	./Core/src/Networking/MessageProcessor.cpp 	./Core/src/Time/TimeKeeper.cpp 	./Core/src/World/ScoringSystem.cpp 	./Core/src/Collisions/Solver.cpp 	./Core/src/Input/InputSystem.cpp 	./Core/src/World/ComponentFactory.cpp 	./Core/src/Collisions/CollisionSystem.cpp 	./Core/src/World/Entities/SideBoundary.cpp 	./Core/src/World/Entities/DeathZone.cpp 	./Core/src/World/Entities/Platforms.cpp 	./Core/src/World/Entities/Character.cpp 	./Core/src/World/Components.cpp 	./Core/src/World/World.cpp 	./Core/src/Utils/Utils.cpp 	./Core/src/Input/Keyboard.cpp 	./Core/src/Engine.cpp
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
	g++ $(STANDARD) -c ./Core/src/World/Entities/Platforms.cpp -o ./build/Platforms.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Entities/Character.cpp -o ./build/Character.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/Components.cpp -o ./build/Components.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/World/World.cpp -o ./build/World.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Utils/Utils.cpp -o ./build/Utils.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Input/Keyboard.cpp -o ./build/Keyboard.o $(INCLUDE)
	g++ $(STANDARD) -c ./Core/src/Engine.cpp -o ./build/Engine.o $(INCLUDE)



clean:
	rm ./build/* ./game ./gameserver ./gamecli ./gamepeer