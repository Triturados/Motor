#pragma once

#include <climits>
#include <../Export.h>

namespace LoveEngine {
	namespace ECS {
        class Agent;
        class Action
        {
        public:
            // Cantidad de prioridad que se incrementa cada frame
            float increasePrioOverTime = 0.0;

            // Avisa al agente de cu�ndo se PUEDE tomar otra acci�n
            bool actionComplete = false;

            // Condiciones que se tienen que cumplir para que la acci�n se realice, ignorando prioridad
            // Por ejemplo un ataque mel� puede requerir una m�nima proximidad al objetivo
            virtual bool conditionsFulfilled() const { return true; };

            virtual void onActionStart() {};

            Action(Agent* agent_, float priority_ = LONG_MAX);

            // llamado en cada frame, est� o no activa la acci�n (necesario para control de prioridad etc.)
            virtual void passiveUpdate();

            // llamado en cada frame mientras se est� ejecutando la acci�n
            virtual void activeUpdate() {};

            // Si la acci�n no se ha completado, tiene que seguir a pesar de las prioridades actuales
            // Si las condiciones no se cumplen, no se ejecutar� esta acci�n
            float getPriority() const noexcept;
        protected:
            Agent* agent;

            // Para incrementar la prioridad, hay que pasar valores negativos
            virtual void addPriority(float increase);
            virtual void setPriority(float priority_);
        private:
            float priority;
        };

	}
}
