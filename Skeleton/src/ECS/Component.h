#pragma once
#include <vector>
#include <string>
class Scene;
class GameObject;
using Key = char;


class Component {
	friend GameObject;

public:
	Component();

	GameObject* gameObject;
protected:

	// Puntero a escena
	Scene* scene;
	
	/// Componentes desactivados no son actualizados automáticamente por el motor, 
	/// pero otras componentes pueden llamar a sus métodos.
	bool enabled = true;

	/// Lista de componentes de las que depende esta componente. Si se intenta añadir esta componente
	/// a un objeto que no tiene todas sus dependencias, se escribe un mensaje de error y no se añande.
	std::vector<Component*> dependencies;

public:
	void print(std::string mssg, int line = -1, const char* file = "");
protected:

	virtual void init() {};
	virtual void postInit() {};

	virtual void update() {};
	virtual void stepPhysics() {};
	virtual void preRender() {};

	virtual void activated() {};
	virtual void deActivated() {};

#pragma region Input Callbacks

	void keyListener(Key keys[]);
	void clickListener(int mouseButtons[]);
	void mouseMovementListener();

	virtual void keyPressed(Key key) {};
	virtual void keyDown(Key key) {};
	virtual void keyUp(Key key) {};

	virtual void clickPressed(int button) {};
	virtual void clickUp(int button) {};
	virtual void clickDown(int button) {};

	virtual void onMouseMoved(int mx, int my, int x, int y) {};

#pragma endregion 

#pragma region Physics Callbacks

	virtual void colliding() {};
	virtual void enterCollision() {};
	virtual void exitCollision() {};

#pragma endregion Physics Callbacks

public:
	void setActive(bool val);
	void invertActive();

	void remove(Component*);
	void remove(GameObject*);


private:

	std::vector<GameObject*> collisions;
	void checkCollisionCallbacks();


	void DontUpdate();
};




