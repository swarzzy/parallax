#pragma once
#include "Light2DBase.h"

namespace siv {
	class PerlinNoise;
}

namespace prx {
	class TorchLight2D final : public Light2DBase {
		PRX_DISALLOW_COPY_AND_MOVE(TorchLight2D)
	private:
		inline static siv::PerlinNoise* s_PerlinNoseGenerator = nullptr;
		// Needs that only to delete noise generator at the time
		inline size_t static s_GlobalTorchLightCounter = 0;

		float		m_FlickeringSpeed;
		hpm::vec2	m_FlickeringRange;
	public:
		TorchLight2D();
		TorchLight2D(hpm::vec2 position, float depth, color_t color, float radius, hpm::vec2 flickeringRange, float flickeringSpeed);
		~TorchLight2D();

		void setFlickeringSpeed(float speed);
		void setFlickeringRange(const hpm::vec2 range);

		float getFlickeringSpeed() const;
		const hpm::vec2& getFlickeringRange() const;

		void update() override;
	};
}
