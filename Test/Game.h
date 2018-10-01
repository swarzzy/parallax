#pragma once


#include "../parallax/include/Parallax.h"
#include "../parallax/include/renderer/layers/SceneLayer.h"
#include "../parallax/include/renderer/renderable/FPSCounter.h"
#include "../parallax/include/renderer/layers/UILayer.h"
#include "../parallax/include/renderer/renderable/AnimatedSprite.h"

//#include "../parallax/include/shading/Shader.h"

class Game : public prx::Application {
public:
	prx::Window* m_Window;
	prx::Shader* m_Shader;
	prx::Shader* m_ShaderUI;
	prx::Sound*  m_Sound;
	prx::SceneLayer* m_Layer;
	prx::SceneLayer* m_Layer2;
	prx::Label* m_FPSCounter;
	prx::Label* m_UPSCounter;
	std::string m_Path;
	prx::UILayer* m_Ui;
	unsigned aID;
	unsigned aID2;
	unsigned aID3;
	prx::AnimatedSprite* hero;
	prx::Sprite* sp;
public:
	Game(std::string_view path) 
		: m_Path(path) {};
	~Game() {};

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
};
