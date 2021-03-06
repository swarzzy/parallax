#pragma once
#include "../../Common.h"
#include <hypermath.h>

namespace prx {
	class TransformComponent2D {
	private:
		hpm::mat3	m_LocalMat;
		hpm::mat3	m_WorldMat;
		hpm::mat3	m_AnchorMat;

		hpm::vec2	m_Position;
		float		m_Scale;
		float		m_RotationAngle;
		float		m_RotationRadius;
		hpm::vec2	m_Size;
		hpm::vec2	m_AnchorPoint;

		bool m_LocalUpdate;
		bool m_WorldUpdate;
		bool m_AnchorUpdate;

		bool m_Initialized;

	public:

		PRX_DISALLOW_COPY_AND_MOVE(TransformComponent2D)

		TransformComponent2D();
		~TransformComponent2D();

		void init();
		void update();
		// Clear local and world matrix
		void destroy();

		//TransformComponent2D clone() const;

		inline const hpm::mat3& getWorldMat() const noexcept;
		inline const hpm::mat3& getLocalMat() const noexcept;
		inline const hpm::mat3& getAnchorMat() const noexcept;

		inline const hpm::vec2& getPosition() const noexcept;
		inline const hpm::vec2& getSize() const noexcept;
		inline const hpm::vec2& getAnchorPoint() const noexcept;
		inline float getScale() const noexcept;
		inline float getRotationAngle() const noexcept;
		inline float getRotationRadius() const noexcept;

		// TODO: extract transformation components from matrices
		inline void setWorldMat(const hpm::mat3& matrix) noexcept;
		inline void setAnchorMat(const hpm::mat3& matrix) noexcept;
		inline void setLocalMat(const hpm::mat3& matrix) noexcept;

		inline void setPosition(const hpm::vec2& position) noexcept;
		inline void setSize(const hpm::vec2& size) noexcept;
		inline void setSize(float width, float height) noexcept;
		inline void setPosition(float x, float y) noexcept;
		inline void setScale(float scale) noexcept;
		inline void setRotation(float angle) noexcept;
		inline void setRotation(float angle, float radius) noexcept;
		inline void setAnchorPoint(hpm::vec2 anchorPoint) noexcept;
		inline void setAnchorPoint(float x, float y) noexcept;
	};
}
#include "TransformComponent2D.inl"
