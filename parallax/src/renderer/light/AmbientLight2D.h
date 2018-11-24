#pragma once

#include "Light2DBase.h"

namespace prx {
	class AmbientLight2D final : public Light2DBase {
		PRX_DISALLOW_COPY_AND_MOVE(AmbientLight2D)

	public:
		AmbientLight2D()
			: Light2DBase()
		{}

		AmbientLight2D(color_t color, float intensity)
			: Light2DBase({ 0.0f, 0.0f }, 0.0f, color, intensity, 0.0f)
		{}

		void update() override {}
	};
}