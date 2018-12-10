#include "Sandbox.h"
#include "utils/imgui_widgets/ToggleButton.h"
#include "utils/imgui_widgets/SliderFloat.h"
#include "utils/imgui_widgets/SliderInt.h"
#include "renderer/DefferedRenderer2D.h"
#include "renderer/light/AmbientLight2D.h"
#include "renderer/DFR2DMetrics.h"

void Sandbox::init() {
	InitializeParallax({ "parallax", 800, 600, false, true }, RendererType::DEFFERED_RENDERER, LogLevel::LOG_INFO);
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

	

	auto floor = m_Scene->createSprite(800, 600, "res/textures/level/floor.png", m_LevelGroup);
	floor->getSprite().setWrapMode(SpriteWrapMode::TEXTURE_WRAPPING_BOTH_DIR);
	floor->setPosition(0.0, 0.0);

	auto HWall1 = m_Scene->createSprite(800, 100, "res/textures/level/wall_h.png", "res/textures/level/wall_h_normal.png",  m_LevelGroup);
	HWall1->getSprite().setWrapMode(SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL);
	HWall1->setPosition(0, 500);

	auto VWall1 = m_Scene->createSprite(100, 800, "res/textures/level/wall_v.png", m_LevelGroup);
	VWall1->getSprite().setWrapMode(SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL);
	VWall1->setPosition(0, 33);

	auto VWall2 = m_Scene->createSprite(100, 800, "res/textures/level/wall_v.png", m_LevelGroup);
	VWall2->getSprite().setWrapMode(SpriteWrapMode::TEXTURE_WRAPPING_VERTICAL);
	VWall2->setPosition(790, 33);

	auto HWall2 = m_Scene->createSprite(800, 100, "res/textures/level/wall_h.png", m_LevelGroup);
	HWall2->getSprite().setWrapMode(SpriteWrapMode::TEXTURE_WRAPPING_HORIZONTAL);
	HWall2->setPosition(0, -57);

	auto brick = m_Scene->createSprite(600, 600, "res/textures/level/brickwall.jpg", "res/textures/level/brickwall_normal.jpg", m_LevelGroup);
	brick->setPosition(200, 200);
	
	auto rock = m_Scene->createSprite(600, 600, "res/textures/level/slate_diff.jpg", "res/textures/level/slate_norm.jpg", m_LevelGroup);
	rock->setPosition(0, 0);

	m_FPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_UPSCounter = m_Scene->createLabel("", 0xffffffff);
	m_RendererMetrics = m_Scene->createLabel("", FontManager::getInstance()->getDefault(10), 0xffffffff);
	m_FPSCounter->setPosition(4, 560);
	m_UPSCounter->setPosition(4, 537);
	m_RendererMetrics->setPosition(4, 515);
	m_FPSCounter->setParent(m_UILayer);
	m_UPSCounter->setParent(m_UILayer);
	m_RendererMetrics->setParent(m_UILayer);
	Director::getInstance()->addDebugMenuItem(new SliderFloat("Slider", &slider, 0.0f, 600.0f));
	Director::getInstance()->addDebugMenuItem(new SliderFloat("Slider2", &slider2, 0.0f, 600.0f));

	m_Hero = m_Scene->createAnimation(100, 80, "res/textures/adventurer.sheet", "run", m_LevelLayer);
	m_Hero->loopAnimation("run");
	Director::getInstance()->setCurrentScene("Scene");
	Director::getInstance()->playScene();
	m_HeroPos = hpm::vec2(0.0f);

	btn = false;
	slider = 0.0f;
	slider2 = 0.0f;

	m_Light1 = std::make_shared<Light2D>(hpm::vec2(200, 250), 2, 0xffffffff, 1.0, 300);
	m_Light2 = std::make_shared<Light2D>(hpm::vec2(300, 350), 3, 0xff00ff00, 0.5, 80);
	m_Light3 = std::make_shared<Light2D>(hpm::vec2(100, 100), 0, 0xff0000ff, 1.0, 70);
	m_Light4 = std::make_shared<Light2D>(hpm::vec2(500, 500), 1, 0xffffffff, 1.0, 100);


	m_DebugMode = 0;

	Director::getInstance()->addDebugMenuItem(new ToggleButton("Debug light", &m_DebugMode));
	//Director::getInstance()->addDebugMenuItem(new SliderFloat("c", &c, 0.0f, 800.0f));
	//Director::getInstance()->addDebugMenuItem(new SliderFloat("l", &l, 0.0f, 600.0f));
	//Director::getInstance()->addDebugMenuItem(new SliderFloat("q", &q, 0.0000008f, 1.9f));


	DefferedRenderer2D::getInstance()->setAmbientLight(std::make_shared<AmbientLight2D>(0xffffffff, 0.4));
}

void Sandbox::tick() {
	//PRX_INFO(DFR2DMetrics::getFormatted());
	//m_RendererMetrics->getLabel().setText(DFR2DMetrics::getFormatted());
	m_UPSCounter->getLabel().setText(std::to_string(getUPS()) + " ups");
	m_FPSCounter->getLabel().setText(std::to_string(getFPS()) + " fps");
}

void Sandbox::update() {
	m_PrevHeroPos = m_HeroPos;
	m_LevelGroup->enableVisibilityTest(false);

	if (Window::getInstance()->isMouseButtonHeld(PARALLAX_MOUSE_BUTTON_1))
		m_Hero->playAnimation("attack_1");
	else {
		if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_W)) {
			m_HeroPos.y += 0.3;
		}
		if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_S)) {
			m_HeroPos.y -= 0.3;
		}
		if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_A)) {
			m_HeroPos.x -= 0.3;
			m_Hero->reflect(true);
		}
		if (Window::getInstance()->isKeyHeld(PARALLAX_KEY_D)) {
			m_HeroPos.x += 0.3;
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

	//m_Hero->setPosition(m_HeroPos);
	Director::getInstance()->update();
	m_Scene->setCameraPosition(m_HeroPos);

	static float fontScale = 1.0;

	if (Window::getInstance()->isKeyPressed(PARALLAX_KEY_UP)) {
		fontScale += 0.3;
		FontManager::getInstance()->reload(fontScale);
	}

	if (Window::getInstance()->isKeyPressed(PARALLAX_KEY_DOWN)) {
		fontScale -= 0.3;
		FontManager::getInstance()->reload(fontScale);
	}

	m_Light1->setPosition(Window::getInstance()->getCursorPos().x + m_HeroPos.x, Window::getInstance()->getCursorPos().y + m_HeroPos.y);
	DefferedRenderer2D::getInstance()->debugLights(m_DebugMode);

}

void Sandbox::render() {
	DFR2DMetrics::newFrame();
	DefferedRenderer2D::getInstance()->submitLight(m_Light1);
	DefferedRenderer2D::getInstance()->submitLight(m_Light2);
	DefferedRenderer2D::getInstance()->submitLight(m_Light3);
	DefferedRenderer2D::getInstance()->submitLight(m_Light4);
	
	Director::getInstance()->render();
}

void Sandbox::destroy() {
}
