#pragma once

#include <Component.h>
#include <functional>


class Timer : public Component {
	using action = std::function<void(Timer* t)>;
private:
	float maxTime = 0;
	float currentTime = 0;
	bool _loop = false;
	action funct;

	void onTimeUp();

	Component* componentToDelete;
	GameObject* objectToDelete;

public:
	void setValue(action f, float t);
	void update() override;
	void stop();
	void restart();
	void pause();
	void resume();
	void loop();
	void noloop();

	float timeLeft();


	static Timer* invoke(action funct, float time);
	static Timer* repeat(action funct, float initialcall, float interval);
	static Timer* deleteGameObject(GameObject* gameObject, float time);
	static Timer* deleteComponent(Component* component, float time);

private:
	static Timer* createObjectWithTimer();

};