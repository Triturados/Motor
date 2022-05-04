#include "Agent.h"
#include "GameTime.h"

namespace LoveEngine {
	namespace ECS {
        Agent::Agent()
        {
            actions = std::vector<Action*>();
        }

        Agent::~Agent()
        {
            for (Action* a : actions)
                delete a;
        }

        void Agent::init()
        {
            getNextAction();
            if (currentAction == nullptr)
                throw new std::exception("Agente sin acciones");
        }

        void Agent::update()
        {
            currentAction->activeUpdate();

            for (Action* a : actions)
                a->passiveUpdateAndPrio();

            if (!currentAction->lockAction)
            {
                getNextAction();
                currentAction->onActionStart();
            }
        }

        Agent::Action* Agent::addAction(Action* a)
        {
            actions.push_back(a);
            return a;
        }

        Agent::Action* Agent::getNextAction()
        {
            float highestPrio = LONG_MAX;
            
            for (Action* a : actions)
            {
                if (a->getPriority() < highestPrio)
                {
                    currentAction = a;
                    highestPrio = a->getPriority();
                }
            }
            return currentAction;
        }
#pragma region Action
        Agent::Action::Action(Agent* agent_, float priority_)
        {
            agent = agent_;
            priority = priority_;
        }

        // Si la acción no se ha completado, tiene que seguir a pesar de las prioridades actuales
        // Si las condiciones no se cumplen, no se ejecutará esta acción
        float Agent::Action::getPriority() const noexcept { return lockAction ? LONG_MIN : conditionsFulfilled() ? priority : LONG_MAX; }

        // Para incrementar la prioridad, hay que pasar valores negativos
        void Agent::Action::addPriority(float increase) { priority += increase; }

        void Agent::Action::setPriority(float priority_) {
            priority = priority_;
        }
        void Agent::Action::passiveUpdateAndPrio()
        {
            passiveUpdate();
            addPriority(-increasePrioOverTime * LoveEngine::Time::getInstance()->deltaTime);
        }
#pragma endregion
    }
}
