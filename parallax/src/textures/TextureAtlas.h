#pragma once
#include "TextureBase.h"

namespace prx {
	class TextureAtlas final : public TextureBase {
		PRX_DISALLOW_COPY_AND_MOVE(TextureAtlas)
	private:
		struct AtlasNode {
			uint id;
			const char name[10];
		};

		std::vector<AtlasNode> m_Nodes;

		explicit TextureAtlas(std::string_view filepath);
	public:
		static std::shared_ptr<TextureAtlas> create(std::string_view filepath);
		~TextureAtlas();

		const float* getUV(uint id);
		const float* getUV(std::string_view name);
		uint getID(std::string_view name);

	private:
		void load(std::string_view filepath);
		void parse(std::string_view filepath);
	};
}
