#pragma once
#include "Commons.h"

class GameObject
{
public:
	//error prone
	virtual SDL_FRect getTransform();
	virtual void setTransform();
	virtual std::string getTag();
	virtual void LoadMedia(SDL_Renderer* renderer);
	virtual void Start();
	virtual void HandleEvent(SDL_Event& event);
	virtual void Update(float deltaTime);
	virtual void Render(SDL_Renderer* renderer);

	virtual bool CheckForCollision(const SDL_FRect &other);
	virtual void OnCollision(GameObject &other, float deltaTime);

	/*Return true if object should be destryoed*/
	virtual bool ToDestroy(); 
	/*Set an object to be destroy before the next Update*/
	virtual void Destroy(); 

private:
	bool toDestroy = false;
};
