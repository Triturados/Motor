#pragma once
#include <vector>
#include <string>
class Scene;
class GameObject;
using Key = char;

// Componente interfaz, utilizada para listas polim�rficas
class Component {
	friend GameObject;

public:
	// Indica el n�mero de subclases de componente que existen. Necesario para calcular IDs.
	static unsigned int numOfComponentClasses;

	Component();

	GameObject* gameObject;
protected:

	// Puntero a escena
	Scene* scene;
	
	/// Componentes desactivados no son actualizados autom�ticamente por el motor, 
	/// pero otras componentes pueden llamar a sus m�todos.
	bool enabled = true;

	/// Lista de componentes de las que depende esta componente. Si se intenta a�adir esta componente
	/// a un objeto que no tiene todas sus dependencias, se escribe un mensaje de error y no se a�ande.
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
/// Calcula el n�mero de componente que le corresponde a una clase concreta de ComponentTemplate.
/// El n�mero no tiene por qu� ser el mismo en diferentes compilaciones, pero dentro de una misma ejecuci�n
/// siempre ser� el mismo para todas las instancias de esa clase.
/// El n�mero de componente solo tiene valor para generar la id, por lo que no tiene getter p�blico.
/// 
/// Al ser un template, se compila una versi�n de esta funci�n por cada tipo que lo llame.
/// </summary>
template<typename T>
inline static auto calculateComponentNum() {
	static auto componentNum = Component::numOfComponentClasses++;;
	return componentNum;
}


// Todas las clases Componentes deben heredar de esta clase, para que puedan tener IDs.
// Esta clase usa herencia inversa (Curiously Recurring Template Pattern), por lo que las clases que heredan
// de ella deben estar declaradas as�:
// class NombreClase: public ComponentTemplate<NombreClase>
template <class T>
class ComponentTemplate : public Component
{
private:
	static uint componentNum;
	static size_t id;

	void generateComponentID();
public:
	inline size_t getId() const { return id; };
};

// Las ids se usan para comparar componentes y organizarlas en listas ordenadas
template<class T>
inline void ComponentTemplate<T>::generateComponentID()
{
	componentNum = calculateComponentNum<T>();
	std::hash<ComponentTemplate<T>> myComponentHash;
	ComponentTemplate<T>::id = myComponentHash(componentNum);
}

// Un hash genera un n�mero muy grande determinista a partir de un valor
template<class T>
struct std::hash<ComponentTemplate<T>>
{
	std::size_t operator()(unsigned int num) const noexcept;
};