#include "Game.h"
#include <random>

#include "../parallax/include/renderer/renderable/Group.h"
#include "../parallax/include/textures/TextureAtlas.h"
#include "../parallax/include/renderer/renderable/Sprite.h"
//#include "GLFW/glfw3.h>
#include "../parallax/include/textures/Texture.h"
#include <experimental/filesystem>
#include <filesystem>
#include "../parallax/include/renderer/layers/UILayer.h"
#include "../parallax/include/renderer/renderable/UI/UIButtonBase.h"
#include "ButtonListener.h"
#include "../parallax/include/renderer/renderable/UI/UIGroup.h"
#include "../parallax/include/renderer/renderable/UI/UIButton.h"
#include "../parallax/include/textures/SpriteSheet.h"

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
	unsigned int soundID = prx::Resources::loadSound("test", "res/audio/test.ogg");
	m_Sound = prx::Resources::getSound(soundID);
	//
	//float gain = 1.0;
	m_Sound->play();

	//std::random_device rd;
	std::mt19937 engine;
	std::uniform_int_distribution<unsigned int> DistribX(0, 750);
	std::uniform_int_distribution<unsigned int> DistribY(0, 550);

	/*for (int i = 0; i < 8; i++)
		m_Path.pop_back();
	std::string path = m_Path + "res\\textures";
	for (auto& p : std::filesystem::directory_iterator(path)) {
		m_Layer2->add(new prx::Sprite(hpm::vec3(DistribX(engine), DistribY(engine), 1.0), hpm::vec2(100), new prx::Texture(p.path().string())));
		
	}*/
	prx::SpriteSheet* sheet = new prx::SpriteSheet("res/textures/hero_spritesheet.png", 8, 5);
	std::vector<unsigned int> mask = { 0,1,2,3,4,5, 6, 7 };
	std::vector<unsigned int> mask2 = { 8,9,10,11,12,13 };
	std::vector<unsigned int> mask3 = { 24, 25, 26, 27, 28, 29, 30 };
	aID = sheet->addAnimation("1", mask);
	aID2 = sheet->addAnimation("2", mask2);
	aID3 = sheet->addAnimation("3", mask3);
	hero = new prx::AnimatedSprite(hpm::vec3(0.0, 0.0, 0.0), hpm::vec2(100), sheet, aID);
	//hero->playAnimation(aID2);
	m_Layer2->add(hero);
	//m_Layer2->add();
	m_Layer2->add(new prx::Label("WASD to move", hpm::vec3(400, 500, 0.0), prx::Resources::getFont(prx::RESOURCES_DEFAULT_FONT_ID), 0xffffffff));
	//m_Layer2->add(new prx::Sprite(hpm::vec3(0.0, 0.0, 0.0), hpm::vec2(600), sheet));

	auto tex = prx::Resources::getTexture(prx::Resources::loadTexture("res/textures/button_play_released.png"));
	sp = new prx::Sprite(hpm::vec3(0.0, 0.0, 0.0), hpm::vec2(100), tex);
	m_Layer2->add(sp);
	m_FPSCounter = new prx::FPSCounter(*this);
	m_Layer2->add(m_FPSCounter);
	//m_Layer2->add(new prx::UIButton(hpm::vec3(100, 100, 0.0), 200, "Button"));
	//auto buttonID = prx::Resources::loadTexture("res/textures/button.png");
	//auto button = prx::Resources::getTexture(buttonID);
	//m_Layer2->add(new prx::Label("button", hpm::vec3(200, 200, 0), prx::Resources::getFont(prx::Resources::loadFont("res/fonts/BMKIRANGHAERANG-TTF.ttf", 60)), 0xffffffff));
	/*prx::Texture* bplr = prx::Resources::getTexture(prx::Resources::loadTexture("res/textures/button_play_released.png"));
	prx::Texture* bplp = prx::Resources::getTexture(prx::Resources::loadTexture("res/textures/button_play_pressed.png"));
	prx::Texture* bpr = prx::Resources::getTexture(prx::Resources::loadTexture("res/textures/button_pause_released.png"));
	prx::Texture* bpp = prx::Resources::getTexture(prx::Resources::loadTexture("res/textures/button_pause_pressed.png"));
	m_Ui = new prx::UILayer();
	auto button = new prx::UIButton(hpm::vec3(200, 300, 0.0), 100, bplp, bplr);
	auto button2 = new prx::UIButton(hpm::vec3(500, 300, 0.0), 100, bpp, bpr);
	std::cout << button->getID() << std::endl;
	std::cout << button2->getID() << std::endl;
	auto listener = new prx::event::ButtonListener(this);
	button->setOnClickListener(*listener);
	button2->setOnClickListener(*listener);
	m_Ui->add(button);
	m_Ui->add(button2);*/
	
}

void Game::tick() {
	m_FPSCounter->update();
	//std::cout << m_Window->getWidth() << std::endl;
	//std::cout << m_Window->getHeight() << std::endl;
	//m_Layer->setProjectionMatrix(hpm::mat4::ortho(0.0, m_Window->getWidth(), m_Window->getHeight(), 0.0, -10.0, 100.0));
	//m_Layer2->setProjectionMatrix(hpm::mat4::ortho(0.0, m_Window->getWidth(), m_Window->getHeight(), 0.0, -10.0, 100.0));
}

void Game::update() {
	//hpm::vec2 cursorPos = m_Window->getCursorPos();
	//cursorPos.y = m_Window->getHeight() - cursorPos.y;
	//std::cout << m_Window->getCursorPos().x << " " << m_Window->getCursorPos().y << std::endl;

	//m_Shader->bind();
	//m_Shader->setUniform("u_lightPos", cursorPos);
	if (m_Window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
		hero->playAnimation(aID3);
		return;
	}
	if (m_Window->isKeyHeld(GLFW_KEY_W)) {
		hero->setPosition(hpm::vec3(hero->getPosition().x, hero->getPosition().y + 3.0 , hero->getPosition().z));
		hero->loopAnimation(aID2);
	} else if (m_Window->isKeyHeld(GLFW_KEY_S)) {
		hero->setPosition(hpm::vec3(hero->getPosition().x, hero->getPosition().y - 3.0 , hero->getPosition().z));
		hero->loopAnimation(aID2);
	} else if (m_Window->isKeyHeld(GLFW_KEY_A)) {
		hero->setPosition(hpm::vec3(hero->getPosition().x - 5.0 , hero->getPosition().y, hero->getPosition().z));
		hero->loopAnimation(aID2);
		hero->reflect(true);
	} else if (m_Window->isKeyHeld(GLFW_KEY_D)) {
		hero->setPosition(hpm::vec3(hero->getPosition().x + 5.0 , hero->getPosition().y, hero->getPosition().z));
		hero->loopAnimation(aID2);
		hero->reflect(false);
	} //else
		//hero->loopAnimation(aID);
	

	//m_Ui->update();

}

void Game::render() {
	//if (m_Window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		
		//m_Sound->pause();

	//if (m_Window->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		//std::cout << "wow" << std::endl;
	//m_Ui->draw();
	//m_Layer->draw();
	m_Layer2->draw();
}
