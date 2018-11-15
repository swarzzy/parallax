#pragma once

#include <hypermath.h>
#include "../../Common.h"

namespace prx {
	class Light2D {
		PRX_DISALLOW_COPY_AND_MOVE(Light2D)
	private:
		hpm::vec2 m_Position;
		float	  m_Depth;
		unsigned  m_Color;
		float	  m_Brightness;
		float	  m_Radius;

	public:
		Light2D();
		Light2D(hpm::vec2 position, float depth, unsigned color, float brightness, float radius);
		virtual ~Light2D();

		inline void setPosition(hpm::vec2 position);
		inline void setPosition(float x, float y);
		inline void setDepth(float depth);
		inline void setColor(unsigned color);
		inline void setBrightness(float brightness);
		inline void setRadius(float radius);

		inline const hpm::vec2& getPosition() const;
		inline float getDepth() const;
		inline unsigned getColor() const;
		inline float getBrightness() const;
		inline float getRadius() const;
	};
}
#include "Light2D.inl"




