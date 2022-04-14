#pragma once

#include "Component.h"
#include <../Export.h>
#include <queue>

namespace LoveEngine {
	namespace ECS {
        
        // TO DO: remove these
        class RigidBody;
        class Transform;


		class lovexport Agent : public ComponentTemplate<Agent>
		{

        protected:
#pragma region Action
            class Action
            {
            public:
                friend Agent;
                // Cantidad de prioridad que se incrementa cada frame
                float increasePrioOverTime = 0.0;

                // Avisa al agente de que NO SE PUEDE tomar otra acción
                bool lockAction = false;

                // Condiciones que se tienen que cumplir para que la acción se realice, ignorando prioridad
                // Por ejemplo un ataque melé puede requerir una mínima proximidad al objetivo
                virtual bool conditionsFulfilled() const { return true; };

                virtual void onActionStart() {};

                Action(Agent* agent_, float priority_ = LONG_MAX);

                // llamado en cada frame, esté o no activa la acción (necesario para control de prioridad etc.)
                virtual void passiveUpdate() {};

                // llamado en cada frame mientras se esté ejecutando la acción
                virtual void activeUpdate() {};

                // Si la acción no se ha completado, tiene que seguir a pesar de las prioridades actuales
                // Si las condiciones no se cumplen, no se ejecutará esta acción
                float getPriority() const noexcept;
            protected:
                Agent* agent;

                // Para incrementar la prioridad, hay que pasar valores negativos
                virtual void addPriority(float increase);
                virtual void setPriority(float priority_);
            private:
                float priority;
                // Este método es privado para evitar que sobrecargar el passiveUpdate requiera actualizar la prioridad
                void passiveUpdateAndPrio();
            };
#pragma endregion

#pragma region move these to game
            class MeleeAttack : public Action
            {
            public:
                MeleeAttack(Agent* agent_);
                void setTarget(Transform* t);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void activeUpdate() final;
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
            };

            class Idle : public Action
            {
            public:
                Idle(Agent* agent_);
                void activeUpdate() final;
            };

            class Chase : public Action
            {
            public:
                Chase(Agent* agent_);
                void setTarget(Transform* t);
                void activeUpdate() final;
            protected:
                float maxVel = 10;
                float acc = 10;
                RigidBody* rb = nullptr;
                Transform* target = nullptr;
                Transform* tr = nullptr;
            };

            class Leap : public Action
            {
            public:
                Leap(Agent* agent_);
                void setTarget(Transform* t);
                bool conditionsFulfilled() const final;
                void onActionStart() final;
                void activeUpdate() final;
            protected:
                RigidBody* rb;
                Transform* target = nullptr;
                Transform* tr = nullptr;
            };
#pragma endregion
        public:
            Agent();

            ~Agent();

            void init() override;

            void update() override;

            Action* addAction(Action* a);

        private:
            // vector iterable de acciones, para llamar los updates
            std::vector<Action*> actions;

            // la acción que se está realizando actualmente
            Action* currentAction = nullptr;

            Action* getNextAction();
		};
	}
}
