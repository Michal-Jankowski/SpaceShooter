#include <glm/ext/matrix_transform.hpp>
#include <array>
#include <memory>
#include <vector>
#include "GameScene.h"
#include "../engine/shaders/ShaderManager.h"
#include "../engine/shaders/ShaderProgramManager.h"
#include "../engine/textures/TextureManager.h"
#include "../engine/textures/SamplerManager.h"
#include "models/Ship.h"
#include "models/Collectible.h"
#include "../engine/maths/MatrixManager.h"
#include "models/Enemy.h"
#include "models/Planet.h"
#include "../engine/utils/ErrorCallback.h"

bool visualizeColorFrameBuffer = false;

void GameScene::initScene() {

	try {
		// Related info: https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions#glbuffer
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(err_callback::message_callback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);

		auto& shaderManager = ShaderManager::getInstance();
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& textureManager = TextureManager::getInstance();

		shaderManager.loadFragmentShader("main_part", "../src/shaders/shader.frag");
		shaderManager.loadFragmentShader("assimp_part", "../src/shaders/assimp.frag");
		shaderManager.loadVertexShader("main_part", "../src/shaders/shader.vert");
		shaderManager.loadVertexShader("assimp_part", "../src/shaders/assimp.vert");
		shaderManager.loadFragmentShader("outline_part", "../src/shaders/shaderOutline.frag");
		shaderManager.loadVertexShader("outline_part", "../src/shaders/shaderOutline.vert");
		shaderManager.loadFragmentShader("laser_part", "../src/shaders/line.frag");
		shaderManager.loadVertexShader("laser_part", "../src/shaders/line.vert");
		shaderManager.loadFragmentShader("skybox_part", "../src/shaders/skybox.frag");
		shaderManager.loadVertexShader("skybox_part", "../src/shaders/skybox.vert");

		auto& mainShaderProgram = shaderProgramManager.createShaderProgram("main");
		mainShaderProgram.addShaderToProgram(shaderManager.getVertexShader("main_part"));
		mainShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("main_part"));

        auto& assimpShaderProgram = shaderProgramManager.createShaderProgram("assimp");
        assimpShaderProgram.addShaderToProgram(shaderManager.getVertexShader("assimp_part"));
        assimpShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("assimp_part"));

        auto& singleColorShaderProgram = shaderProgramManager.createShaderProgram("outline");
		singleColorShaderProgram.addShaderToProgram(shaderManager.getVertexShader("outline_part"));
		singleColorShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("outline_part"));
		
		auto& laserShaderProgram = shaderProgramManager.createShaderProgram("laser");
		laserShaderProgram.addShaderToProgram(shaderManager.getVertexShader("laser_part"));
		laserShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("laser_part"));

		auto& skyboxShaderProgram = shaderProgramManager.createShaderProgram("skybox");
		skyboxShaderProgram.addShaderToProgram(shaderManager.getVertexShader("skybox_part"));
		skyboxShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("skybox_part"));
		shaderProgramManager.linkAllPrograms();

		// init objs
		collisionHandler = std::make_unique<CollisionHandler>();
		m_skybox = std::make_unique<Skybox>("res/skybox/blue");
		m_cube = std::make_unique<Cube>();
		m_ambientLight = std::make_unique<AmbientLight>(glm::vec3(0.6f, 0.6f, 0.6f));
		m_diffuseLight = std::make_unique<DiffuseLight>(glm::vec3(1.0f, 1.0f, 1.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), 15.0f);
		m_material = std::make_unique<Material>(12.0f, 20.0f);
		m_HUD = std::make_unique<GameHUD>(*this);
		m_pointLightOne = std::make_unique<PointLight>(glm::vec3(-60.0f, 20.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.3f, 0.3f, 0.004f, 0.0001f);
		m_pointLightTwo = std::make_unique<PointLight>(glm::vec3(60.0f, 20.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.3f, 0.3f, 0.0005f, 0.0005f);

		Material shinnyMaterial = Material(1.0f, 32.0f);

		SamplerManager::getInstance().createSampler("main", FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_TRILINEAR);
		TextureManager::getInstance().loadTexture2D("snow", "res/img/snow.png");
		TextureManager::getInstance().loadTexture2D("lava", "res/img/lava.png");

		int width, height;
		glfwGetWindowSize(getWindow(), &width, &height);
		m_camera = std::make_shared<Camera>(
                glm::vec3(-120.0f, 8.0f, 120.0f),
                glm::vec3(-120.0f, 8.0f, 119.0f),
                glm::vec3(0.0f, 1.0f, 0.f),
                glm::i32vec2(width / 2, height / 2),
                15.0f);
        auto ship = std::make_unique<Ship>(this, m_camera);
        shipRef = ship.get();
        addObject(std::move(ship));
        auto planet1 = std::make_unique<Planet>(this, 30.0f, true, glm::vec3(-50.0f, 0.0f, -50.0f));
        auto planet2 = std::make_unique<Planet>(this, 30.0f, true, glm::vec3(50.0f, 50.0f, -50.0f));
        addObject(std::move(planet2));

		auto sourceLightOne = std::make_unique<Planet>(this, 10, false,
                                                          "../res/models/sun.obj",
                                                          glm::vec3(-60.0f, 20.0f, 0.0f));
        auto sourceLightTwo = std::make_unique<Planet>(this, 10, false,
                                                          "../res/models/sun.obj",
                                                          glm::vec3(60.0f, 20.0f, 0.0f));
        addObject(std::move(planet1));
        addObject(std::move(sourceLightOne));
        addObject(std::move(sourceLightTwo));


	}
	catch (const std::runtime_error& error) {
		std::cout << "Error occured during initialization: " << error.what() << std::endl;
		closeWindow(true);
		return;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glClearDepth(1.0);
	glClearColor(0.2, 0.7f, 0.2f, 1.0f);
}

void GameScene::updateMatrices(){
    auto& matrixManager = MatrixManager::getInstance();

    matrixManager.setProjectionMatrix(getProjectionMatrix());
    matrixManager.setOrthoProjectionMatrix(getOrthoProjectionMatrix());
    matrixManager.setViewMatrix(m_camera->getViewMatrix());
}

void GameScene::updateShaderMatrices(const std::string &shaderKey){
    auto& shaderProgramManager = ShaderProgramManager::getInstance();
    auto& mainProgram = shaderProgramManager.getShaderProgram(shaderKey);
    mainProgram.useProgram();
    mainProgram.setUniform("matrices.projectionMatrix", getProjectionMatrix());
    mainProgram.setUniform("matrices.viewMatrix", m_camera->getViewMatrix());
    mainProgram.setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
    mainProgram.setUniform("isStencil", false);
	mainProgram.setUniform("cameraPosition", m_camera->getEye());

}

void GameScene::updateLights(const std::string &shaderKey){
    auto& shaderProgramManager = ShaderProgramManager::getInstance();
    auto& mainProgram = shaderProgramManager.getShaderProgram(shaderKey);
    mainProgram.useProgram();

	m_ambientLight->setUniform(mainProgram, "ambientLight");
	m_diffuseLight->setUniform(mainProgram, "diffuseLight");
	m_pointLightOne->setUniform(mainProgram, "pointLightOne");
	m_pointLightTwo->setUniform(mainProgram, "pointLightTwo");
}

void GameScene::clearBuffers() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void GameScene::renderScene() {


	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& textureManager = TextureManager::getInstance();
	clearBuffers();

    updateMatrices();
    updateShaderMatrices("main");
    updateShaderMatrices("assimp");
    updateLights("assimp");


    auto& mainProgram = shaderProgramManager.getShaderProgram("main");
  	auto& outlineProgram = shaderProgramManager.getShaderProgram("outline");

    glm::mat4 model = glm::mat4( 1.0 );
    glm::mat4 translated = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
  	mainProgram.useProgram();
    mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
    mainProgram.setUniform("matrices.modelMatrix",translated);


	// Set Light properties for skybox, instead we would have illuminated sky
	AmbientLight  ambientSkybox(glm::vec3(0.9f, 0.9f, 0.9f));
	DiffuseLight::none().setUniform(mainProgram, "diffuseLight");
	ambientSkybox.setUniform(mainProgram, "ambientLight");
	Material::none().setUniform(mainProgram, "material");
	//PointLight::none().setUniform(mainProgram, "pointLightOne");
	//PointLight::none().setUniform(mainProgram, "pointLightTwo");


	SamplerManager::getInstance().getSampler("main").bind();
	m_ambientLight->setUniform(mainProgram, "ambientLight");
	m_diffuseLight->setUniform(mainProgram, "diffuseLight");
	m_pointLightOne->setUniform(mainProgram, "pointLightOne");
	m_pointLightTwo->setUniform(mainProgram, "pointLightTwo");

	mainProgram.setUniform("cameraPosition", m_camera->getEye());
	m_material->setUniform(mainProgram, "material");

	Cube cub1 = Cube();
	auto crateSize = 8.0f;
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 0.0f, -80.0f));
	float renderedHeight = 5.0f;
	model = glm::translate(model, glm::vec3(0.0f, 1.5f + crateSize / 2.0f + renderedHeight, 0.0f));
	model = glm::scale(model, glm::vec3(crateSize, crateSize, crateSize));
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", model);
	TextureManager::getInstance().getTexture("lava").bind(0);
	m_cube->render();

	// Order of drawing skybox, text does matters, due to the depth buffer manipulation
	m_skybox->render(m_camera->getEye(), mainProgram);

    drawGameObjects();
    if(drawDebug) {
        collisionHandler->drawDebug();
    }

    m_HUD->renderHUD(ambientSkybox);
    drawGameObjectsHUD();
	glEnable(GL_DEPTH_TEST);
}
void GameScene::onWindowSizeChanged(int width, int height)
{
	if (width == 0 || height == 0) {
		return;
	}
}

