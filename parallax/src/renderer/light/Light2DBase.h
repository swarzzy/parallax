#pragma once

#include <hypermath.h>
#include "../../Common.h"
#include "../DefferedRenderer2D_Properties.h"

namespace prx {
	class Light2DBase {
		PRX_DISALLOW_COPY_AND_MOVE(Light2DBase)
	protected:
		internal::DFR2D::DFR2DLightProperties		m_LightProperties;
		internal::DFR2D::DFR2DLightVolumeProperties m_LightVolumeProperties;

		Light2DBase();
		Light2DBase(hpm::vec2 position, float depth, color_t color, float intensity, float radius);

	public:
		virtual ~Light2DBase();

		virtual void update() = 0;

		inline void setPosition(hpm::vec2 position);
		inline void setPosition(float x, float y);
		inline void setDepth(float depth);
		inline void setColor(color_t color);
		inline void setIntensity(float intensity);
		inline void setRadius(float radius);

		inline const hpm::vec2& getPosition() const;
		inline float getDepth() const;
		inline color_t getColor() const;
		inline const hpm::vec3& getColor3f() const;
		inline float getRadius() const;
		inline float getVolumeRadius() const;
		inline float getIntensity() const;

		inline const internal::DFR2D::DFR2DLightProperties& getLightProperties() const;
		inline const internal::DFR2D::DFR2DLightVolumeProperties& getLightVolumeProperties() const;

	private:
		float calcVolumeRadius();
	};
}
#include "Light2DBase.inl"