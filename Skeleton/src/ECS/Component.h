#pragma once
#include <vector>
#include <string>
class Scene;
class GameObject;
using Key = char;

using uint = unsigned int;

// Componente interfaz, utilizada para listas polimï¿½rficas
class Component {
	friend GameObject;

public:
	// Indica el nï¿½mero de subclases de componente que existen. Necesario para calcular IDs.
	static uint numOfComponentClasses;

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


/// <summary>
/// Calcula el nï¿½mero de componente que le corresponde a una clase concreta de ComponentTemplate.
/// El nï¿½mero no tiene por quï¿½ ser el mismo en diferentes compilaciones, pero dentro de una misma ejecuciï¿½n
/// siempre serï¿½ el mismo para todas las instancias de esa clase.
/// El nï¿½mero de componente solo tiene valor para generar la id, por lo que no tiene getter pï¿½blico.
/// </summary>
template<typename T>
inline static auto calculateComponentNum() {
	static auto componentNum = Component::numOfComponentClasses++;;
	return componentNum;
}

template <class T>
class ComponentTemplate : public Component
{
private:
	static uint componentNum;
};



