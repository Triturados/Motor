#include "Agent.h"
#include "GameTime.h"

// TO DO: remove these includes
#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"
#include <iostream>

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
            actions.push_back(new Idle(this));
            actions.push_back(new MeleeAttack(this));
            actions.push_back(new Leap(this));
            getNextAction();
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
            priority = priority;
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

#pragma region Move these to game
        Agent::MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0)
        {
            rb = agent->gameObject->getComponent<RigidBody>();
            tr = agent->gameObject->getComponent<Transform>();
            increasePrioOverTime = 10.0;
        };

        void Agent::MeleeAttack::setTarget(Transform* t)
        {
            target = t;
        }

        bool Agent::MeleeAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return true; // TO DO: Change true to false
            return (*(target->getPos()) - *(tr->getPos())).magnitude() < 10;
        }

        void Agent::MeleeAttack::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nAttacking at melee\n\n\n\n\n\n\n\n";
            setPriority(30.0);
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                //throw new std::exception("Faltan referencias para una acción");
                return;
            }
            // TO DO: start animation
        }

        void Agent::MeleeAttack::activeUpdate()
        {
            // TO DO: lookat target
        }

        Agent::Idle::Idle(Agent* agent_) : Action(agent_, 8.0) {}

        void Agent::Idle::activeUpdate() { std::cout << "Idle\n"; }

        Agent::Chase::Chase(Agent* agent_) : Action(agent_, 0.0) { };

        void Agent::Chase::setTarget(Transform* t)
        {
            target = t;
        }

        void Agent::Chase::activeUpdate()
        {
            if ((*(rb->getVelocity())).magnitude() < maxVel)
            {
                Utilities::Vector3<float> targetPos = *(target->getPos());
                Utilities::Vector3<float> pos = *(tr->getPos());

                rb->addForce((targetPos - pos).getNormalized() * acc * rb->getMass(), Utilities::Vector3<float>(0, 0, 0), (int)ForceMode::ACCELERATION);
                //lookat target
            }
        }

        Agent::Leap::Leap(Agent* agent_) : Action(agent_, 80)
        {
            rb = agent->gameObject->getComponent<RigidBody>();
            tr = agent->gameObject->getComponent<Transform>();
            increasePrioOverTime = 10;
        }

        void Agent::Leap::setTarget(Transform* t)
        {
            target = t;
        }

        bool Agent::Leap::conditionsFulfilled() const
        {
            if (target == nullptr) return true; // TO DO: Change true to false
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > 40;
        }

        void Agent::Leap::onActionStart()
        {
            std::cout << "\n\n\n\n\n\n\nLeaping\n\n\n\n\n\n\n\n";
            if (target == nullptr || rb == nullptr || tr == nullptr)
            {
                //throw new std::exception("Faltan referencias para una acción");
                return;
            }

            //start animation
            rb->addForce(*(target->getPos()) - *(tr->getPos()) + Utilities::Vector3<float>(0, 10, 0), Utilities::Vector3<float>(0, 0, 0), (int)ForceMode::IMPULSE);
        }

        void Agent::Leap::activeUpdate()
        {
            setPriority(80);
            if (target == nullptr || rb == nullptr || tr == nullptr) return;
            // TO DO: remove these lines ^^^^
            if (rb->getVelocity()->y > 0 && rb->getVelocity()->y < 0.02)
                setPriority(80);
            //end animation
        }
#pragma endregion
    }
}
