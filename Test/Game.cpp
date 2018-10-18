#include "Game.h"
#include <random>


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


void Game::init() {
	m_Window = parallaxInit("Parallax", 600, 600, false, prx::LOG_LEVEL::LOG_INFO, 0xff000000);

	m_Renderer = new ForwardRenderer2D(hpm::mat4::ortho(0, 600, 600, 0, -10, 10));
	m_CameraPosition = hpm::vec2(0.0);
	m_Sound = Resources::getSound(Resources::loadSound("test", "res/audio/test.ogg"));

	auto background = Resources::getTexture(Resources::loadTexture("res/textures/background.png"));
	auto sun = Resources::getTexture(Resources::loadTexture("res/textures/sun.png"));
	auto bluePlanet = Resources::getTexture(Resources::loadTexture("res/textures/blue_planet.png"));
	auto brownPlanet = Resources::getTexture(Resources::loadTexture("res/textures/brown_planet.png"));

	m_Scene = new Scene(m_Renderer);
	m_Scene->init();
	m_Layer = new Layer(0, m_Scene);
	m_UILayer = new Layer(1, m_Scene);
	m_Layer->init();
	m_UILayer->init();
	m_Background = new SpriteNode(0, 0, 850, 850, background, m_Layer);
	m_Background->setAnchorPoint(0.5, 0.5);
	m_Sun = new SpriteNode(0, 0, 150, 150 ,sun , m_Layer);
	m_Sun->setAnchorPoint(0.5, 0.5);
	m_BluePlanet = new SpriteNode(0, 0, 80, 80, bluePlanet, m_Layer);
	m_BluePlanet->setAnchorPoint(0.5, 0.5);
	m_BrownPlanet = new SpriteNode(0, 0, 30, 30, brownPlanet, m_BluePlanet);
	m_BrownPlanet->setAnchorPoint(0.5, 0.5);
	
	m_FPSCounter = new prx::LabelNode("", 0, 577, 0xffffffff, m_UILayer);
	m_UPSCounter = new prx::LabelNode("", 0, 555, 0xffffffff, m_UILayer);
	m_Sound->loop();

	prx::SpriteSheet* sheet = new prx::SpriteSheet("res/textures/hero_spritesheet.png", 8, 5);
	std::vector<unsigned int> mask = { 0,1,2,3,4,5, 6, 7 };
	std::vector<unsigned int> mask2 = { 8,9,10,11,12,13 };
	std::vector<unsigned int> mask3 = { 24, 25, 26, 27, 28, 29, 30 };
	int aID = sheet->addAnimation("1", mask);
	int aID2 = sheet->addAnimation("2", mask2);
	int aID3 = sheet->addAnimation("3", mask3);
	m_Hero = new AnimatedSpriteNode(100, 100, sheet, aID, m_Sun);
	m_Hero->loopAnimation(aID);
	m_Hero->setAnchorPoint(0.5, 0.5);
}

void Game::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	m_Background->setRotation(getTime() / 80);
	m_Sun->setRotation(-getTime() / 80);
	m_BluePlanet->setRotation(getTime() / 50, 120);
	m_BrownPlanet->setRotation(getTime() / 5, 45);
	m_Sun->setScale(std::fabs(std::sin(getTime() / 1000)) + 0.5);

	if (m_Window->isKeyHeld(PARALLAX_KEY_W))
		m_CameraPosition.y += 3.0;
	if (m_Window->isKeyHeld(PARALLAX_KEY_S))
		m_CameraPosition.y -= 3.0;
	if (m_Window->isKeyHeld(PARALLAX_KEY_A))
		m_CameraPosition.x -= 3.0;
	if (m_Window->isKeyHeld(PARALLAX_KEY_D))
		m_CameraPosition.x += 3.0;

	m_Scene->setCameraPosition(m_CameraPosition);
	m_Scene->update();
}
	
void Game::render() {
	m_Scene->present();
}
