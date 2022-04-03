#include "Agent.h"
#include "Action.h"

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

        void Agent::update()
        {
            currentAction->activeUpdate();

            for (Action* a : actions)
                a->passiveUpdate();

            if (currentAction->actionComplete)
            {
                getNextAction();
                currentAction->onActionStart();
            }
        }

        Action* Agent::addAction(Action* a)
        {
            actions.push_back(a);
            return a;
        }

        Action* Agent::getNextAction()
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
    }
}
