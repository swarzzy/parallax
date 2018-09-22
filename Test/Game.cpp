#include "Game.h"
#include <random>

#include "../parallax/include/renderer/renderable/Group.h"
#include "../parallax/include/textures/TextureAtlas.h"
#include "../parallax/include/renderer/renderable/Sprite.h"
//#include "GLFW/glfw3.h>
#include "../parallax/include/textures/Texture.h"
#include <experimental/filesystem>
#include <filesystem>

void Game::init() {
	m_Window = parallaxInit();

	//unsigned int shaderID = prx::Resources::loadShader("base_shader", "res/shaders/default.vs", "res/shaders/default_light.fs");
	unsigned int shaderNoLightID = prx::Resources::loadShader("UI_shader", "res/shaders/default.vs", "res/shaders/default_nolight.fs");
	//m_Shader = prx::Resources::getShader(shaderID);
	m_ShaderUI = prx::Resources::getShader(shaderNoLightID);
	//m_Layer = new prx::SceneLayer(m_Shader);
	m_Layer2 = new prx::SceneLayer(m_ShaderUI);
	
	//std::random_device rd;
	//std::uniform_int_distribution<unsigned int> colorDistrib(0, 255);
	
	//hpm::vec4 color;
	//float step = 0.1;
	//int counter = 0;
	//prx::Group* group = new prx::Group(hpm::mat4::identity());
	//for (float x = 0; x < 800; x += 3) {// 3, 1.0
	//	for (float y = 0; y < 600; y += 3) {
	//		unsigned int color = 255 << 24 | colorDistrib(rd) << 16 | colorDistrib(rd) << 8 | colorDistrib(rd);
	//		group->add(new prx::Sprite(hpm::vec3(x, y, 1.0), hpm::vec2(2), color));
	//		step += 0.0001f;
	//		counter++;
	//	}
	//}
	/*unsigned int NotoSansID = prx::Resources::loadFont("res/fonts/NotoSans-Regular.ttf", 80, 1.0);
	unsigned int AbrilFatfaceID = prx::Resources::loadFont("res/fonts/AbrilFatface-Regular.ttf", 300, 1.0);
	
	prx::Font* NotoSans = prx::Resources::getFont(NotoSansID);
	prx::Font* AbrilFatface = prx::Resources::getFont(AbrilFatfaceID);*/
	
	//group->add(new prx::Label("Hello world!", hpm::vec3(200, 150, 0), NotoSans, 0xff568745));
	//m_Layer->add(group);
	//auto text = new prx::Label("Text renderer!", hpm::vec3(20.0, 20.0, 0.0), AbrilFatface, 0xff3456ff);
	//text->setText("sfaggysdf");
	//m_FPSCounter = new prx::FPSCounter(*this);
	//m_Layer2->add(m_FPSCounter);
	//m_Layer2->add(text);
	//unsigned int textureID1 = prx::Resources::loadTexture("res/textures/crate.png");
	//prx::Texture* texture1 = prx::Resources::getTexture(textureID1);
	//unsigned int textureID2 = prx::Resources::loadTexture("res/textures/default.jpg");
	//prx::Texture* texture2 = prx::Resources::getTexture(textureID2);
	//unsigned int textureID3 = prx::Resources::loadTexture("res/textures/test.png");
	//prx::Texture* texture3 = prx::Resources::getTexture(textureID3);
	//
	//auto sprite1 = new prx::Sprite(hpm::vec3(0, 0, 1.0), hpm::vec2(100), texture1);
	//auto sprite2 = new prx::Sprite(hpm::vec3(100, 0, 1.0), hpm::vec2(100), texture2);
	//auto sprite3 = new prx::Sprite(hpm::vec3(200, 0, 1.0), hpm::vec2(100), texture3);

	//m_Layer2->add(sprite1);
	//m_Layer2->add(sprite2);
	//m_Layer2->add(sprite3);

	////auto sprite = new prx::Sprite(hpm::vec3(300, 300, 1.0), hpm::vec2(200, 200), 0xffffffff);
	//
	////m_Layer2->add(sprite);
	//
	//unsigned int soundID = prx::Resources::loadSound("test", "res/audio/shotgun.wav");
	//m_Sound = prx::Resources::getSound(soundID);
	//
	//float gain = 1.0;
	//m_Sound->play();

	//std::random_device rd;
	std::mt19937 engine;
	std::uniform_int_distribution<unsigned int> DistribX(0, 750);
	std::uniform_int_distribution<unsigned int> DistribY(0, 550);

	for (int i = 0; i < 8; i++)
		m_Path.pop_back();
	std::string path = m_Path + "res\\textures";
	for (auto& p : std::filesystem::directory_iterator(path)) {
		m_Layer2->add(new prx::Sprite(hpm::vec3(DistribX(engine), DistribY(engine), 1.0), hpm::vec2(100), new prx::Texture(p.path().string())));
		
	}

	m_FPSCounter = new prx::FPSCounter(*this);
	m_Layer2->add(m_FPSCounter);
		
}

void Game::tick() {
	m_FPSCounter->update();
	std::cout << m_Window->getWidth() << std::endl;
	std::cout << m_Window->getHeight() << std::endl;
	//m_Layer->setProjectionMatrix(hpm::mat4::ortho(0.0, m_Window->getWidth(), m_Window->getHeight(), 0.0, -10.0, 100.0));
	m_Layer2->setProjectionMatrix(hpm::mat4::ortho(0.0, m_Window->getWidth(), m_Window->getHeight(), 0.0, -10.0, 100.0));
}

void Game::update() {
	hpm::vec2 cursorPos = m_Window->getCursorPos();
	cursorPos.y = m_Window->getHeight() - cursorPos.y;

	//m_Shader->bind();
	//m_Shader->setUniform("u_lightPos", cursorPos);
}

void Game::render() {
	if (m_Window->isKeyPressed(GLFW_KEY_P))
		m_Sound->pause();
	if (m_Window->isKeyPressed(GLFW_KEY_S))
		m_Sound->play();
	if (m_Window->isKeyPressed(GLFW_KEY_R))
		m_Sound->stop();
	if (m_Window->isKeyPressed(GLFW_KEY_L))
		m_Sound->loop();
	if (m_Window->isKeyPressed(GLFW_KEY_G))
		m_Window->enableFullScreen(true);
	if (m_Window->isKeyPressed(GLFW_KEY_F))
		m_Window->enableFullScreen(false);
	
	//m_Layer->draw();
	m_Layer2->draw();
}
