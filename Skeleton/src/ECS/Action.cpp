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

        // Si la acción no se ha completado, tiene que seguir a pesar de las prioridades actuales
        // Si las condiciones no se cumplen, no se ejecutará esta acción
        float Action::getPriority() const noexcept { return actionComplete ? LONG_MIN : conditionsFulfilled() ? priority : LONG_MAX; }

        // Para incrementar la prioridad, hay que pasar valores negativos
        void Action::addPriority(float increase) { priority += increase;}

        void Action::setPriority(float priority_) {
            priority = priority_;
        }

        MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0) { increasePrioOverTime = 1.0; }

        void MeleeAttack::onActionStart() { std::cout << "\n\n\n\n\n\n\nAttacking at melee\n\n\n\n\n\n\n\n"; setPriority(10.0); }

        Idle::Idle(Agent* agent_) : Action(agent_, 8.0) { actionComplete = true; }

        void Idle::activeUpdate() { std::cout << "Idle\n"; }
    }
}
