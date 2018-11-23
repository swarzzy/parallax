#pragma once
#include "../../Common.h"

namespace prx {
	class AmbientLight2D final {
		PRX_DISALLOW_COPY_AND_MOVE(AmbientLight2D)
	private:
		color_t m_Color;
		float	m_Intensity;

	public:
		AmbientLight2D(color_t color, float intensity)
			: m_Color(color)
			, m_Intensity(intensity)
		{}

		inline void setColor(color_t color) {
			m_Color = color;
		}

		inline void setIntensity(float intensity) {
			m_Intensity = intensity;
		}

		inline color_t getColor() const {
			return m_Color;
		}

		inline float getIntensity() const {
			return m_Intensity;
		}
	};
}