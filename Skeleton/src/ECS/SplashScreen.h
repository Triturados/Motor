#pragma once
#include <Component.h>
namespace LoveEngine {

	namespace ECS {
		class Image;
		class Scene;
	}

	class FillIcon : public ECS::Component {
	private:
		ECS::Image* img;
		float speed;
		float ypos;
	public:
		void init() override;
		void update() override;
		void receiveMessage(Utilities::StringFormatter& sf) override;
	};

	namespace SceneManagement {
		void populateSplashScreen(ECS::Scene*);
	}
}