#include "Action.h"
#include "Agent.h"
#include <iostream>
#include "GameTime.h"

// TO DO: remove these includes
#include "RigidBody.h"
#include "Transform.h"
#include "GameObject.h"
#include "Vector3.h"

namespace LoveEngine {
	namespace ECS {
        Action::Action(Agent* agent_, float priority_)
        {
            agent = agent_;
            agent->addAction(this);
            priority = priority;
        }

        // Si la acción no se ha completado, tiene que seguir a pesar de las prioridades actuales
        // Si las condiciones no se cumplen, no se ejecutará esta acción
        float Action::getPriority() const noexcept { return lockAction ? LONG_MIN : conditionsFulfilled() ? priority : LONG_MAX; }

        // Para incrementar la prioridad, hay que pasar valores negativos
        void Action::addPriority(float increase) { priority += increase;}

        void Action::setPriority(float priority_) {
            priority = priority_;
        }
        void Action::passiveUpdateAndPrio()
        {
            passiveUpdate();
            addPriority(-increasePrioOverTime * LoveEngine::Time::getInstance()->deltaTime);
        }
#pragma region ExampleActions

        MeleeAttack::MeleeAttack(Agent* agent_) : Action(agent_, 10.0) { increasePrioOverTime = 10.0; };

        void MeleeAttack::setTarget(Transform* t)
        {
            target = t;
        }

        bool MeleeAttack::conditionsFulfilled() const
        {
            if (target == nullptr) return true;
            return (*(target->getPos()) - *(tr->getPos())).magnitude() < 10;
        }

        void MeleeAttack::onActionStart() 
        { 
            //start animation
            std::cout << "\n\n\n\n\n\n\nAttacking at melee\n\n\n\n\n\n\n\n"; 
            setPriority(30.0);
        }

        void MeleeAttack::activeUpdate()
        {
            //lookat target
        }

        Idle::Idle(Agent* agent_) : Action(agent_, 8.0) {}

        void Idle::activeUpdate() { std::cout << "Idle\n"; }

        Chase::Chase(Agent* agent_) : Action(agent_, 0.0) { };

        void Chase::setTarget(Transform* t)
        {
            target = t;
        }

        void Chase::activeUpdate()
        {
            if ((*(rb->getVelocity())).magnitude() < maxVel)
            {
                Utilities::Vector3<float> targetPos = *(target->getPos());
                Utilities::Vector3<float> pos = *(tr->getPos());
                
                rb->addForce((targetPos - pos).getNormalized() * acc * rb->getMass(), Utilities::Vector3<float>(0, 0, 0), (int)ForceMode::ACCELERATION);
                //lookat target
            }
        }

        Leap::Leap(Agent* agent_) : Action(agent)
        {
            rb = agent->gameObject->getComponent<RigidBody>();
            tr = agent->gameObject->getComponent<Transform>();
            increasePrioOverTime = 10;
        }

        void Leap::setTarget(Transform* t)
        {
            target = t;
        }

        bool Leap::conditionsFulfilled() const
        {
            return (*(target->getPos()) - *(tr->getPos())).magnitude() > 40;
        }

        void Leap::onActionStart()
        {
            if (target == nullptr) return;
            
            //start animation
            rb->addForce(*(target->getPos()) - *(tr->getPos()) + Utilities::Vector3<float>(0, 10, 0), Utilities::Vector3<float>(0, 0, 0), (int)ForceMode::IMPULSE);
        }

        void Leap::activeUpdate()
        {
            if (rb->getVelocity()->y > 0 && rb->getVelocity()->y < 0.02)
                setPriority(80);
                //end animation
        }

#pragma endregion
    }
}
