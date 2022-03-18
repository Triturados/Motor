#include <iostream>
#include <memory> // For unique_ptr.

/// <summary>
/// Clase Singleton que utiliza smart pointers
/// </summary>


class Singleton {
public:

    /// <summary>
    /// Metodo para inicializar el singleton. Debe llamarse antes de los demas
    /// </summary>
    static bool init() {
        if (instance == nullptr) {
            std::cout << "Creando instancia en Init\n";
            instance.reset(new Singleton()); // Create new instance, assign to unique_ptr.
            return true;
        }
        else return false;
    }

    /// <summary>
    /// Referencia a la clase
    /// </summary>
    static Singleton& getInstance()
    {
        //se debe controlar la correcta inicializacion de la instancia desde fuera
        return *instance;
    }

    /// <summary>
    /// Destruye la instancia (si existe)
    /// </summary>
    static bool destroy()
    {
        if (instance != nullptr) {
            std::cout << "Destroying instance.\n";
            instance.reset(nullptr); // Replaces stored pointer with nullptr, calls deleter on pointed-to instance.
            return true;
        }
        else return false;
    }

    /// <summary>
    /// Destructora vacia
    /// </summary>
    ~Singleton()
    {
        std::cout << "Destructor llamado.\n";
        if (instance == nullptr) {
            std::cout << "* Instancia previamente borrada! No hago nada\n";
        }
    }
private:
    /// <summary>
    /// Constructora vacia
    /// </summary>
    Singleton() { }

    /// <summary>
    /// Metodo personalizado para la destructora. No es necesario
    /// </summary>
    static void destroy(Singleton* instance) {
        if (instance != nullptr) {
            std::cout << "Borrando...\n";
            delete instance;
            instance = nullptr;
        }
    }

    // Con destructora personalizada...
    //static std::unique_ptr<Singleton, decltype(&Singleton::destroy)> instance;

    // De forma normal
    static std::unique_ptr<Singleton> instance;
};

// Inicializar variables estaticas en el cpp
//std::unique_ptr<Singleton, decltype(&Singleton::destroy)> Singleton::instance = {nullptr, &Singleton::destroy};
//std::unique_ptr<Singleton> Singleton::instance = nullptr;

