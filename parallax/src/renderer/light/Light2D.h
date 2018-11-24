#pragma once

#include "Light2DBase.h"

namespace prx {
	class Light2D final : public Light2DBase {
		PRX_DISALLOW_COPY_AND_MOVE(Light2D)
	public:
		Light2D()
			: Light2DBase()
		{}

		Light2D(hpm::vec2 position, float depth, color_t color, float intensity, float radius)
			: Light2DBase(position, depth, color, intensity, radius)
		{}

		void update() override {}
	};
}