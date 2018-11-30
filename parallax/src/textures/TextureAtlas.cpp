#include "TextureAtlas.h"

namespace prx {
	TextureAtlas::TextureAtlas(std::string_view filepath) 
		: TextureBase(filepath) 
	{
		load(filepath);
	}

	std::shared_ptr<TextureAtlas> TextureAtlas::create(std::string_view filepath) {
		// TODO: Custom allocator
		return nullptr; // std::make_shared<TextureAtlas>(filepath);
	}

	void TextureAtlas::load(std::string_view filepath) {
		
	}

	void TextureAtlas::parse(std::string_view filepath) {
		
	}
}
