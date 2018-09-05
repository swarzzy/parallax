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
#include "renderer/renderable/Label.h"
#include "renderer/renderable/Group.h"
#include "resources/Resources.h"


int main(int argc, char *argv[]) {

	prx::Log::setLevel(prx::LOG_DEFAULT);
	prx::Window window("window", 800, 600);
	std::cout << argv[0] << std::endl;
	window.setClearColor(prx::Color::HEXtoGLVec("#000000"));
	prx::Resources::init();

	auto shader = prx::Resources::loadShader("default_light", "res/shaders/default.vs", "res/shaders/default_light.fs");
	auto shaderNoLight = prx::Resources::loadShader("default_nolight", "res/shaders/default.vs", "res/shaders/default_nolight.fs");

	prx::SceneLayer layer(shader);
	prx::SceneLayer layer2(shaderNoLight);

	std::knuth_b rand;
	std::uniform_real_distribution<double> colorDistrib(0.0, 1.0);

	hpm::vec4 color;
	float step = 0.1;
	int counter = 0;
	prx::Group* group = new prx::Group(hpm::mat4::identity());
	for (float x = 0; x < 800; x += 3) {// 3, 1.0
		for (float y = 0; y < 600; y += 3) {
			color = hpm::vec4(colorDistrib(rand), colorDistrib(rand), colorDistrib(rand), 1.0);
			group->add(new prx::Sprite(hpm::vec3(x, y, 1.0), hpm::vec2(2), color));
			step += 0.0001f;
			counter++;
		}
	}
	auto font = prx::Resources::loadFont("NotoSans-Regular", "res/fonts/NotoSans-Regular.ttf", 80);
	auto font2 = *prx::Resources::loadFont("AbrilFatface-Regular", "res/fonts/AbrilFatface-Regular.ttf", 50);

	group->add(new prx::Label("Hello world!", hpm::vec3(200, 150, 0), *prx::Resources::getFont("NotoSans-Regular"), hpm::vec4(prx::Color::HEXtoGLVec("#c62828"), 1.0)));
	layer.add(group);
	layer2.add(new prx::Label("Text renderer!", hpm::vec3(20.0, 20.0, 0.0), *prx::Resources::getFont("AbrilFatface-Regular"), hpm::vec4(prx::Color::HEXtoGLVec("#ffa000"), 1.0)));

	while (!window.isClosed()) {
		window.clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);

		hpm::vec2 cursorPos = window.getCursorPos();
		cursorPos.y = 600 - cursorPos.y;
		
		shader->bind();
		shader->setUniform("u_lightPos", cursorPos);
		
		layer.draw();
		layer2.draw();

		window.update();
	}
	prx::Resources::ternimate();
	return 0;
}
