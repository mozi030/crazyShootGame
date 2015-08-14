#include"CameraController.h"

CameraController*CameraController::cameraController = NULL;

CameraController::CameraController() {}

CameraController::~CameraController(){
	if (cameraController != NULL) {
		cameraController->removeFromParentAndCleanup(true);
		cameraController = NULL;
	}
}

CameraController*CameraController::getInstance() {
	if (cameraController == NULL) {
		cameraController = CameraController::create();
	}
	return cameraController;
}

Camera* CameraController::getCamera() {
	return camera;
}

bool CameraController::init() {
	if (!Layer::init()) 
		return false;
	Size visibleSize = ParameterManager::getVisibleSize();
	//camera = Camera::createOrthographic(visibleSize.width, visibleSize.height,1,100);
	camera = Camera::create();
	camera->setCameraFlag(CameraFlag::USER1);
	this->addChild(camera);
	//this->lookAtInitial();
	return true;
}

void CameraController::updateCamera(bool isGameEnded) {
	if (isGameEnded == true) return;

	Size visibleSize = ParameterManager::getVisibleSize();
	Size mapSize = ParameterManager::getGameParameterInstance(ParameterManager::getCurrentGameLevel())->mapSize;
	//设置camera位置
	Vec2 archerPosition = ArcherController::getInstance()->getArcher()->getPosition();

	float x, y;
	if (archerPosition.x <= visibleSize.width / 2) {
		x = visibleSize.width / 2;
	}
	else if (archerPosition.x >= mapSize.width - visibleSize.width / 2){
		x = mapSize.width - visibleSize.width / 2;
	}
	else {
		x = archerPosition.x;
	}
	if (archerPosition.y <= visibleSize.height / 2) {
		y = visibleSize.height / 2;
	}
	else if (archerPosition.y >= mapSize.height - visibleSize.height / 2) {
		y = mapSize.height - visibleSize.height / 2;
	}
	else {
		y = archerPosition.y;
	}
	Vec3 eyePos = Vec3(x, y, camera->getPositionZ());
	camera->setPosition3D(eyePos);
	camera->lookAt(Vec3(eyePos.x, eyePos.y, 0),Vec3::UNIT_Y);

	//设置gameEndedItem位置
	//GameoverController::getInstance()->gameEndedMenu->setPosition(x - visibleSize.width / 2, y - visibleSize.height / 2);

	//设置ProgressTimeController位置
	ArcherController::getInstance()->getProgressTime()->setPosition(x - visibleSize.width / 2, y - visibleSize.height / 2);
	ItemController::getInstance()->setPosition(x - visibleSize.width / 2, y - visibleSize.height / 2);
}

void CameraController::lookAtInitial() {
	Size visibleSize = ParameterManager::getVisibleSize();
	camera->setPosition3D(Vec3(visibleSize.width / 2, visibleSize.height / 2, camera->getPositionZ()));
	camera->lookAt(Vec3(visibleSize.width / 2, visibleSize.height / 2, 0), Vec3::UNIT_Y);
}