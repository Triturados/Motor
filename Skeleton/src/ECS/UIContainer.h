#pragma once
#include <../Export.h>

#include <UIElement.h>
#include <vector>


namespace LoveEngine {

	namespace ECS {

		class lovexport UIContainer : public UIElement {

		private:
			
			struct UIChild {
				UIElement* element;
				Utilities::Vector3<int> localPosition;
				Utilities::Vector2<int> localDimensions;
			};
			std::vector<UIChild> uiElements;

		protected:

			void onMove() override;
			void onResize() override;


		public:
			void postInit() override;

			void addElement(UIElement* element);

			void receiveComponent(int, Component*) override;
		};

	}

}