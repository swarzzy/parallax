#include "window/Window.h"
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
#include "audio/Sound.h"

#define PARALLAX_GRAPHICS_TEST
//#define PARALLAX_SOUND_TEST

#ifdef PARALLAX_GRAPHICS_TEST
int main(int argc, char *argv[]) {
	
	prx::Log::setLevel(prx::LOG_DEFAULT);
	prx::Window window("window", 800, 600);
	std::cout << argv[0] << std::endl;
	window.setClearColor(0xff000000);
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
	group->setTransformationMatrix(hpm::mat4::rotation(30, hpm::vec3(0, 0, 1)));
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
	auto text = new prx::Label("Text renderer!", hpm::vec3(20.0, 20.0, 0.0), AbrilFatface, 0xff3456ff);
	text->setText("sfasdf");
	prx::FPSCounter counterf;

	layer2.add(text);
	auto texture = prx::Resources::loadTexture("res/textures/crate.png");
	auto texture2 = prx::Resources::loadTexture("res/textures/test.png");
	auto texSprite = new prx::Sprite(hpm::vec3(100, 100, 1.0), hpm::vec2(200, 200), texture);
	layer2.add(texSprite);
	auto sprite = new prx::Sprite(hpm::vec3(300, 300, 1.0), hpm::vec2(200, 200), 0xffffffff);
	layer2.add(sprite);
	sprite->setColor(0xff654743);
	texSprite->setTexture(texture2);
	texSprite->setPosition(hpm::vec3(400, 300, 1));
	texSprite->setSize(hpm::vec2(100, 600));
	prx::FPSCounter* FPS = new prx::FPSCounter();
	layer2.add(FPS);
	auto sound = prx::Resources::loadSound("res/audio/test.ogg");
	
	
	while (!window.isClosed()) {
		window.clear(prx::COLOR_BUFFER | prx::DEPTH_BUFFER);
		FPS->update();

		hpm::vec2 cursorPos = window.getCursorPos();
		cursorPos.y = 600 - cursorPos.y;
		
		shader->bind();
		shader->setUniform("u_lightPos", cursorPos);
		
		layer.draw();
		layer2.draw();
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_2)) {;
		sound->stop();
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
			sound->loop();
		if (window.isMouseButtonReleased(GLFW_MOUSE_BUTTON_1))
			sound->pause();
		if (window.isMouseButtonHeld(GLFW_MOUSE_BUTTON_1))
			std::cout << "holded" << std::endl;
			window.update();
	}
	prx::Resources::terminate();
	return 0;
}
#endif

#ifdef PARALLAX_SOUND_TEST
#include "../dependencies/gorilla-audio/ga.h"
#include "../dependencies/gorilla-audio/gau.h"
#include <stdio.h>

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
	gc_int32* flag = (gc_int32*)(in_context);
	*flag = 1;
	ga_handle_destroy(in_handle);
}

int main() {
	gau_Manager* mgr;
	ga_Mixer* mixer;
	ga_Sound* sound;
	ga_Handle* handle;
	gau_SampleSourceLoop* loopSrc = 0;
	gau_SampleSourceLoop** pLoopSrc = &loopSrc;
	gc_int32 loop = 1;
	gc_int32 quit = 0;

	/* Initialize library + manager */
	gc_initialize(0);
	mgr = gau_manager_create();
	mixer = gau_manager_mixer(mgr);

	/* Create and play shared sound */
	if (!loop)
		pLoopSrc = 0;
	sound = gau_load_sound_file("res/audio/shotgun.wav", "wav");
	handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);

	/* Bounded mix/queue/dispatch loop */
	bool flag = true;
	while (!quit)
	{
		if (flag) {
			ga_handle_play(handle);
			flag = false;
		}
		gau_manager_update(mgr);
		printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
		gc_thread_sleep(1);
	}

	/* Clean up sound */
	ga_sound_release(sound);

	/* Clean up library + manager */
	gau_manager_destroy(mgr);
	gc_shutdown();

	return 0;
}
#endif
