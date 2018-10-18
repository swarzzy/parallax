#include "TransformComponent2D.h"
namespace prx {
	
	inline const hpm::mat3& TransformComponent2D::getWorldMat() const noexcept {
		return m_WorldMat;
	}

	inline const hpm::mat3& TransformComponent2D::getLocalMat() const noexcept {
		return m_LocalMat;
	}

	inline const hpm::mat3& TransformComponent2D::getAnchorMat() const noexcept {
		return m_AnchorMat;
	}

	inline const hpm::vec2& TransformComponent2D::getPosition() const noexcept {
		return m_Position;
	}

	inline const hpm::vec2& TransformComponent2D::getAnchorPoint() const noexcept {
		return m_AnchorPoint;
	}

	inline float TransformComponent2D::getScale() const noexcept {
		return m_Scale;
	}

	inline float TransformComponent2D::getRotationAngle() const noexcept {
		return m_RotationAngle;
	}

	inline float TransformComponent2D::getRotationRadius() const noexcept {
		return m_RotationRadius;
	}

	inline void TransformComponent2D::setWorldMat(const hpm::mat3 & matrix) noexcept {
		m_WorldMat = matrix;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setAnchorMat(const hpm::mat3 & matrix) noexcept {
		m_AnchorMat = matrix;
	}

	inline void TransformComponent2D::setLocalMat(const hpm::mat3 & matrix) noexcept {
		m_LocalMat = matrix;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setPosition(const hpm::vec2 & position) noexcept {
		m_Position = position;
		m_LocalUpdate = true;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setPosition(float x, float y) noexcept {
		m_Position = hpm::vec2(x, y);
		m_LocalUpdate = true;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setScale(float scale) noexcept {
		m_Scale = scale;
		m_LocalUpdate = true;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setRotation(float angle) noexcept {
		m_RotationAngle = angle;
		m_LocalUpdate = true;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setRotation(float angle, float radius) noexcept {
		m_RotationAngle = angle;
		m_RotationRadius = radius;
		m_LocalUpdate = true;
		m_WorldUpdate = true;
	}

	inline void TransformComponent2D::setAnchorPoint(hpm::vec2 anchorPoint) noexcept {
		m_AnchorPoint = anchorPoint;
		m_AnchorUpdate = true;
	}

	inline void TransformComponent2D::setAnchorPoint(float x, float y) noexcept {
		m_AnchorPoint = hpm::vec2(x, y);
		m_AnchorUpdate = true;
	}
}