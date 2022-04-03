#include "Action.h"
#include "Agent.h"
#include <iostream>
#include "GameTime.h"


namespace LoveEngine {
	namespace ECS {
        Action::Action(Agent* agent_, float priority_)
        {
            agent = agent_;
            agent->addAction(this);
            priority = priority;
        }

        void Action::passiveUpdate()
        {
            addPriority(-increasePrioOverTime * LoveEngine::Time::getInstance()->deltaTime);
        }

        // Si la acci�n no se ha completado, tiene que seguir a pesar de las prioridades actuales
        // Si las condiciones no se cumplen, no se ejecutar� esta acci�n
        float Action::getPriority() const noexcept { return actionComplete ? LONG_MIN : conditionsFulfilled() ? priority : LONG_MAX; }

        // Para incrementar la prioridad, hay que pasar valores negativos
        void Action::addPriority(float increase) { priority += increase;}

        void Action::setPriority(float priority_) {
            priority = priority_;
        }

    }
}
