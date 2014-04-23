#pragma once

class MovingObject;
class Game{
	Game();
	Game(const Game&);
	Game& operator=(const Game&);

	static Game* instance;

	bool running;
	MovingObject* testObject;
public:
	~Game();

	static Game* GetInstance();
	static Game& GetReference();

	void Initialize();
	void Shutdown();
	void DeleteInstance();
	void Stop() {running = false;}
	bool Run();

	void Update(float dt);
	void Input();
	
};