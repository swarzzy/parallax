
#include "Window.h"
#include "utils/Color.h"
#include "utils/log/Log.h"
#include <iostream>
#include "shading/Shader.h"
#include <vector>
#include <string>
#include "resources/Resources.h"
#include "renderer/SimpleRenderer2D.h"
#include "renderer/BatchRenderer2D.h"
#include "renderer/renderable/Sprite.h"
#include <random>
#include "utils/Timer.h"
#include "renderer/layers/SceneLayer.h"
#include "renderer/renderable/Group.h"
#include "shading/Texture.h"
#include <filesystem>
#include <algorithm>
#include "../../../hypermath/hypermath.h";
#include <ft2build.h>
#include "freetype-gl.h"

#define PARALLAX_MAIN 1
std::vector<std::string> getTexPaths(std::string_view path) {
	std::vector<std::string> vec;
	for (auto& p : std::filesystem::directory_iterator(path)) {
		std::string name = p.path().string();
		int pos = name.find_last_of('\\');
		name.erase(0, pos);
		std::string result = "res\\textures";
		result += name;
		vec.push_back(result);
	}
	return vec;
}
#if PARALLAX_MAIN

int main(int argc, char *argv[]) {
	prx::Log::setLevel(prx::LOG_DEFAULT);
	prx::Window window("window", 800, 600);
	std::cout << argv[0] << std::endl;
	window.setClearColor(prx::Color::HEXtoGLVec("#000000"));

	auto shader = new prx::Shader("res/shaders/simple.vs", "res/shaders/simple.fs");

	prx::SceneLayer layer(shader);

	prx::BatchRenderer2D renderer;

	prx::Sprite sprite(hpm::vec3(0.5, 0.6, 1.0), hpm::vec2(200), hpm::vec4(1.0));

	/*std::string dir = argv[0];
	int p = dir.find_last_of('\\');
	dir.erase(p, dir.size());
	dir += "\\res\\textures";

	auto paths = getTexPaths(dir);
	for (auto elem : paths)
		std::cout << elem << std::endl;*/

	std::knuth_b rand;
	std::uniform_real_distribution<double> distribX(0.0, 700.0);
	std::uniform_real_distribution<double> distribY(0.0, 500.0);
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

	//prx::Timer timer;
	while (!window.isClosed()) {
		//timer.reset();
		window.clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);

		hpm::vec2 cursorPos = window.getCursorPos();
		cursorPos.y = 600 - cursorPos.y;
		
		shader->bind();
		shader->setUniform("u_lightPos", cursorPos);

		//layer.draw();
		renderer.begin();
		//renderer.submit(sprite);
		renderer.drawString("", hpm::vec3(0.0), hpm::vec4(0.0));
		renderer.end();
		renderer.flush();

		window.update();
		//std::cout << timer.elapsed() << std::endl;
		
	}
	delete shader;
	return 0;
}
#endif

