#include "Game.h"

void Game::init() {
	parallaxInit("parallax", 600, 600, false, LogLevel::LOG_INFO, 0xff000000);

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
	m_FPSCounter->setPosition(4, 577);
	m_UPSCounter->setPosition(4, 555);
	m_FPSCounter->setParent(m_UILayer);
	m_UPSCounter->setParent(m_UILayer);

	
	m_Hero = m_Scene->createAnimation(100, 80, "res/textures/adventurer.sheet", "run", m_Layer);
	m_Hero->loopAnimation("run");
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
	
	Director::getInstance()->setCurrentScene("Scene");
	Director::getInstance()->playScene();
	m_HeroPos = hpm::vec2(0.0f);
}

void Game::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Game::update() {
	m_FPSCounter->setPosition(m_Scene->getCameraPosition() + hpm::vec2(4, 577));
	m_UPSCounter->setPosition(m_Scene->getCameraPosition() + hpm::vec2(4, 555));

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
		m_Hero->setPosition(m_HeroPos);
	//m_Scene->setCameraPosition(m_CameraPosition);
	Director::getInstance()->update();
}
	
void Game::render() {
	Director::getInstance()->render();
}

void Game::destroy() {
}
