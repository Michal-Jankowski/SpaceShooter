#include <glm/ext/matrix_transform.hpp>
#include <array>
#include <memory>
#include <vector>
#include "GameScene.h"
#include "../engine/shaders/ShaderManager.h"
#include "../engine/shaders/ShaderProgramManager.h"
#include "../engine/textures/TextureManager.h"
#include "../engine/textures/SamplerManager.h"
#include "../engine/buffers/ObjPicker.h"
#include "models/Ship.h"
#include "models/Collectible.h"
#include "../engine/maths/MatrixManager.h"
#include "../engine/buffers/DefaultBuff.h"
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
		shaderManager.loadFragmentShader("outline_part", "../src/shaders/shaderOutline.frag");
		shaderManager.loadVertexShader("outline_part", "../src/shaders/shaderOutline.vert");
		shaderManager.loadFragmentShader("laser_part", "../src/shaders/line.frag");
		shaderManager.loadVertexShader("laser_part", "../src/shaders/line.vert");

		auto& mainShaderProgram = shaderProgramManager.createShaderProgram("main");
		mainShaderProgram.addShaderToProgram(shaderManager.getVertexShader("main_part"));
		mainShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("main_part"));

        auto& assimpShaderProgram = shaderProgramManager.createShaderProgram("assimp");
        assimpShaderProgram.addShaderToProgram(shaderManager.getVertexShader("main_part"));
        assimpShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("assimp_part"));

        auto& singleColorShaderProgram = shaderProgramManager.createShaderProgram("outline");
		singleColorShaderProgram.addShaderToProgram(shaderManager.getVertexShader("outline_part"));
		singleColorShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("outline_part"));
		
		auto& laserShaderProgram = shaderProgramManager.createShaderProgram("laser");
		laserShaderProgram.addShaderToProgram(shaderManager.getVertexShader("laser_part"));
		laserShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("laser_part"));

		// init objs
		m_skybox = std::make_unique<Skybox>("res/skybox/blue", true, true, true);
		m_cube = std::make_unique<Cube>(true, true, true);
		m_ambientLight = std::make_unique<AmbientLight>(glm::vec3(0.6f, 0.6f, 0.6f));
		m_diffuseLight = std::make_unique<DiffuseLight>(glm::vec3(1.0f, 1.0f, 1.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), 15.0f);
		m_material = std::make_unique<Material>(12.0f, 20.0f);
		m_sphere = std::make_unique<Sphere>(30.0f, 15, 15, true, true, true);
		m_HUD = std::make_unique<GameHUD>(*this);
		m_pointLightOne = std::make_unique<PointLight>(glm::vec3(-60.0f, 20.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), 0.3f, 0.3f, 0.004f, 0.0001f);
		m_pointLightTwo = std::make_unique<PointLight>(glm::vec3(60.0f, 20.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 0.3f, 0.3f, 0.0005f, 0.0005f);

		Material shinnyMaterial = Material(1.0f, 32.0f);

		SamplerManager::getInstance().createSampler("main", FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_TRILINEAR);
		TextureManager::getInstance().loadTexture2D("snow", "res/img/snow.png");
		TextureManager::getInstance().loadTexture2D("lava", "res/img/lava.png");

		shaderProgramManager.linkAllPrograms();
		int width, height;
		glfwGetWindowSize(getWindow(), &width, &height);
		ObjPicker::getInstance().initialize();
		m_camera = std::make_shared<Camera>(
                glm::vec3(-120.0f, 8.0f, 120.0f),
                glm::vec3(-120.0f, 8.0f, 119.0f),
                glm::vec3(0.0f, 1.0f, 0.f),
                glm::i32vec2(width / 2, height / 2),
                15.0f);

		gameObjects.push_back(std::make_unique<Ship>(m_camera));
        auto planet1 = std::make_unique<Planet>(30.0f, this, glm::vec3(-50.0f, 0.0f, -50.0f));
		// Need a way to represent pointLight object, Planet is non-ideal solution
		auto sourceLightOne = std::make_unique<Planet>(3.0f, this, glm::vec3(-60.0f, 20.0f, 0.0f));
		auto sourceLightTwo = std::make_unique<Planet>(3.0f, this, glm::vec3(60.0f, 20.0f, 0.0f));

		gameObjects.push_back(std::move(planet1));
		gameObjects.push_back(std::move(sourceLightOne));
		gameObjects.push_back(std::move(sourceLightTwo));


		//gameObjects.push_back(std::make_unique<Planet>(1.0f, this));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
    mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
    mainProgram.setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
    mainProgram.setUniform("isStencil", false);
}

