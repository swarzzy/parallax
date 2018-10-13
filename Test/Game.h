#pragma once
#include "../parallax/include/Parallax.h"
#include "../parallax/include/renderer/layers/SceneLayer.h"
#include "../parallax/include/renderer/renderable/FPSCounter.h"
#include "../parallax/include/renderer/layers/UILayer.h"
#include "../parallax/include/scene/SpriteNode.h"
#include "../parallax/include/scene/Scene.h"
#include "../parallax/include/renderer/renderable/Label.h"
#include "../parallax/include/scene/LabelNode.h"

//#include "../parallax/include/shading/Shader.h"
using namespace prx;
class Game : public prx::Application {
public:
	Window* m_Window;
	Shader* m_Shader;
	SceneLayer* m_Layer;
	Sound* m_Sound;
	LabelNode* m_FPSCounter;
	LabelNode* m_UPSCounter;
	Scene* m_Scene;
	SpriteNode* m_Background;
	Renderer2D* m_Renderer;
	SpriteNode* m_Sun;
	SpriteNode* m_BluePlanet;
	SpriteNode* m_BrownPlanet;
	SpriteNode* m_Clouds;
public:
	Game(std::string_view path) {}
	~Game() {};

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
};
