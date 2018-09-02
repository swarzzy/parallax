#include "Window.h"
#include "utils/Color.h"
#include "utils/log/Log.h"
#include <iostream>
#include "shading/Shader.h"
#include "renderer/renderable/Sprite.h"
#include <random>
#include "utils/Timer.h"
#include "renderer/layers/SceneLayer.h"
#include <filesystem>
#include "../../../hypermath/hypermath.h";
#include "renderer/BatchRenderer2D.h"


int main(int argc, char *argv[]) {

	prx::Log::setLevel(prx::LOG_DEFAULT);
	prx::Window window("window", 800, 600);
	std::cout << argv[0] << std::endl;
	window.setClearColor(prx::Color::HEXtoGLVec("#ffffff"));

	auto shader = new prx::Shader("res/shaders/simple.vs", "res/shaders/simple.fs");

	prx::SceneLayer layer(shader);
	prx::BatchRenderer2D renderer;

	std::knuth_b rand;
	std::uniform_real_distribution<double> colorDistrib(0.0, 1.0);

	hpm::vec4 color;
	float step = 0.1;
	int counter = 0;
	for (float x = 0; x < 800; x += 3) {// 3, 1.0
		for (float y = 0; y < 600; y += 3) {
			color = hpm::vec4(colorDistrib(rand), colorDistrib(rand), colorDistrib(rand), 1.0);
			layer.add(new prx::Sprite(hpm::vec3(x, y, 1.0), hpm::vec2(2), color));
			step += 0.0001f;
			counter++;
		}
	}

	std::cout << counter << std::endl;

	while (!window.isClosed()) {
		window.clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);

		hpm::vec2 cursorPos = window.getCursorPos();
		cursorPos.y = 600 - cursorPos.y;
		
		shader->bind();
		shader->setUniform("u_lightPos", cursorPos);
		renderer.begin();
		renderer.drawString("sd", hpm::vec3(0.0), hpm::vec4(0.0));
		renderer.end();
		renderer.flush();
		//layer.draw();

		window.update();
	}
	delete shader;
	return 0;
}