void GameScene::updateLights(const std::string &shaderKey){
    auto& shaderProgramManager = ShaderProgramManager::getInstance();
    auto& mainProgram = shaderProgramManager.getShaderProgram(shaderKey);
    mainProgram.useProgram();
    m_ambientLight->setUniform(mainProgram, "ambientLight");
    m_diffuseLight->setUniform(mainProgram, "diffuseLight");
}

void GameScene::renderScene() {


	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& textureManager = TextureManager::getInstance();


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	DefaultBuff::bindAsBothReadAndDraw();

    updateMatrices();
    updateShaderMatrices("main");
    updateShaderMatrices("assimp");
    updateLights("assimp");
	gameObjectsLoop();
    auto& mainProgram = shaderProgramManager.getShaderProgram("main");
  	auto& outlineProgram = shaderProgramManager.getShaderProgram("outline");

    glm::mat4 model = glm::mat4( 1.0 );
    glm::mat4 translated = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
  	mainProgram.useProgram();
    mainProgram.setUniform("matrices.modelMatrix",translated);


	auto& objectPicker = ObjPicker::getInstance();
	objectPicker.renderAllPickableObjects();

	if (visualizeColorFrameBuffer)
	{
		const auto cursorPosition = getOpenGLCursorPosition();
		objectPicker.performObjectPicking(cursorPosition.x, cursorPosition.y);
		objectPicker.copyColorToDefaultFrameBuffer();
	}
	// Set Light properties for skybox, instead we would have illuminated sky
	AmbientLight  ambientSkybox(glm::vec3(0.9f, 0.9f, 0.9f));
	DiffuseLight::none().setUniform(mainProgram, "diffuseLight");
	ambientSkybox.setUniform(mainProgram, "ambientLight");
	Material::none().setUniform(mainProgram, "material");
	PointLight::none().setUniform(mainProgram, "pointLightOne");
	PointLight::none().setUniform(mainProgram, "pointLightTwo");
	m_skybox->render(m_camera->getEye(), mainProgram);

	SamplerManager::getInstance().getSampler("main").bind();
	m_ambientLight->setUniform(mainProgram, "ambientLight");
	m_diffuseLight->setUniform(mainProgram, "diffuseLight");
	m_pointLightOne->setUniform(mainProgram, "pointLightOne");
	m_pointLightTwo->setUniform(mainProgram, "pointLightTwo");

	mainProgram.setUniform("cameraPosition", m_camera->getEye());
	m_material->setUniform(mainProgram, "material");

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	Cube cub1 = Cube();
	auto crateSize = 8.0f;
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 0.0f, -80.0f));
	float renderedHeight = 5.0f;
	model = glm::translate(model, glm::vec3(0.0f, 1.5f + crateSize / 2.0f + renderedHeight, 0.0f));
	model = glm::scale(model, glm::vec3(crateSize, crateSize, crateSize));
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", model);
	TextureManager::getInstance().getTexture("lava").bind(0);
	m_cube->render();
	

	textureManager.getTexture("snow").bind(0);
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
	m_sphere->render();

	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilMask(0x00);

	mainProgram.setUniform("isStencil", true);
	crateSize = 10.0f;
	model = glm::translate(glm::mat4(1.0f), glm::vec3(-30.0f, 0.0f, -80.0f));
	renderedHeight = 5.0f;
	model = glm::translate(model, glm::vec3(0.0f, 1.5f + crateSize / 2.0f + renderedHeight, 0.0f));
	model = glm::scale(model, glm::vec3(crateSize, crateSize + 5.0f, crateSize ));
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", model);
	TextureManager::getInstance().getTexture("lava").bind(0);
	m_cube->render();
	mainProgram.setUniform("isStencil", false);

    m_HUD->renderHUD(ambientSkybox);
    drawGameObjectsHUD();

	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);

	DefaultBuff::bindAsBothReadAndDraw();
	DefaultBuff::setFullViewport();
}
void GameScene::onWindowSizeChanged(int width, int height)
{
	if (width == 0 || height == 0) {
		return;
	}
	ObjPicker::getInstance().resizePickingFrameBuffer(width, height);
}

