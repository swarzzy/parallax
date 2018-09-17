#include <renderer/layers/SceneLayer.h>
#include <renderer/BatchRenderer2D.h>
#include <resources/Resources.h>

namespace prx {
	SceneLayer::SceneLayer(Shader* shader)
		: Layer(new BatchRenderer2D, shader, hpm::mat4::ortho(0.0, 800.0, 600.0, 0.0, -10.0, 100.0)) {
	}

	SceneLayer::~SceneLayer() {
	}
}
