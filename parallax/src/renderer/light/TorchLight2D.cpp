#include "TorchLight2D.h"
#include "../ext/PerlinNoise/PerlinNoise.hpp"
#include "../../Application/Application.h"

namespace prx {
	TorchLight2D::TorchLight2D()
		: Light2DBase()
		, m_FlickeringSpeed(0.0f)
		, m_FlickeringRange(0.0f, 1.0f)
	{
		if (!s_PerlinNoseGenerator)
			s_PerlinNoseGenerator = new siv::PerlinNoise();
		s_GlobalTorchLightCounter++;
	}

	TorchLight2D::TorchLight2D(hpm::vec2 position, float depth, color_t color, float radius, hpm::vec2 flickeringRange, float flickeringSpeed)
		: Light2DBase(position, depth, color, flickeringRange.y, radius)
		, m_FlickeringSpeed(flickeringSpeed)
		, m_FlickeringRange(flickeringRange)
	{
		if (!s_PerlinNoseGenerator)
			s_PerlinNoseGenerator = new siv::PerlinNoise();
		s_GlobalTorchLightCounter++;
	}

	TorchLight2D::~TorchLight2D() {
		s_GlobalTorchLightCounter--;
		if (s_GlobalTorchLightCounter == 0) {
			delete s_PerlinNoseGenerator;
			s_PerlinNoseGenerator = nullptr;
		}
	}

	void TorchLight2D::setFlickeringSpeed(float speed) {
		m_FlickeringSpeed = speed;
	}

	void TorchLight2D::setFlickeringRange(const hpm::vec2 range) {
		m_FlickeringRange = range;
	}

	float TorchLight2D::getFlickeringSpeed() const {
		return m_FlickeringSpeed;
	}

	const hpm::vec2& TorchLight2D::getFlickeringRange() const {
		return m_FlickeringRange;
	}

	void TorchLight2D::update() {
		if (m_FlickeringSpeed == 0.0f) m_LightProperties.intensity = m_FlickeringRange.y;
		float val = static_cast<float>(s_PerlinNoseGenerator->octaveNoise0_1(Application::getInstance()->getTime() / (100 / m_FlickeringSpeed), 5));
		m_LightProperties.intensity = hpm::map(val, 0.0f, 1.0f, m_FlickeringRange.x, m_FlickeringRange.y);
	}
}
