#include "Game.h"
#include <random>

#include "../parallax/include/renderer/renderable/Group.h"
#include "../parallax/include/renderer/renderable/Sprite.h"
//#include "GLFW/glfw3.h>

void Game::init() {
	m_Window = parallaxInit();

	unsigned int shaderID = prx::Resources::loadShader("base_shader", "res/shaders/default.vs", "res/shaders/default_light.fs");
	unsigned int shaderNoLightID = prx::Resources::loadShader("UI_shader", "res/shaders/default.vs", "res/shaders/default_nolight.fs");
	m_Shader = prx::Resources::getShader(shaderID);
	m_ShaderUI = prx::Resources::getShader(shaderNoLightID);
	m_Layer = new prx::SceneLayer(m_Shader);
	m_Layer2 = new prx::SceneLayer(m_ShaderUI);
	
	std::random_device rd;
	std::uniform_int_distribution<unsigned int> colorDistrib(0, 255);
	
	hpm::vec4 color;
	float step = 0.1;
	int counter = 0;
	prx::Group* group = new prx::Group(hpm::mat4::identity());
	for (float x = 0; x < 800; x += 3) {// 3, 1.0
		for (float y = 0; y < 600; y += 3) {
			unsigned int color = 255 << 24 | colorDistrib(rd) << 16 | colorDistrib(rd) << 8 | colorDistrib(rd);
			group->add(new prx::Sprite(hpm::vec3(x, y, 1.0), hpm::vec2(2), color));
			step += 0.0001f;
			counter++;
		}
	}
	unsigned int NotoSansID = prx::Resources::loadFont("res/fonts/NotoSans-Regular.ttf", 80);
	unsigned int AbrilFatfaceID = prx::Resources::loadFont("res/fonts/AbrilFatface-Regular.ttf", 50);
	
	prx::Font* NotoSans = prx::Resources::getFont(NotoSansID);
	prx::Font* AbrilFatface = prx::Resources::getFont(AbrilFatfaceID);
	
	group->add(new prx::Label("Hello world!", hpm::vec3(200, 150, 0), NotoSans, 0xff568745));
	m_Layer->add(group);
	auto text = new prx::Label("Text renderer!", hpm::vec3(20.0, 20.0, 0.0), AbrilFatface, 0xff3456ff);
	text->setText("sfasdf");
	m_FPSCounter = new prx::FPSCounter(*this);
	m_Layer2->add(m_FPSCounter);
	m_Layer2->add(text);
	unsigned int textureID = prx::Resources::loadTexture("res/textures/crate.png");
	prx::Texture* texture = prx::Resources::getTexture(textureID);
	//auto texture2 = prx::Resources::loadTexture("res/textures/test.png");
	auto texSprite = new prx::Sprite(hpm::vec3(100, 100, 1.0), hpm::vec2(200, 200), texture);
	m_Layer2->add(texSprite);
	auto sprite = new prx::Sprite(hpm::vec3(300, 300, 1.0), hpm::vec2(200, 200), 0xffffffff);
	
	m_Layer2->add(sprite);
	sprite->setColor(0xff654743);
	//texSprite->setTexture(texture2);
	//texSprite->setPosition(hpm::vec3(400, 300, 1));
	//texSprite->setSize(hpm::vec2(100, 600));
	unsigned int soundID = prx::Resources::loadSound("test", "res/audio/test.ogg");
	m_Sound = prx::Resources::getSound(soundID);
	
	float gain = 1.0;
	m_Sound->play();
}

void Game::tick() {
	m_FPSCounter->update();
}

void Game::update() {
	hpm::vec2 cursorPos = m_Window->getCursorPos();
	cursorPos.y = 600 - cursorPos.y;

	m_Shader->bind();
	m_Shader->setUniform("u_lightPos", cursorPos);
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
	
	m_Layer->draw();
	m_Layer2->draw();
}
