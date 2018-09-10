#pragma once
#ifndef _SCENE_LAYER_H_
#define _SCENE_LAYER_H__

#include "Layer.h"

namespace prx {
	class SceneLayer : public Layer {
	public:
		SceneLayer(ResourceHandler<Shader> shader);
		~SceneLayer();
	};
}
#endif

