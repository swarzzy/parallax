#pragma once

#include <hypermath.h>
namespace prx {
	class Camera2D final {
	private:
		inline static const unsigned defaultViewSpaceWidth  = 1600;
		inline static const unsigned defaultViewSpaceHeight = 900;
	
	private:
		hpm::vec2 m_Position;
		hpm::mat4 m_ProjectionMatrix;
		float	  m_ViewSpaceWidth;
		float	  m_ViewSpaceHeight;
		bool	  m_NeedsUpdate;

		// Temporary solution
		float m_Near;
		float m_Far;

	public:
		Camera2D();
		~Camera2D();

		void init(hpm::vec2 position,
				  float near,
				  float far,
				  float viewSpaceWidth = defaultViewSpaceWidth,
				  float viewSpaceHeight = defaultViewSpaceHeight);

		void update();

		inline const hpm::mat4& getProjectionMatrix() const noexcept;

		inline const unsigned getViewSpaceWidth() const noexcept;
		inline const unsigned getViewSpaceHeight() const noexcept;

		inline void setCameraPosition(const hpm::vec2 position) noexcept;
		inline void setCameraPosition(float x, float y) noexcept;

		inline void setViewSpace(const hpm::vec2 viewSpaceSize) noexcept;
		inline void setViewSpace(float width, float height) noexcept;

	public:
		Camera2D(const Camera2D& other) = delete;
		Camera2D(const Camera2D&& other) = delete;
		Camera2D(Camera2D&& other) = delete;
		Camera2D& operator=(const Camera2D& other) = delete;
		Camera2D& operator=(const Camera2D&& other) = delete;
		Camera2D& operator=(Camera2D&& other) = delete;
	};

	inline const hpm::mat4& Camera2D::getProjectionMatrix() const noexcept {
		return m_ProjectionMatrix;
	}
	
	inline const unsigned Camera2D::getViewSpaceWidth() const noexcept {
		return m_ViewSpaceWidth;
	}

	inline const unsigned Camera2D::getViewSpaceHeight() const noexcept {
		return m_ViewSpaceHeight;
	}

	inline void Camera2D::setCameraPosition(const hpm::vec2 position) noexcept {
		m_Position = position;
		m_NeedsUpdate = true;
	}

	inline void Camera2D::setCameraPosition(float x, float y) noexcept {
		m_Position = hpm::vec2(x, y);
		m_NeedsUpdate = true;
	}

	inline void Camera2D::setViewSpace(const hpm::vec2 viewSpaceSize) noexcept {
		m_ViewSpaceWidth = viewSpaceSize.x;
		m_ViewSpaceHeight = viewSpaceSize.y;
		m_NeedsUpdate = true;
	}

	inline void Camera2D::setViewSpace(float width, float height) noexcept {
		m_ViewSpaceWidth = width;
		m_ViewSpaceHeight = height;
		m_NeedsUpdate = true;
	}
}
