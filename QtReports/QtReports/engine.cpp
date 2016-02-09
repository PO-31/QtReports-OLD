#include "engine.hpp"

namespace qtreports {

	Engine::Engine(QObject * parent) : QObject(parent) {

	}

	Engine::~Engine() {

	}

	bool	Engine::compile( std::string path ) {
		return false;
	}

	WidgetPtr	Engine::getWidget() {
		return WidgetPtr();
	}

}