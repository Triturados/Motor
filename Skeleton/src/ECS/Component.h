#pragma once
#include <vector>
#include <string>
class Scene;
class GameObject;
using Key = char;

// Componente interfaz, utilizada para listas polimórficas
class Component {
	friend GameObject;

public:
	// Indica el número de subclases de componente que existen. Necesario para calcular IDs.
	static unsigned int numOfComponentClasses;

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
/// Calcula el número de componente que le corresponde a una clase concreta de ComponentTemplate.
/// El número no tiene por qué ser el mismo en diferentes compilaciones, pero dentro de una misma ejecución
/// siempre será el mismo para todas las instancias de esa clase.
/// El número de componente solo tiene valor para generar la id, por lo que no tiene getter público.
/// 
/// Al ser un template, se compila una versión de esta función por cada tipo que lo llame.
/// </summary>
template<typename T>
inline static auto calculateComponentNum() {
	static auto componentNum = Component::numOfComponentClasses++;;
	return componentNum;
}


// Todas las clases Componentes deben heredar de esta clase, para que puedan tener IDs.
// Esta clase usa herencia inversa (Curiously Recurring Template Pattern), por lo que las clases que heredan
// de ella deben estar declaradas así:
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

// Un hash genera un número muy grande determinista a partir de un valor
template<class T>
struct std::hash<ComponentTemplate<T>>
{
	std::size_t operator()(unsigned int num) const noexcept;
};