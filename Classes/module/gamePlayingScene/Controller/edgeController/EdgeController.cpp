#include"EdgeController.h"

EdgeController* EdgeController::edgeController = NULL;

EdgeController::EdgeController() {}

EdgeController::~EdgeController() {
	if (edgeController != NULL) {
		edgeController->removeFromParentAndCleanup(true);
		edgeController = NULL;
	}
}

EdgeController* EdgeController::getInstance() {
	if (edgeController == NULL) {
		edgeController = EdgeController::create();
	}
	return edgeController;
}

bool EdgeController::init() {
	if (!Node::init()) { return false; }

	auto gameEdgeParameter = ParameterManager::getGameParameterInstance(ParameterManager::getCurrentGameLevel())->edgeParameter;
	for (std::vector<EdgeParameter*>::iterator it = gameEdgeParameter.begin(); it != gameEdgeParameter.end(); it++) {
		switch ((*it)->type) {
		case 1:
			this->addChild(edge::createEdge1((*it)->firstPoint,(*it)->secondPoint));
			break;
		case 2:
			this->addChild(edge::createEdge2((*it)->firstPoint, (*it)->secondPoint));
			break;
		case 3:
			this->addChild(edge::createRope((*it)->firstPoint, (*it)->secondPoint));
			break;
		default:
			break;
		}
	}
	return true;
}