void GameScene::onMouseButtonPressed(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		const auto cursorPosition = getOpenGLCursorPosition();
	}
}

void GameScene::updateScene() {
	
	std::string title = "SpaceShooter FPS count: " + std::to_string(getFPS()) + " VSync: " + (isVerticalSynchronizationEnabled() ? "On" : "Off");
	glfwSetWindowTitle(getWindow(), title.c_str());
	/* Should close window*/
	if (keyPressedOnce(GLFW_KEY_ESCAPE)) {
		closeWindow();
	}
	/* Vertical Synchronization*/
	if (keyPressedOnce(GLFW_KEY_0)) {
		setVerticalSynchronization(!isVerticalSynchronizationEnabled());
	}
	/* Switch wireframe mode*/
	if (keyPressedOnce(GLFW_KEY_1)) {
		setWireframeMode(!isWireframeModeEnabled());
	}
	/* Free floating camera or static camera*/
	if (keyPressedOnce(GLFW_KEY_2)) {
		glfwSetInputMode(this->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		setCameraUpdateEnabled(!isCameraUpdateEnabled());
	}
	/* Update camera state*/
	if (isCameraUpdateEnabled()) {
		m_camera->update([this](int keyCode) {return this->keyPressed(keyCode); }, [this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
		[this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y); }, [this](float value) { return this->getValueByTime(value); });
	}
	/* Switch Ambient Light*/
	if (keyPressedOnce(GLFW_KEY_4)) {
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& mainProgram = shaderProgramManager.getShaderProgram("main");
		mainProgram.useProgram();
		m_ambientLight->switchLight(mainProgram, !m_ambientLight->getLightState());

	}
	if (keyPressedOnce(GLFW_KEY_5)) {
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& mainProgram = shaderProgramManager.getShaderProgram("main");
		mainProgram.useProgram();

	}
    if (keyPressedOnce(GLFW_KEY_6)) {
        drawDebug = !drawDebug;
    }
	m_rotationAngleRad += getValueByTime(glm::radians(5.0f));
    gameObjectsLogicLoop();
}

void GameScene::releaseScene() {
	m_skybox.reset();
	ShaderManager::getInstance().clearShaderCache();
	ShaderProgramManager::getInstance().clearShaderProgramCache();
	TextureManager::getInstance().clearTextureCache();
	SamplerManager::getInstance().clearSamplerKeys();
	m_cube.reset();
	m_HUD.reset();
    for (int i = 0; i < gameObjects.size(); ++i) {
        gameObjects[i].reset();
    }
}

void GameScene::gameObjectsLogicLoop() {
    ///SPAWN
    while(!creatingGameObjects.empty()){
        auto inserting = creatingGameObjects.front().get();
        if(const auto model = dynamic_cast<GameModel*>(inserting)){
            if(model->mesh.hasTransparentMaterials()){
                gameObjects.push_back(std::move(creatingGameObjects.front()));
            }
            else{
                gameObjects.insert(gameObjects.begin(), std::move(creatingGameObjects.front()));
            }
        }
        else{
            gameObjects.insert(gameObjects.begin(), std::move(creatingGameObjects.front()));
        }
        creatingGameObjects.pop();
    }
    ///UPDATE
    for (auto & gameObject : gameObjects) {
        gameObject->update();
    }
    ///COLLISIONS
    collisionHandler->runCollisionChecks();
    ///REMOVE
    for (int i = 0; i < gameObjects.size(); ++i) {
        if(gameObjects[i]->awaitingDestroy){
            removeGameObjectAt(i);
        }
    }
}

void GameScene::drawGameObjects() {
    for (auto & gameObject : gameObjects) {
        gameObject->render();
        if(drawDebug){
            gameObject->renderDebug();
        }
    }
}


void GameScene::addObject(std::unique_ptr<GameObject> go) {
    if(go->useCollision(nullptr)) {
        collisionHandler->registerCollider(go.get());
    }
    creatingGameObjects.push(std::move(go));

}

void GameScene::removeGameObjectAt(int &i) {
    if(gameObjects[i]->useCollision(nullptr)) {
        collisionHandler->deregisterCollider(gameObjects[i].get());
    }
    gameObjects[i].reset();
    gameObjects.erase(gameObjects.begin()+i);
    i--;
}


void GameScene::drawGameObjectsHUD() {
    for (auto & gameObject : gameObjects) {
        gameObject->drawHud(m_HUD.get());
    }
    m_HUD->clearLines();
}

const CollisionHandler &GameScene::getCollisionHandler() {
    return *collisionHandler;
}

Ship* GameScene::getPlayer() {
    return shipRef;
}

void GameScene::reinitObjects() {
    for (auto & gameObject : gameObjects) {
        gameObject->reinit();
    }
}


