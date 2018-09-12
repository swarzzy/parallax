#include "Window.h"
#include "utils/Color.h"
#include "utils/log/Log.h"
#include <iostream>
#include "shading/Shader.h"
#include "renderer/renderable/Sprite.h"
#include <random>
#include "renderer/layers/SceneLayer.h"
#include <filesystem>
#include "../../../hypermath/hypermath.h";
#include "renderer/renderable/Label.h"
#include "renderer/renderable/Group.h"
#include "resources/Resources.h"
#include <thread>
#include "renderer/renderable/FPSCounter.h"

int main(int argc, char *argv[]) {

	prx::Log::setLevel(prx::LOG_DEFAULT);
	prx::Window window("window", 800, 600);
	std::cout << argv[0] << std::endl;
	window.setClearColor(prx::Color::HEXtoGLVec("#000000"));
	prx::Resources::init();

	auto shader = prx::Resources::loadShader("res/shaders/default.vs", "res/shaders/default_light.fs");
	auto shaderNoLight = prx::Resources::loadShader("res/shaders/default.vs", "res/shaders/default_nolight.fs");

	prx::SceneLayer layer(shader);
	prx::SceneLayer layer2(shaderNoLight);

	std::knuth_b rand;
	std::uniform_int_distribution<unsigned int> colorDistrib(0, 255);

	hpm::vec4 color;
	float step = 0.1;
	int counter = 0;
	prx::Group* group = new prx::Group(hpm::mat4::identity());
	for (float x = 0; x < 800; x += 3) {// 3, 1.0
		for (float y = 0; y < 600; y += 3) {
			unsigned int color = 255 << 24 | colorDistrib(rand) << 16 | colorDistrib(rand) << 8 | colorDistrib(rand);
			group->add(new prx::Sprite(hpm::vec3(x, y, 1.0), hpm::vec2(2), color));
			step += 0.0001f;
			counter++;
		}
	}
	auto NotoSans = prx::Resources::loadFont("res/fonts/NotoSans-Regular.ttf", 80);
	auto AbrilFatface = prx::Resources::loadFont("res/fonts/AbrilFatface-Regular.ttf", 50);

	group->add(new prx::Label("Hello world!", hpm::vec3(200, 150, 0), NotoSans, 0xff568745));
	layer.add(group);
	layer2.add(new prx::Label("Text renderer!", hpm::vec3(20.0, 20.0, 0.0), AbrilFatface, 0xff3456ff));
	auto texture = prx::Resources::loadTexture("crate.png");
	layer2.add(new prx::Sprite(hpm::vec3(100, 100, 1.0), hpm::vec2(200, 200), texture));
	layer2.add(new prx::Sprite(hpm::vec3(300, 300, 1.0), hpm::vec2(200, 200), 0xffffffff));
	
	prx::FPSCounter* FPS = new prx::FPSCounter();
	layer2.add(FPS);

	while (!window.isClosed()) {
		window.clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);
		FPS->update();

		hpm::vec2 cursorPos = window.getCursorPos();
		cursorPos.y = 600 - cursorPos.y;
		
		shader->bind();
		shader->setUniform("u_lightPos", cursorPos);
		
		layer.draw();
		layer2.draw();
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			std::cout << "hello" << std::endl;
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			std::cout << "hello1" << std::endl;
		if (window.isMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
			std::cout << "bye" << std::endl;
		if (window.isMouseButtonHeld(GLFW_MOUSE_BUTTON_1))
			std::cout << "holded" << std::endl;
		window.update();
	}
	return 0;
}
