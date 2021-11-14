#include <glm/ext/matrix_transform.hpp>
#include "GameScene.h"
#include "ShaderManager.h"
#include "ShaderProgramManager.h"
#include "TextureManager.h"
#include "SamplerManager.h"
#include "MatrixManager.h"
#include <glm/gtc/matrix_transform.hpp>


std::vector<glm::vec3> cratePositions
{
	glm::vec3(-30.0f, 0.0f, -80.0f),
	glm::vec3(30.0f, 0.0f, -40.0f),
	glm::vec3(-30.0f, 0.0f, 0.0f),
	glm::vec3(30.0f, 0.0f, 40.0f),
	glm::vec3(-30.0f, 0.0f, 80.0f),
};

float rotationAngleRad = 0.0f;


void GameScene::initScene() {

	try {
		auto& shaderManager = ShaderManager::getInstance();
		auto& shaderProgramManager = ShaderProgramManager::getInstance();
		auto& textureManager = TextureManager::getInstance();

		shaderManager.loadFragmentShader("main_part", "../src/shaders/shader.frag");
		shaderManager.loadVertexShader("main_part", "../src/shaders/shader.vert");

		auto& mainShaderProgram = shaderProgramManager.createShaderProgram("main");
		mainShaderProgram.addShaderToProgram(shaderManager.getVertexShader("main_part"));
		mainShaderProgram.addShaderToProgram(shaderManager.getFragmentShader("main_part"));

		// init skybox
		m_skybox = std::make_unique<Skybox>("res/skybox/blue", true, true, true);
		m_cube = std::make_unique<Cube>(true, true, true);
		m_plainGround = std::make_unique<PlainGround>(true, true, true);
		m_ambientLight = std::make_unique<AmbientLight>(glm::vec3(0.6f, 0.6f, 0.6f));
		m_diffuseLight = std::make_unique<DiffuseLight>(glm::vec3(1.0f, 1.0f, 1.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)), 15.0f);
		m_material = std::make_unique<Material>(12.0f, 20.0f);
		m_ship = std::make_unique<GameModel>("../res/models/ship.obj");
        SamplerManager::getInstance().createSampler("main", FilterOptions::MAG_FILTER_BILINEAR, FilterOptions::MIN_FILTER_TRILINEAR);
		TextureManager::getInstance().loadTexture2D("snow", "res/img/snow.png");
		TextureManager::getInstance().loadTexture2D("lava", "res/img/lava.png");

		shaderProgramManager.linkAllPrograms();
		int width, height;
		glfwGetWindowSize(getWindow(), &width, &height);
		m_camera = std::make_unique<Camera>(glm::vec3(-120.0f, 8.0f, 120.0f), glm::vec3(-120.0f, 8.0f, 119.0f), glm::vec3(0.0f, 1.0f, 0.f), glm::i32vec2(width / 2, height / 2), 15.0f);
	}
	catch (const std::runtime_error& error) {
		std::cout << "Error occured during initialization: " << error.what() << std::endl;
		closeWindow(true);
		return;
	}
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glClearColor(0.2, 0.7f, 0.2f, 1.0f);

}

void GameScene::renderScene() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	auto& matrixManager = MatrixManager::getInstance();
	auto& shaderProgramManager = ShaderProgramManager::getInstance();
	auto& textureManager = TextureManager::getInstance();


    auto& mainProgram = shaderProgramManager.getShaderProgram("main");

    matrixManager.setProjectionMatrix(getProjectionMatrix());
    matrixManager.setOrthoProjectionMatrix(getOrthoProjectionMatrix());
    matrixManager.setViewMatrix(m_camera->getViewMatrix());

    glm::mat4 model = glm::mat4( 1.0 );
    glm::mat4 translated = glm::translate(model, glm::vec3(0.0f, 1.0f, 0.0f));
	mainProgram.useProgram();
    mainProgram.setUniform("matrices.modelMatrix",translated);

    m_ship->moveBy(glm::vec3(0.0f, 0.0f, -SetupWindow::getDeltaTime()));
    m_ship->render();

	//Render skybox
	
	matrixManager.setProjectionMatrix(getProjectionMatrix());
	matrixManager.setOrthoProjectionMatrix(getOrthoProjectionMatrix());
	matrixManager.setViewMatrix(m_camera->getViewMatrix());

	mainProgram = shaderProgramManager.getShaderProgram("main");
	mainProgram.useProgram();
	mainProgram.setUniform("matrices.projectionMatrix", getProjectionMatrix());
	mainProgram.setUniform("matrices.viewMatrix", m_camera->getViewMatrix());
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
	mainProgram.setUniform("color", glm::vec4(1.0, 1.0, 1.0, 1.0));
	mainProgram.setUniform("sampler", 0);

	// TODO: render skybox only with AmbientLight, do we need that?
	AmbientLight  ambientSkybox(glm::vec3(0.9f, 0.9f, 0.9f));
	DiffuseLight::none().setUniform(mainProgram, "diffuseLight");
	ambientSkybox.setUniform(mainProgram, "ambientLight");
	Material::none().setUniform(mainProgram, "material");
	// render skybox
	m_skybox->render(m_camera->getEye(), mainProgram);
	
	SamplerManager::getInstance().getSampler("main").bind();
	m_ambientLight->setUniform(mainProgram, "ambientLight");
	m_diffuseLight->setUniform(mainProgram, "diffuseLight");
	mainProgram.setUniform("cameraPosition", m_camera->getEye());
	m_material->setUniform(mainProgram, "material");
	std::vector<glm::mat4> crateModelMatrices;
	for (const auto& position : cratePositions)
	{
		const auto crateSize = 8.0f;
		auto model = glm::translate(glm::mat4(1.0f), position);
		float renderedHeight = 5.0f;
		model = glm::translate(model, glm::vec3(0.0f, 1.5f + crateSize / 2.0f + renderedHeight, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, rotationAngleRad, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(crateSize, crateSize, crateSize));
		crateModelMatrices.push_back(model);
		mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", model);
		TextureManager::getInstance().getTexture("lava").bind(0);
		m_cube->render();
	}

	textureManager.getTexture("snow").bind(0);
	mainProgram.SetModelAndNormalMatrix("matrices.modelMatrix", "matrices.normalMatrix", glm::mat4(1.0f));
	//m_plainGround->render();
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
	rotationAngleRad += getValueByTime(glm::radians(5.0f));

}

void GameScene::releaseScene() {

	m_skybox.reset();
	m_plainGround.reset();
	ShaderManager::getInstance().clearShaderCache();
	ShaderProgramManager::getInstance().clearShaderProgramCache();
	TextureManager::getInstance().clearTextureCache();
	SamplerManager::getInstance().clearSamplerKeys();
	m_cube.reset();
    m_ship.release();
}
