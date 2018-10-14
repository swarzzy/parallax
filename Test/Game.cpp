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
#include "../parallax/include/renderer/renderable/UI/UIGroup.h"
#include "../parallax/include/renderer/renderable/UI/UIButton.h"
#include "../parallax/include/textures/SpriteSheet.h"
#include "../parallax/include/renderer/FrameBuffer2D.h"
#include "../parallax/include/scene/LabelNode.h"


void Game::init() {
	m_Window = parallaxInit("Parallax", 600, 600, false, prx::LOG_LEVEL::LOG_INFO, 0xff000000);

	m_Shader = ShaderManager::getShader(ShaderManager::loadShader(ShaderType::DEFAULT));
	
	m_Layer = new SceneLayer(m_Shader);
	m_Layer->setProjectionMatrix(hpm::mat4::ortho(0, 600, 600, 0, -10, 10));
	m_Renderer = m_Layer->getRenderer();
	
	m_Sound = Resources::getSound(Resources::loadSound("test", "res/audio/test.ogg"));

	auto background = Resources::getTexture(Resources::loadTexture("res/textures/background.png"));
	auto sun = Resources::getTexture(Resources::loadTexture("res/textures/sun.png"));
	auto bluePlanet = Resources::getTexture(Resources::loadTexture("res/textures/blue_planet.png"));
	auto brownPlanet = Resources::getTexture(Resources::loadTexture("res/textures/brown_planet.png"));
	//auto clouds = Resources::getTexture(Resources::loadTexture("res/textures/clouds.png"));

	m_Scene = new Scene(m_Layer->getRenderer());
	m_Background = new SpriteNode(-425, -425, 0.0, 850, 850, background, m_Renderer, m_Scene);
	//m_Clouds = new SpriteNode(-300, -300, 0.0, 600, 600, clouds, m_Renderer, m_Scene);
	m_Sun = new SpriteNode(-150 /2, -150 /2, 1, 150, 150 ,sun ,m_Renderer, m_Scene);
	m_BluePlanet = new SpriteNode(0, 0, 0, 80, 80, bluePlanet, m_Renderer, m_Scene);
	m_BrownPlanet = new SpriteNode(0, 0, 0, 30, 30, brownPlanet, m_Renderer, m_BluePlanet);
	
	m_FPSCounter = new prx::LabelNode("", -290, 270, 0xffffffff, m_Renderer, m_Scene);
	m_UPSCounter = new prx::LabelNode("", -290, 240, 0xffffffff, m_Renderer, m_Scene);
	m_Sound->loop();

	prx::SpriteSheet* sheet = new prx::SpriteSheet("res/textures/hero_spritesheet.png", 8, 5);
	std::vector<unsigned int> mask = { 0,1,2,3,4,5, 6, 7 };
	std::vector<unsigned int> mask2 = { 8,9,10,11,12,13 };
	std::vector<unsigned int> mask3 = { 24, 25, 26, 27, 28, 29, 30 };
	int aID = sheet->addAnimation("1", mask);
	int aID2 = sheet->addAnimation("2", mask2);
	int aID3 = sheet->addAnimation("3", mask3);
	m_Hero = new AnimatedSprite(100, 100, sheet, aID);
	m_Hero->loopAnimation(aID);
}

void Game::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	m_Scene->update();
	m_Sun->setTransform(hpm::mat3::rotation(-getTime() / 80) * hpm::mat3::translation(-150 / 2, -150 / 2));
	m_Background->setTransform( hpm::mat3::rotation(getTime() / 100) * hpm::mat3::translation(-425, -425));
	m_BluePlanet->setTransform(hpm::mat3::rotation(getTime() / 50) * hpm::mat3::translation(80, 80));
	m_BrownPlanet->setTransform(hpm::mat3::translation(40, 40) * hpm::mat3::rotation(getTime() / 6) * hpm::mat3::translation(30, 30));
}
	
void Game::render() {
	m_Shader->bind();
	m_Renderer->begin();

	m_Scene->draw();
	m_Hero->submit(m_Renderer, hpm::mat3::identity());

	m_Renderer->end();
	m_Renderer->flush();
	m_Shader->unbind();
	
	m_Layer->draw();
}
