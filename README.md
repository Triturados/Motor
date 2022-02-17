# Motor
El código de todo el proyecto estará dividido en dos soluciones. Una solución contará con la implementación del motor, y en la otra estará el código completo del juego.
En este repositorio estará subida la solución del motor **'Grind'**. 

# Arquitectura 
El repositorio estará dividio en **siete** soluciones diferentes

| Grind                 |                                                                                                           |
|-----------------------|:---------------------------------------------------------------------------------------------------------:|
|  Proyecto principal   |  Inicialización, bucle principal y enlace con otros proyectos                                             |
|  Físicas              |  Abstracción de bullet physics para implementación de físicas en el motor                                 |
|  Render               |  Abstracción de ogre para renderizado de elementos en 3d, y SDL para el renderizado de elementos en 2D    |
|  Input                |  Manejo de Input usando SDL                                                                               |
|  Sonido               |  Implementación de fmod para sonidos y música                                                             |
|  ECS                  |  Arquitectura basada en componentes y escenas para representar la información dentro del juego            |
|  Utils                |  Elementos de ayuda y herramientas de desarrollo (pe. Time, Gestor de escenas, Math...)                   |

# Inicialización

Desde el proyecto principal se abrirán el resto de librerías dinámicas del juego, seguido de la preparación del entorno e inicialización inicial del juego.
Se ejecuta entonces el bucle principal de juego y cuando este finalice se cierran todos los procesos y se libera la memoria.

# Loop de juego

El bucle de juego se presenta en el siguiente orden:

```
    ->input
    ->update
    ->fisicas
    ->render
    ->sceneManagement

```
El bucle está implementado de tal forma que cada apartado tiene su propia frecuencia de ejecución según una prioridad arbitraria

# ECS

Del patrón ECS (Entity-Component-System) nos quedaremos principalmente solo con la EC, por lo que será una arquitectura pura de componentes.
La información de cada uno de los elementos del juego estará guardada en forma de componente, y una entidad no será más que una capa contenedora que los asocie.
Sólo puede haber un único componente de cada tipo por entidad.

Además de los componentes, una entidad tendrá asociada un valor que indique si está activado, una capa de colisión, y un vector de entidades con las que se ha colisionado para facilitar el uso de callbacks.

Cada componente, podrá sobreescribir los siguientes métodos:

```
init     -> inicialización temprana del componente
postInit -> inicialización tardía del componente

update   -> método que se llama a cada frame
stepPhysics -> método que se llama en cada ejecución del motor físico
preRender -> método que se llama antes de renderizar una escena

activated ( value ) -> método que se llama cuando un componente o entidad se activa o desactiva
setActive ( value ) -> activa o desactiva un componente o entidad

remove -> elimina un componente o entidad (las entidades se eliminan al final del método update)

Callbacks de colisión ( es necesario haberse suscrito)
enterCollision ( collider ) -> se ejecuta al entrar en contacto con un collider
colliding ( collider ) -> se ejecuta al entrar en contacto con un collider
exitCollision ( collider ) -> se ejecuta al entrar en contacto con un collider

Callbacks de input ( es necesario haberse suscrito )
keyPressed ( key ) -> tecla mantenida pulsada
keyDown    ( key ) -> tecla que acaba de ser pulsada
keyUp      ( key ) ->  tecla que ha dejado de ser pulsada
mouseClick     ( value ) -> botón que se ha pulsado del ratón
mouseClickDown ( value ) -> botón que se acaba de pulsar del ratón
mouseClickUp   ( value ) -> botón que se acaba de soltar del ratón

```

Además, existen los siguiente métodos de consulta

```

entity -> entidad asociada al componente
scene -> escena en la que existe la entidad asociada al componente
transform -> componente transform asociado a la entidad ( no todas las entidades tienen transform )
getComponent -> referencia a un componente en concreto de una entidad ( por defecto, la propia entidad )

enabledEntity -> la entidad está activada
enabled -> el componente está activado


```

# Gestor de escenas

Una escena no es más que una colección de **entidades** con funcionalidad añadida, como poder buscar un elemento o ejecutar un método sobre cada entidad.
Las escenas se manejan y se modifican desde el gestor de escenas, donde están almacenadas en una **pila**.
Un gestor de escenas es un singleton desde donde se podrán añadir o quitar escenas.
Además de modificar la cola, se podrá obtener una referencia a la escena actual o saber el número de escenas totales.
El gestor de escena además de la pila de escenas, contiene una escena especial para almacenar elementos que no deberían ser destruidos entre escenas.

Cada una de las escenas del juego está representada por un **entero**.
Un programador que use el motor podrá crear una función initScene(idx). Esta función creará y poblará una escena.

La creación del gestor de escenas se hará durante la fase de inicialización del main.


# Utilidades

Dentro del programa, se podrán usar una serie de clases ( ya bien siendo clases estáticas o singletons) que sirvan para dotar de funcionalidad o utilidad a diversos comportamientos

Dentro de las clases destacables están:

| Clase                 |   Función                                                                                                 |
|-----------------------|:---------------------------------------------------------------------------------------------------------:|
|  Vector2 / Vector3    |  Ampliación de la clase vector de Ogre que sirva como intermediaria entre las librerias, LUA y el motor   |
|  Maths                |  Utilidades de operaciones matemáticas frecuentes, interpolados y operaciones sobre vectores              |
|  Input                |  Control del input del usuario donde poder consular un input en concreto o suscribirse como oyente        |
|  Time                 |  Consulta del tiempo, intervalo entre fotogramas, poder cambiar la escala de tiempo y creación de timers  |
|  SceneManager         |  Manejador de la escena actual del juego                                                                  |
|  ECS                  |  Arquitectura basada en componentes y escenas para representar la información dentro del juego            |
|  Utils                |  Elementos de ayuda y herramientas de desarrollo (pe. Time, Gestor de escenas, Math...)                   |
|  Camera               |  Gestor de cámaras, acceso a cámara principal y operaciones básicas de cámaras ( seguimiento )            |
|  Physics              |  Operaciones físicas, como comprobación de raycasts                                                       |



# Componentes esenciales

A continuación de una lista de componentes esenciales ya definidos por el motor:

| Componentes           |    Breve descripción                                                                                      |
|-----------------------|:---------------------------------------------------------------------------------------------------------:|
|  Transform            |  Posición, rotación y escala de una entidad                                                               |
|  Camera               |  Representación de una cámara                                                                             |
|  MeshContainer        |  Almacenamiento de una malla y el material que tiene asociado. Se encarga de renderizar la entidad        |
|  Collider             |  Puede ser un trigger, y su malla ser un cubo, esfera, o la malla asociada                                |
|  RigidBody            |  Actualización de movimiento físico durante el ciclo de físicas del motor                                 |
|  Agent /AgentBehaviour|  Abtracción para facilitar la implementación de IA para entidades                                         |
|  Gizmos               |  Renderización de elementos de ayuda a la depuración dentro de la escena                                  |
|  Sound                |  Produce un sonido dentro de la escena                                                                    |
|  Image                |  Dibujado de un sprite en 2d para la interfaz del juego                                                   |
|  PostProcess          |  Modifica el resultado de la renderización para añadir efectos visuales antes de dibujar el frame         |