#pragma once


#include "../parallax/include/Parallax.h"
#include "../parallax/include/renderer/layers/SceneLayer.h"
#include "../parallax/include/renderer/renderable/FPSCounter.h"
//#include "../parallax/include/shading/Shader.h"

class Game : public prx::Application {
private:
	prx::Window* m_Window;
	prx::Shader* m_Shader;
	prx::Shader* m_ShaderUI;
	prx::Sound*  m_Sound;
	prx::SceneLayer* m_Layer;
	prx::SceneLayer* m_Layer2;
	prx::FPSCounter* m_FPSCounter;
public:
	Game() {};
	~Game() {};

	void init() override;
	void tick() override;
	void update() override;
	void render() override;
};
