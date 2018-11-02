#pragma once
#include "../parallax/include/Parallax.h"
#include "../parallax/include/scene/SpriteNode.h"
#include "../parallax/include/scene/Scene.h"
#include "../parallax/include/renderer/renderable/Label.h"
#include "../parallax/include/scene/LabelNode.h"
#include "../parallax/include/renderer/renderable/AnimatedSprite.h"
#include "../parallax/include/camera/Camera2D.h"
#include "../parallax/include/scene/Layer.h"
#include "../parallax/include/scene/AnimatedSpriteNode.h"
#include "../parallax/include/scene/Group.h"
#include "../parallax/include/scene/Director.h"

//#include "../parallax/include/shading/Shader.h"
using namespace prx;
class Game : public prx::Application {
public:
	ResourceHandler<Sound> m_Sound;
	LabelNode* m_FPSCounter;
	LabelNode* m_UPSCounter;
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
public:
	Game(std::string_view path) : m_Sound(nullptr) {}
	~Game() {};

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
	void destroy() override;
};
