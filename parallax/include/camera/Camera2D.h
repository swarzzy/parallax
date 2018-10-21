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

	public:
		Camera2D();
		~Camera2D();

		inline static const hpm::vec2 defaultViewSpaceSize() noexcept;

		void init(float viewSpaceWidth = defaultViewSpaceWidth,
				  float viewSpaceHeight = defaultViewSpaceHeight);

		void update();

		inline const hpm::mat4& getProjectionMatrix() const noexcept;

		inline const hpm::vec2& getViewSpaceSize() const noexcept;
		inline const hpm::vec2& getCameraPosition() const noexcept;

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

	inline const hpm::vec2 Camera2D::defaultViewSpaceSize() noexcept {
		return hpm::vec2(defaultViewSpaceWidth, defaultViewSpaceHeight);
	}


	inline const hpm::mat4& Camera2D::getProjectionMatrix() const noexcept {
		return m_ProjectionMatrix;
	}
	
	inline const hpm::vec2& Camera2D::getViewSpaceSize() const noexcept {
		return hpm::vec2(m_ViewSpaceWidth, m_ViewSpaceHeight);
	}


	inline const hpm::vec2& Camera2D::getCameraPosition() const noexcept {
		return m_Position;
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
