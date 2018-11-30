#pragma once
#define HOLD1N(x) private: float x; public:

namespace prx::DFR2D {

	// Common DefferedRenderer2D properties
	inline const size_t		MAX_SPRITES					= 10000;
	inline const size_t		MAX_LIGHTS					= 30;
	inline const float		LIGHT_VOLUME_CIRCLE_STEP	= 30.0f;
}

namespace prx::internal::DFR2D {
	// DefferedRenderer2D pipeline data structs

	struct DFR2DVertex {
		hpm::vec2	coords;
		float		depth;
		hpm::vec2	UVs;
		float		texID;
		float		normalID;
		color_t		color;
	};

	struct DFR2DLightVertex {
		hpm::vec2	coords;
	};

	struct DFR2DLightProperties {
		hpm::vec3 color;	// 0N
		float radius;
		hpm::vec2 position; // 4N
		float intensity;
		float depth;
							// 8N
	};

	struct DFR2DLightVolumeProperties {
		hpm::vec2 position;
		float radius;
	};
}