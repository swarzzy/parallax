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

	unsigned int shaderNoLightID = prx::Resources::loadShader("UI_shader", "res/shaders/default.vs", "res/shaders/default_nolight.fs");
	m_ShaderUI = prx::Resources::getShader(shaderNoLightID);
	m_Layer2 = new prx::SceneLayer(m_ShaderUI);
	
	unsigned int soundID = prx::Resources::loadSound("test", "res/audio/test.ogg");
	m_Sound = prx::Resources::getSound(soundID);
	
	m_Sound->play();


	prx::SpriteSheet* sheet = new prx::SpriteSheet("res/textures/hero_spritesheet.png", 8, 5);
	std::vector<unsigned int> mask = { 0,1,2,3,4,5, 6, 7 };
	std::vector<unsigned int> mask2 = { 8,9,10,11,12,13 };
	std::vector<unsigned int> mask3 = { 24, 25, 26, 27, 28, 29, 30 };
	aID = sheet->addAnimation("1", mask);
	aID2 = sheet->addAnimation("2", mask2);
	aID3 = sheet->addAnimation("3", mask3);
	hero = new prx::AnimatedSprite(hpm::vec3(0.0, 0.0, 0.0), hpm::vec2(100), sheet, aID);
	//hero->loopAnimation(aID);
	m_Layer2->add(hero);
	m_Layer2->add(new prx::Label("WASD to move", hpm::vec3(400, 500, 0.0), prx::Resources::getFont(prx::RESOURCES_DEFAULT_FONT_ID), 0xffffffff));

	m_FPSCounter = new prx::Label("", 10, 570, 0, prx::Resources::getFont(prx::RESOURCES_DEFAULT_FONT_ID), 0xffffffff);
	m_Layer2->add(m_FPSCounter);

	m_UPSCounter = new prx::Label("", 10, 540, 0, prx::Resources::getFont(prx::RESOURCES_DEFAULT_FONT_ID), 0xffffffff);
	m_Layer2->add(m_UPSCounter);

	prx::Log::message(prx::LOG_LEVEL::LOG_ERROR, "lol", std::string(" log works "), 87);
	prx::Log::message(prx::LOG_LEVEL::LOG_WARN, "asdasdasdas");
}

void Game::tick() {
	m_UPSCounter->setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	if (m_Window->isMouseButtonPressed(PARALLAX_MOUSE_BUTTON_1)) {
		hero->playAnimation(aID3);
		
		return;
	}
	else {
		if (m_Window->isKeyHeld(PARALLAX_KEY_W)) {
			hero->setPosition(hpm::vec3(hero->getPosition().x, hero->getPosition().y + 3.0, hero->getPosition().z));
			hero->loopAnimation(aID2);
		}
		else if (m_Window->isKeyHeld(PARALLAX_KEY_S)) {
			hero->setPosition(hpm::vec3(hero->getPosition().x, hero->getPosition().y - 3.0, hero->getPosition().z));
			hero->loopAnimation(aID2);
		}
		else if (m_Window->isKeyHeld(PARALLAX_KEY_A)) {
			hero->setPosition(hpm::vec3(hero->getPosition().x - 5.0, hero->getPosition().y, hero->getPosition().z));
			hero->loopAnimation(aID2);
			hero->reflect(true);
		}
		else if (m_Window->isKeyHeld(PARALLAX_KEY_D)) {
			hero->setPosition(hpm::vec3(hero->getPosition().x + 5.0, hero->getPosition().y, hero->getPosition().z));
			hero->loopAnimation(aID2);
			hero->reflect(false);
		}
		else
		{
			hero->loopAnimation(aID);
		}
	}
		//else
			//hero->loopAnimation(aID);
	}
	

	//m_Ui->update();

void Game::render() {
	m_Layer2->draw();
}
