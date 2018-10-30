#include "Game.h"
#include <random>
#include "../parallax/include/resources/ResourceHandler.h"

#include "../parallax/include/renderer/renderable/Group.h"
#include "../parallax/include/textures/TextureAtlas.h"
#include "../parallax/include/renderer/renderable/Sprite.h"
#include "../parallax/include/textures/Texture.h"
#include <experimental/filesystem>
#include <filesystem>
#include "../parallax/include/renderer/layers/UILayer.h"
#include "../parallax/include/renderer/renderable/UI/UIButtonBase.h"
#include "../parallax/include/renderer/renderable/UI/UIGroup.h"
#include "../parallax/include/renderer/renderable/UI/UIButton.h"
#include "../parallax/include/textures/SpriteSheet.h"
#include "../parallax/include/renderer/FrameBuffer2D.h"
#include "../parallax/include/scene/LabelNode.h"
#include "../parallax/include/renderer/ForwardRenderer2D.h"
#include <complex>
#include "../parallax/include/scene/Group.h"
#include "../parallax/include/resources/ResourceManager.h"


void Game::init() {
	parallaxInit("Parallax", 600, 600, false, prx::LOG_LEVEL::LOG_INFO, 0xff000000);

	m_Sound = get_resource<Sound>("res/audio/test.ogg");
	m_Sound->init();
	m_Sound->loop();

	Director::getInstance()->createScene("Scene");
	Director::getInstance()->createScene("Scene2");
	m_Scene = Director::getInstance()->getScene("Scene");
	m_Scene2 = Director::getInstance()->getScene("Scene2");

	m_Layer = m_Scene->createLayer(0);
	m_UILayer = m_Scene->createLayer(1);
	auto layer2 = m_Scene2->createLayer(0);

	auto sprite = m_Scene2->createSprite(100, 100, "res/textures/5mb.jpg", layer2);
	sprite->setPosition(300, 300);

	m_Sun = m_Scene->createSprite(100, 100, "res/textures/sun.png");
	m_Sun->setParent(m_Layer);
	m_Sun->setPosition(5, 5);

	m_Group = m_Scene->createGroup();
	m_Group->setParent(m_Sun);
	m_Group->setPosition(50, 50);

	m_BluePlanet = m_Scene->createSprite(50, 50, "res/textures/blue_planet.png");
	m_BluePlanet->setParent(m_Sun);
	m_BluePlanet->setPosition(50, 50);

	m_BrownPlanet = m_Scene->createSprite(60, 60, "res/textures/brown_planet.png", m_BluePlanet);
	m_BrownPlanet->setPosition(60, 60);
	
	m_FPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_UPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_FPSCounter->setPosition(4, 577);
	m_UPSCounter->setPosition(4, 555);
	m_FPSCounter->setParent(m_UILayer);
	m_UPSCounter->setParent(m_UILayer);
	
	//std::knuth_b rand;
	//std::uniform_int_distribution<unsigned int> colorDistrib(0, 255);
	//m_Group = new Group(m_Layer);
	//m_Group->setPosition(300, 300);
	////m_Group->setAnchorPoint(0.5, 0.5);
	//m_Group->enableVisibilityTest(false);
	////m_Group->setPosition(100, 100);
	
	//float step = 0.1;
	//int counter = 0;
	//for (float x = 0; x < 600; x += 3) {// 3, 1.0
	//	for (float y = 0; y < 600; y += 3) {
	//		unsigned int color = 255 << 24 | colorDistrib(rand) << 16 | colorDistrib(rand) << 8 | colorDistrib(rand);
	//		auto t = new SpriteNode(x, y, 1, 1, color, m_Group);
	//		step += 0.0001f;
	//		counter++;
	//	}
	//}
	//m_Group->setPosition(20, 20);

	m_Window = Window::getInstance();
	
	Director::getInstance()->setCurrentScene("Scene");
	Director::getInstance()->playScene();
}

void Game::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	//m_Group->setRotation(getTime() / 80, -300);
	m_Sun->setRotation(-getTime() / 80);
	//m_BluePlanet->setRotation(getTime() / 25, 50);
	//m_BrownPlanet->setRotation(getTime() / 5, 45);
	//m_Sun->setScale(std::fabs(std::sin(getTime() / 1000)) + 0.5);*/

	if (m_Window->isKeyHeld(PARALLAX_KEY_W))
		m_CameraPosition.y += 3.1;
	if (m_Window->isKeyHeld(PARALLAX_KEY_S))
		m_CameraPosition.y -= 3.1;
	if (m_Window->isKeyHeld(PARALLAX_KEY_A))
		m_CameraPosition.x -= 3.0;
	if (m_Window->isKeyHeld(PARALLAX_KEY_D))
		m_CameraPosition.x += 3.0;
	static int depth = 0;
	static bool hide = true;
	static bool hidesp = false;
	static bool freeze = false;
	if (m_Window->isKeyPressed(PARALLAX_KEY_SPACE)) {
		hide = !hide;
		hide ? Director::getInstance()->setCurrentScene("Scene") : Director::getInstance()->setCurrentScene("Scene2");
		Director::getInstance()->playScene();
	}
	if (m_Window->isKeyPressed(PARALLAX_KEY_H)) {
		delete_node(m_BluePlanet);
		m_BluePlanet = nullptr;
	}
	if (m_Window->isKeyPressed(PARALLAX_KEY_F)) {
		Director::getInstance()->deleteScene("Scene2");
		ResourceManager::getInstance()->collectGarbage();
	}
	if (m_Window->isKeyPressed(PARALLAX_KEY_P)) {
		m_Sound.free();
	}
	//m_Group->hide(hidesp);
	//m_Group->freeze(freeze);
	//m_Sun->setSize(500, 500);

	//m_Group->setScale(m_CameraPosition.y);
	/*if (m_Window->isKeyPressed(PARALLAX_KEY_T)) {
		depth++;
		m_Layer->setDepth(depth);
	}
	if (m_Window->isKeyPressed(PARALLAX_KEY_G)) {
		depth--;
		m_Layer->setDepth(depth);
	}*/

	

	m_Scene->setCameraPosition(m_CameraPosition);
	Director::getInstance()->update();
}
	
void Game::render() {
	Director::getInstance()->render();
}
