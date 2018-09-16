#pragma once

#include "Parallax.h"
#include "renderer/layers/Layer.h"
#include "renderer/layers/SceneLayer.h"
#include "renderer/renderable/FPSCounter.h"

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
