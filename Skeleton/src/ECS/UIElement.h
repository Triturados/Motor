#pragma once
#include <../Export.h>
#include <Component.h>
#include <Vector3.h>
#include <Vector2.h>

namespace LoveEngine {

	namespace ECS {

		class UIContainer;
		class lovexport UIElement : public Component {

		protected:

			Utilities::Vector3<int> position;
			Utilities::Vector2<int> dimensions;

			virtual void onResize() {};
			virtual void onMove() {};

			UIContainer* container;
		public:

			UIElement();
			~UIElement();
			Utilities::Vector2<int> getSize();
			void setSize(Utilities::Vector2<int>);


			Utilities::Vector3<int> getPosition();
			void setPosition(Utilities::Vector3<int>);

			void receiveMessage(Utilities::StringFormatter& sf);

			UIContainer* getContainer();
		};

	}

}