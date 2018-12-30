#include "RenderBox.h"

class Game : public Rb::Application {
public:	
	Game() {

	}

	~Game() {

	}
};

Rb::Application* Rb::CreateApplication() {
	return new Game();
}

