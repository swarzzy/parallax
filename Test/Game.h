#pragma once
#include <parallax.h>
#include <hypermath.h>

using namespace prx;
class Game : public prx::Application {
public:
	ResourceHandler<Sound> m_Sound;
	LabelNode* m_FPSCounter;
	LabelNode* m_UPSCounter;
	LabelNode* m_MemCounter;
	Scene* m_Scene;
	SpriteNode* m_Sun;
	SpriteNode* m_BluePlanet;
	SpriteNode* m_BrownPlanet;
	AnimatedSpriteNode* m_Hero;
	Camera2D* m_Camera;
	hpm::vec2 m_CameraPosition;
	Layer* m_Layer;
	Layer* m_UILayer;
	Group* m_Group;
	hpm::vec2 m_HeroPos;
	hpm::vec2 m_PrevHeroPos;
	Layer* IMLayer;
	Font* m_Font;
	bool btn;
	float slider;
	float slider2;
	std::shared_ptr<Light2D> m_Light1;
	std::shared_ptr<Light2D> m_Light2;
	std::shared_ptr<Light2D> m_Light3;
	std::shared_ptr<Light2D> m_Light4;

	float c;
	float l;
	float q;

	bool m_DebugMode;
public:
	Game(std::string_view path) : m_Sound(nullptr) {}
	~Game() {};

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
	void destroy() override;
};
