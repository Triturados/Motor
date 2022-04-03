#pragma once

#include "Component.h"
#include <../Export.h>
#include <queue>

namespace LoveEngine {
	namespace ECS {
        class Action;
		class lovexport Agent : public Component
		{
        public:
            Agent();

            ~Agent();

            void init() override {};

            void update() override;

            Action* addAction(Action* a);

        private:
            // vector iterable de acciones, para llamar los updates
            std::vector<Action*> actions;

            // la acción que se está realizando actualmente
            Action* currentAction;

            Action* getNextAction();
		};
	}
}
