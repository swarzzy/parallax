#include "Game.h"

void Game::init() {
	parallaxInit("parallax", 600, 600, false, LogLevel::LOG_INFO, 0xff000000, true);
	Window::getInstance()->setAspectRatio(1, 1);

	m_Sound = get_resource<Sound>("res/audio/test.ogg");
	m_Sound->init();
	m_Sound->loop();

	Director::getInstance()->createScene("Scene");
	Director::getInstance()->createScene("Scene2");
	m_Scene = Director::getInstance()->getScene("Scene");

	m_Layer = m_Scene->createLayer(0);
	m_UILayer = m_Scene->createLayer(1);

	m_Group = m_Scene->createGroup();
	m_Group->setParent(m_Layer);
	m_Group->setPosition(400, 400);

	m_Sun = m_Scene->createSprite(100, 100, "res/textures/sun.png");
	m_Sun->setParent(m_Group);
	m_Sun->setPosition(0, 0);

	m_BluePlanet = m_Scene->createSprite(50, 50, "res/textures/blue_planet.png");
	m_BluePlanet->setParent(m_Group);

	m_BrownPlanet = m_Scene->createSprite(30, 30, "res/textures/brown_planet.png", m_BluePlanet);
	m_BrownPlanet->setPosition(25, 25);
	
	m_FPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_UPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_FPSCounter->setPosition(4, 560);
	m_UPSCounter->setPosition(4, 537);
	m_FPSCounter->setParent(m_UILayer);
	m_UPSCounter->setParent(m_UILayer);

	m_Hero = m_Scene->createAnimation(100, 80, "res/textures/adventurer.sheet", "run", m_Layer);
	m_Hero->loopAnimation("run");
	Director::getInstance()->setCurrentScene("Scene");
	Director::getInstance()->playScene();
	m_HeroPos = hpm::vec2(0.0f);
}

void Game::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	
	//m_FPSCounter->setPosition(m_Scene->getCameraPosition() + hpm::vec2(4, 577));
	//m_UPSCounter->setPosition(m_Scene->getCameraPosition() + hpm::vec2(4, 555));

	m_Sun->setRotation(-getTime() / 80, -50);
	m_BluePlanet->setRotation(getTime() / 40, 60);
	m_BrownPlanet->setRotation(-getTime() / 10, 20);

	m_PrevHeroPos = m_HeroPos;

	if (Window::getInstance()->isMouseButtonHeld(PARALLAX_MOUSE_BUTTON_1))
		m_Hero->playAnimation("attack_1");
	else {
	if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_W)) {
		m_HeroPos.y += 3.0;
	}
	if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_S)) {
		m_HeroPos.y -= 3.0;
	}
	if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_A)) {
		m_HeroPos.x -= 3.0;
		m_Hero->reflect(true);
	}
	if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_D)) {
		m_HeroPos.x += 3.0;
		m_Hero->reflect(false);
	}
	
		if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_LEFT_SHIFT))
			m_Hero->playAnimation("rollup");
		else
			if (m_HeroPos != m_PrevHeroPos) {
				m_Hero->loopAnimation("run");
			}
			else {
				m_Hero->loopAnimation("idle");
			}
	}

	static bool flag = true;
	if (Window::getInstance()->isKeyPressed(PARALLAX_KEY_TAB)) {
		flag = !flag;
		Director::getInstance()->enableDebugLayer(!flag);
	}

		m_Hero->setPosition(m_HeroPos);
	Director::getInstance()->update();

	static float fontScale = 1.0;

	if (Window::getInstance()->isKeyPressed(PARALLAX_KEY_UP)) {
		fontScale += 0.3;
		FontManager::getInstance()->reload(fontScale);
	}

	if (Window::getInstance()->isKeyPressed(PARALLAX_KEY_DOWN)) {
		fontScale -= 0.3;
		FontManager::getInstance()->reload(fontScale);
	}
	
	
}
	
void Game::render() {
	Director::getInstance()->render();
}

void Game::destroy() {
}
