
#include "stdafx.h"
#include "Headers/Game.h"
#include "Headers/Renderer.h"
#include "Headers/MovingObject.h"

Game* Game::instance = nullptr;

Game::Game(void)
{
}


Game::~Game(void)
{
}

Game* Game::GetInstance()
{
	if(instance == nullptr)
		instance = new Game;
	return instance;
}

Game& Game::GetReference()
{
	if(instance == nullptr)
		instance = new Game;
	return *instance;
}

void Game::DeleteInstance(){
	if(instance)
		delete instance;
}

void Game::Initialize()
{
	running = true;
	Renderer::GetInstance()->Initialize();
	testObject = new MovingObject;
}

void Game::Shutdown()
{
	running = false;
	delete testObject;
}

bool Game::Run()
{
	Input();
	Renderer::GetInstance()->Render();
	Renderer::GetInstance()->Draw(Renderer::Entities::PLAYER,testObject->GetPosX(),testObject->GetPosY());
	return running;
}

void Game::Update(float dt)
{
	testObject->Update(dt);
}

void Game::Input()
{
	testObject->Input();
	//Will handle menus / pausing / GAME related inputs
	if(GetAsyncKeyState(VK_ESCAPE))
		running = false;
}

