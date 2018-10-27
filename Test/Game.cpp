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
	m_Window = parallaxInit("Parallax", 600, 600, false, prx::LOG_LEVEL::LOG_INFO, 0xff000000);
	Director::initialize();

	m_Sound = Resources::getSound(Resources::loadSound("test", "res/audio/test.ogg"));

	auto background = Resources::getTexture(Resources::loadTexture("res/textures/background.png"));
	auto sun = Resources::getTexture(Resources::loadTexture("res/textures/sun.png"));
	auto bluePlanet = Resources::getTexture(Resources::loadTexture("res/textures/blue_planet.png"));
	auto brownPlanet = Resources::getTexture(Resources::loadTexture("res/textures/brown_planet.png"));

	Director::getInstance()->createScene("Scene");
	m_Scene = Director::getInstance()->getScene("Scene");
	m_Layer = new Layer(0, m_Scene);
	{
//		auto h = get_resource<Texture>("res/textures/sun.png");
		ResourceManager::initialize();
		auto t = get_resource<Texture>("tex", std::string("res/textures/background.png"));
		auto r = get_resource<Texture>("tex", std::string("res/textures/brown_planet.png"));
		auto f = ResourceHandler<Texture>(std::move(r));
		
	}
	ResourceManager::getInstance()->collectGarbage();
	std::knuth_b rand;
	std::uniform_int_distribution<unsigned int> colorDistrib(0, 255);
	m_Group = new Group(m_Layer);
	m_Group->setPosition(300, 300);
	//m_Group->setAnchorPoint(0.5, 0.5);
	m_Group->enableVisibilityTest(false);
	//m_Group->setPosition(100, 100);
	m_Sun = new SpriteNode(0, 0, 150, 150, sun, m_Layer);
	//m_Sun->setAnchorPoint(0.5, 0.5);
	m_Sun->setVisibilityTestMode(VisibilityTestMode::QUAD);
	float step = 0.1;
	int counter = 0;
	for (float x = 0; x < 600; x += 3) {// 3, 1.0
		for (float y = 0; y < 600; y += 3) {
			unsigned int color = 255 << 24 | colorDistrib(rand) << 16 | colorDistrib(rand) << 8 | colorDistrib(rand);
			auto t = new SpriteNode(x, y, 1, 1, color, m_Group);
			step += 0.0001f;
			counter++;
		}
	}
	//m_Group->setPosition(20, 20);
	//std::cout << m_Layer->getDepth() << std::endl;
	//std::cout << m_Layer->getLocalMat().toString() << std::endl;
	//std::cout << m_Layer->getWorldMat().toString() << std::endl;
	m_UILayer = new Layer(1, m_Scene);
	////m_Scene->init();
	//auto t = new Layer(23,m_Layer);
	//m_Background = new SpriteNode(0, 0, 1850, 1850, background, t);
	//m_Background->setAnchorPoint(0.5, 0.5);
	
	//m_BluePlanet = new SpriteNode(0, 0, 80, 80, bluePlanet, t);
	//m_BluePlanet->setAnchorPoint(0.5, 0.5);
	//m_BrownPlanet = new SpriteNode(0, 0, 30, 30, brownPlanet, m_BluePlanet);
	//m_BrownPlanet->setAnchorPoint(0.5, 0.5);
	//
	m_FPSCounter = new prx::LabelNode("", 0, 577, 0xffffffff, m_UILayer);
	m_UPSCounter = new prx::LabelNode("", 0, 555, 0xffffffff, m_UILayer);
	//m_Sound->loop();

	//prx::SpriteSheet* sheet = new prx::SpriteSheet("res/textures/hero_spritesheet.png", 8, 5);
	//std::vector<unsigned int> mask = { 0,1,2,3,4,5, 6, 7 };
	//std::vector<unsigned int> mask2 = { 8,9,10,11,12,13 };
	//std::vector<unsigned int> mask3 = { 24, 25, 26, 27, 28, 29, 30 };
	//int aID = sheet->addAnimation("1", mask);
	//int aID2 = sheet->addAnimation("2", mask2);
	//int aID3 = sheet->addAnimation("3", mask3);
	////m_Hero = new AnimatedSpriteNode(100, 100, sheet, aID, m_Sun);
	////m_Hero->loopAnimation(aID);
	////m_Hero->setAnchorPoint(0.5, 0.5);
	//m_Scene->init();
	//std::cout << m_Scene->getID() << std::endl; //1
	//std::cout << m_Layer->getID() << std::endl; //2
	//std::cout << m_UILayer->getID() << std::endl;//3
	//std::cout << m_Background->getID() << std::endl;//4
	//std::cout << m_Sun->getID() << std::endl;//5
	//std::cout << m_BluePlanet->getID() << std::endl;//6
	//std::cout << m_BrownPlanet->getID() << std::endl;//7
	//m_Scene->removeChild(m_UILayer);
	Director::getInstance()->setCurrentScene("Scene");
	Director::getInstance()->initScene();
}

void Game::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	m_Group->setRotation(getTime() / 80, -300);
	/*m_Sun->setRotation(-getTime() / 80);
	m_BluePlanet->setRotation(getTime() / 50, 120);
	m_BrownPlanet->setRotation(getTime() / 5, 45);
	m_Sun->setScale(std::fabs(std::sin(getTime() / 1000)) + 0.5);*/

	if (m_Window->isKeyHeld(PARALLAX_KEY_W))
		m_CameraPosition.y += 3.1;
	if (m_Window->isKeyHeld(PARALLAX_KEY_S))
		m_CameraPosition.y -= 3.1;
	if (m_Window->isKeyHeld(PARALLAX_KEY_A))
		m_CameraPosition.x -= 3.0;
	if (m_Window->isKeyHeld(PARALLAX_KEY_D))
		m_CameraPosition.x += 3.0;
	static int depth = 0;
	static bool hide = false;
	static bool hidesp = false;
	static bool freeze = false;
	if (m_Window->isKeyPressed(PARALLAX_KEY_SPACE))
		hide = !hide;
	if (m_Window->isKeyPressed(PARALLAX_KEY_H))
		hidesp = !hidesp;
	if (m_Window->isKeyPressed(PARALLAX_KEY_F))
		freeze = !freeze;
	m_Sun->hide(hide);
	m_Group->hide(hidesp);
	m_Group->freeze(freeze);

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
	
	//std::cout << m_Scene->getCameraPosition().toString() << std::endl;
	//std::cout << m_Scene->getViewSize().toString() << std::endl;
	//std::cout << m_Layer->getWorldMat().toString() << std::endl;
	Director::getInstance()->update();
}
	
void Game::render() {
	Director::getInstance()->draw();
}