void GameScene::onMouseButtonPressed(int button, int action) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		const auto cursorPosition = getOpenGLCursorPosition();
		ObjPicker::getInstance().performObjectPicking(cursorPosition.x, cursorPosition.y);
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
		setCameraUpdateEnabled(!isCameraUpdateEnabled());
	}
	/* Update camera state*/
	if (isCameraUpdateEnabled()) {
		m_camera->update([this](int keyCode) {return this->keyPressed(keyCode); }, [this]() {double curPosX, curPosY; glfwGetCursorPos(this->getWindow(), &curPosX, &curPosY); return glm::u32vec2(curPosX, curPosY); },
		[this](const glm::i32vec2& pos) {glfwSetCursorPos(this->getWindow(), pos.x, pos.y); }, [this](float value) { return this->getValueByTime(value); });
	}
	/* Switch Diffuse Light*/
	if (keyPressedOnce(GLFW_KEY_3)) {
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& mainProgram = shaderProgramManager.getShaderProgram("main");
		mainProgram.useProgram();
		m_diffuseLight->switchLight(mainProgram, !m_diffuseLight->getLightState());
	}
	/* Switch Ambient Light*/
	if (keyPressedOnce(GLFW_KEY_4)) {
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& mainProgram = shaderProgramManager.getShaderProgram("main");
		mainProgram.useProgram();
		m_ambientLight->switchLight(mainProgram, !m_ambientLight->getLightState());

	}
	if (keyPressedOnce(GLFW_KEY_5)) {
		visualizeColorFrameBuffer = !visualizeColorFrameBuffer;

	}
	
	ObjPicker::getInstance().updateAllPickableObjects(getValueByTime(1.0f));
	m_rotationAngleRad += getValueByTime(glm::radians(5.0f));

}

void GameScene::releaseScene() {
	ObjPicker::getInstance().release();
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

void GameScene::gameObjectsLoop() {
    ///SPAWN
    while(!creatingGameObjects.empty()){
        gameObjects.push_back(std::move(creatingGameObjects.front()));
        creatingGameObjects.pop();
    }
    ///UPDATE
    for (auto & gameObject : gameObjects) {
        gameObject->update(this);
    }
    ///COLLISIONS
    for (int i = 0; i < gameObjects.size(); ++i) {
        for (int j = i+1; j < gameObjects.size(); ++j) {
            if (gameObjects[i]->useCollision(gameObjects[j].get())
             || gameObjects[j]->useCollision(gameObjects[i].get())) {
                bool col = gameObjects[i]->col->isColliding(gameObjects[j]->col.get());
                if(col){
                    gameObjects[i]->onCollision(gameObjects[j].get());
                    gameObjects[j]->onCollision(gameObjects[i].get());
                }
            }
        }

    }
    ///REMOVE
    for (int i = 0; i < gameObjects.size(); ++i) {
        if(gameObjects[i]->awaitingDestroy){
            gameObjects[i].reset();
            gameObjects.erase(gameObjects.begin()+i);
            i--;
        }
    }
    ///RENDER
    for (auto & gameObject : gameObjects) {
        gameObject->render();

    }
}

void GameScene::addObject(std::unique_ptr<GameObject> go) {
    creatingGameObjects.push(std::move(go));
}

void GameScene::drawGameObjectsHUD() {
    for (auto & gameObject : gameObjects) {
        gameObject->drawHud(m_HUD.get());
    }
    m_HUD->clearLines();
}
