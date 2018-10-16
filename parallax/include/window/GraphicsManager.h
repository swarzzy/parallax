#pragma once

namespace prx {
	class GraphicsManager {
	public:
		friend class Window;
	private:
		unsigned m_ViweportHeight;
		unsigned m_ViewportWidth;
	public:
		inline void setViewPortSize(unsigned width, unsigned height);
	};

	inline void GraphicsManager::setViewPortSize(unsigned width, unsigned height) {
		
	}
}
