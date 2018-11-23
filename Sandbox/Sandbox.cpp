#include "Sandbox.h"
#include "utils/imgui_widgets/ToggleButton.h"
#include "utils/imgui_widgets/SliderFloat.h"
#include "utils/imgui_widgets/SliderInt.h"
#include "renderer/DefferedRenderer2D.h"
#include "renderer/light/AmbientLight2D.h"

void Sandbox::init() {
	InitializeParallax({ "parallax", 800, 600, false, false }, RendererType::FORWARD_RENDERER, LogLevel::LOG_INFO);
	Window::getInstance()->setAspectRatio(800, 600);
	DefferedRenderer2D::initialize(hpm::mat4::identity());

	m_Sound = get_resource<Sound>("res/audio/test.ogg");
	m_Sound->init();
	m_Sound->loop();

	Director::getInstance()->createScene("Scene");
	m_Scene = Director::getInstance()->getScene("Scene");

	m_LevelLayer = m_Scene->createLayer(0);
	m_EntityLayer = m_Scene->createLayer(1);
	m_UILayer = m_Scene->createLayer(2);
	m_LevelGroup = m_Scene->createGroup(m_LevelLayer);

	auto HWall1 = m_Scene->createSprite(100, 100, "res/textures/level/wall_horizontal.png", m_LevelGroup);
	HWall1->setPosition(0, 500);
	auto HWall2 = m_Scene->createSprite(100, 100, "res/textures/level/wall_horizontal.png", m_LevelGroup);
	HWall2->setPosition(100, 500);
	auto HWall3 = m_Scene->createSprite(100, 100, "res/textures/level/wall_horizontal.png", m_LevelGroup);
	HWall3->setPosition(200, 500);
	auto HWall4 = m_Scene->createSprite(100, 100, "res/textures/level/wall_horizontal.png", m_LevelGroup);
	HWall4->setPosition(300, 500);
	auto HWall5 = m_Scene->createSprite(100, 100, "res/textures/level/wall_horizontal.png", m_LevelGroup);
	HWall5->setPosition(400, 500);
	auto VWall = m_Scene->createSprite(120, 120, "res/textures/level/wall_vert.png", m_LevelGroup);
	VWall->setPosition(0, 500);

	
	//m_Group->setParent(layer2);
	//m_Group->setPosition(400, 400);

	//m_Sun = m_Scene->createSprite(100, 100, "res/textures/sun.png");
	//m_Sun->setParent(m_Group);
	//m_Sun->setPosition(0, 0);


	//m_BluePlanet = m_Scene->createSprite(50, 50, "res/textures/blue_planet.png");
	//m_BluePlanet->setParent(m_Group);

	//m_BrownPlanet = m_Scene->createSprite(30, 30, "res/textures/brown_planet.png", m_BluePlanet);
	//m_BrownPlanet->setPosition(25, 25);

	m_FPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_UPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_MemCounter = m_Scene->createLabel("", 0xffffffff);
	m_FPSCounter->setPosition(4, 560);
	m_UPSCounter->setPosition(4, 537);
	m_MemCounter->setPosition(4, 515);
	m_FPSCounter->setParent(m_UILayer);
	m_UPSCounter->setParent(m_UILayer);
	m_MemCounter->setParent(m_UILayer);
	Director::getInstance()->addDebugMenuItem(new SliderFloat("Slider", &slider, 0.0f, 600.0f));
	Director::getInstance()->addDebugMenuItem(new SliderFloat("Slider2", &slider2, 0.0f, 600.0f));

	m_Hero = m_Scene->createAnimation(100, 80, "res/textures/adventurer.sheet", "run");
	m_Hero->loopAnimation("run");
	Director::getInstance()->setCurrentScene("Scene");
	Director::getInstance()->playScene();
	m_HeroPos = hpm::vec2(0.0f);

	btn = false;
	slider = 0.0f;
	slider2 = 0.0f;

	m_Light1 = std::make_shared<Light2D>(hpm::vec2(200, 250), 2, 0xffffffff, 1.0, 100);
	m_Light2 = std::make_shared<Light2D>(hpm::vec2(300, 350), 3, 0xff00ff00, 0.5, 80);
	m_Light3 = std::make_shared<Light2D>(hpm::vec2(100, 100), 0, 0xff0000ff, 1.0, 70);
	m_Light4 = std::make_shared<Light2D>(hpm::vec2(500, 500), 1, 0xffffffff, 1.0, 100);


	m_DebugMode = 0;

	Director::getInstance()->addDebugMenuItem(new ToggleButton("Debug light", &m_DebugMode));
	Director::getInstance()->addDebugMenuItem(new SliderFloat("c", &c, 0.0f, 200.0f));
	Director::getInstance()->addDebugMenuItem(new SliderFloat("l", &l, 0.0001f, 0.2f));
	Director::getInstance()->addDebugMenuItem(new SliderFloat("q", &q, 0.0000008f, 1.9f));


	DefferedRenderer2D::getInstance()->setAmbientLight(std::make_shared<AmbientLight2D>(0xffffffff, 1.0));
}

void Sandbox::tick() {
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
	m_MemCounter->getLabel().setText(std::to_string(internal::MemoryManager::getUsageMb()) + " mb");
	PRX_INFO(internal::MemoryManager::getUsageMb());
}

void Sandbox::update() {
	//m_Group->setPosition(slider, slider2);
	//m_FPSCounter->setPosition(m_Scene->getCameraPosition() + hpm::vec2(4, 577));
	//m_UPSCounter->setPosition(m_Scene->getCameraPosition() + hpm::vec2(4, 555));

	////m_Sun->setRotation(-getTime() / 80, -50);
	//->setRotation(getTime() / 40, 60);
	//m_BrownPlanet->setRotation(-getTime() / 10, 20);

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

	m_Light1->setRadius(c);
	DefferedRenderer2D::getInstance()->debugLights(m_DebugMode);

}

void Sandbox::render() {

	//auto light5 = std::make_shared<Light2D>(hpm::vec2(300, 300), 0, 0xffffffff, 0, 120);
	//auto light6 = std::make_shared<Light2D>(hpm::vec2(400, 400), 0, 0xffffffff, 0, 130);

	DefferedRenderer2D::getInstance()->submitLight(m_Light1);
	DefferedRenderer2D::getInstance()->submitLight(m_Light2);
	DefferedRenderer2D::getInstance()->submitLight(m_Light3);
	DefferedRenderer2D::getInstance()->submitLight(m_Light4);
	//DefferedRenderer2D::getInstance()->submitLight(light5);
	//DefferedRenderer2D::getInstance()->submitLight(light6);
	Director::getInstance()->render();
}

void Sandbox::destroy() {
}
