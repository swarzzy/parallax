#include "SpriteSheet.h"
#include "../resources/ImageLoader.h"
#include "../utils/error/UninitializedResourceUsedException.h"
#include "../resources/FileReader.h"
#include "../scene/Node.h"

#include "../ext/rapidxml/rapidxml.hpp"

namespace prx {

	SpriteSheet::SpriteSheet(std::string_view path)
		: TextureBase(""),
		m_Columns(0),
		m_Rows(0),
		m_Tiles(0),
		m_UV(nullptr),
		m_ReflectedUV(nullptr),
		m_Reflected(0),
		m_CurrentUVBuffer(nullptr),
		m_XMLPath(path)
	{
		parseXML();
	}

	SpriteSheet::SpriteSheet(std::string_view path, unsigned int columns, unsigned int rows, bool reflected)
		: TextureBase(path), 
		  m_Columns(columns), 
		  m_Rows(rows), 
		  m_Tiles(columns * rows),
		  m_UV(nullptr),
		  m_ReflectedUV(nullptr),
		  m_Reflected(reflected),
		  m_CurrentUVBuffer(nullptr),
		  m_XMLPath("")
	{}

	SpriteSheet::~SpriteSheet() {
		GLCall(glDeleteTextures(1, &m_TexID));
		delete[] m_UV;
		delete[] m_ReflectedUV;
	}

	void SpriteSheet::initInternal() {
		m_UV = new UV[m_Tiles];
		m_ReflectedUV = new UV[m_Tiles];
		m_CurrentUVBuffer = m_UV;
		
		loadFromFile();

		// Calculate tex coords
		unsigned int spriteWidth = m_Width / m_Columns;
		unsigned int spriteHeight = m_Height / m_Rows;

		int coordCounter = m_Tiles;

		for (int j = m_Height - spriteHeight; j >= 0; j -= spriteHeight) {
			for (unsigned int i = 0; i < m_Width; i += spriteWidth) {
				float leftBottomX = static_cast<float>(i) / m_Width;
				float leftBottomY = static_cast<float>(j) / m_Height;

				m_UV[m_Tiles - coordCounter].lbX = leftBottomX;
				m_UV[m_Tiles - coordCounter].lbY = leftBottomY;
				m_ReflectedUV[m_Tiles - coordCounter].rbX = leftBottomX;
				m_ReflectedUV[m_Tiles - coordCounter].rbY = leftBottomY;


				m_UV[m_Tiles - coordCounter].ltX = leftBottomX;
				m_UV[m_Tiles - coordCounter].ltY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;
				m_ReflectedUV[m_Tiles - coordCounter].rtX = leftBottomX;
				m_ReflectedUV[m_Tiles - coordCounter].rtY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;

				m_UV[m_Tiles - coordCounter].rtX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_UV[m_Tiles - coordCounter].rtY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;
				m_ReflectedUV[m_Tiles - coordCounter].ltX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_ReflectedUV[m_Tiles - coordCounter].ltY = leftBottomY + static_cast<float>(spriteHeight) / m_Height;

				m_UV[m_Tiles - coordCounter].rbX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_UV[m_Tiles - coordCounter].rbY = leftBottomY;
				m_ReflectedUV[m_Tiles - coordCounter].lbX = leftBottomX + static_cast<float>(spriteWidth) / m_Width;
				m_ReflectedUV[m_Tiles - coordCounter].lbY = leftBottomY;

				coordCounter--;
			}
		}
	}

	void SpriteSheet::destroyInternal() {
		delete[] m_UV;
		delete[] m_ReflectedUV;

		GLCall(glDeleteTextures(1, &m_TexID));
	}

	void SpriteSheet::parseXML() {
		using namespace rapidxml;
		
		std::string file;
		try {
			file = read_file_as_text(m_XMLPath);
		} catch(FileReadException& e) {
			PRX_ERROR("SPRITE SHEET: ", e.what());
			m_Columns = 1;
			m_Rows = 1;
			m_Tiles = 1;
			return;
		}
		
		xml_document<> doc;
		xml_node<>* rootNode;
		
		doc.parse<0>(const_cast<char*>(file.c_str()));
		
		rootNode = doc.first_node("spritesheet");

		m_FilePath = rootNode->first_attribute("file")->value();
		m_Columns = std::stoi(rootNode->first_attribute("columns")->value());
		m_Rows = std::stoi(rootNode->first_attribute("rows")->value());

		m_Tiles = m_Columns * m_Rows;
	
		std::vector<unsigned> tiles;
		for (xml_node<>* animationNode = rootNode->first_node("animation"); animationNode; animationNode = animationNode->next_sibling()) {
			const char* name = animationNode->first_attribute("name")->value();
			float duration = std::stof(animationNode->first_attribute("duration")->value());
			for (xml_node<> * tileNode = animationNode->first_node("tile"); tileNode; tileNode = tileNode->next_sibling())
			{
				unsigned tile = std::stoi(tileNode->value());
				if (tile > m_Tiles)
					PRX_ERROR("SPRITE SHEET: Wrong tile number in spritesheet XML markup");
				else {
					tiles.push_back(tile);
				}
			}
			addAnimation(name, tiles, duration);
			tiles.clear();
		}
	}

	int SpriteSheet::addAnimation(std::string_view name, const std::vector<unsigned int>& mask, float duration) {
		if (mask.size() > m_Tiles) {
			PRX_ERROR("SPRITE SHEET: Mask size mismatch.\n->SHEET PATH: ", getFilePath());
			return -1;
		}
		m_Animations.emplace_back(name, mask.size(), mask, duration);
		auto id = static_cast<unsigned>(m_Animations.size() - 1);
		m_AnimationList[std::string(name)] = id;
		return id;
	}

	void SpriteSheet::setDuration(std::string_view animationName, float duration) {
		try {
			Animation& animation = m_Animations.at(m_AnimationList.find(std::string(animationName))->second);
			animation.setDuration(duration);
		} catch (std::out_of_range& e) {
			PRX_ERROR("SPRITE SHEET: Failded to set animation duration. Wrong animation name.\n-> NAME: ", animationName,
						"\n-> INFO: ", e.what());
		}
	}

	const UV* SpriteSheet::getTexCoords(unsigned int animationID) const {
		if (isInitialized()) {
			auto currentTime = Application::getInstance()->getTime();
			try {
				const Animation& animation = m_Animations.at(animationID);

				if (currentTime - animation.timeElapsed > animation.timePerState) {
					animation.currentState == animation.framesNumber - 1 ?
						animation.currentState = 0 : animation.currentState++;
					// TODO: time variables types
					animation.timeElapsed = static_cast<__int64>(currentTime);
				}
				return &m_CurrentUVBuffer[animation.UVIndices[animation.currentState]];

			} catch (std::out_of_range& e) {
				PRX_ERROR("SPRITE SHEET: Failed to get UVs. Wrong animation ID.\n-> ANIM_ID: ", animationID,
							"\n ->SHEET PATH: ", getFilePath(), "\n-> INFO:", e.what());
				return nullptr;
			}
		} else {
			PRX_ERROR("SPRITE SHEET: Using uninitialized spritesheet.\n-> PATH: ", getFilePath());
			return nullptr;
		}
	}

	const UV* SpriteSheet::getTexCoords(const std::string& animationName) const {
		if (isInitialized()) {
			auto currentTime = Application::getInstance()->getTime();
			try {
				const Animation& animation = m_Animations.at(m_AnimationList.find(animationName.c_str())->second);

				if (currentTime - animation.timeElapsed > animation.timePerState) {
					animation.currentState == animation.framesNumber - 1 ?
						animation.currentState = 0 : animation.currentState++;
					// TODO: time variables types
					animation.timeElapsed = static_cast<__int64>(currentTime);
				}
				return &m_CurrentUVBuffer[animation.UVIndices[animation.currentState]];

			}
			catch (std::out_of_range& e) {
				PRX_ERROR("SPRITE SHEET: Failed to get UVs. Wrong animation ID.\n-> NAME: ", animationName,
					"\n ->SHEET PATH: ", getFilePath(), "\n-> INFO: ", e.what());
				return nullptr;
			}
		}
		else {
			PRX_ERROR("SPRITE SHEET: Using uninitialized spritesheet.\n-> PATH: ", getFilePath());
			return nullptr;
		}
	}

	void SpriteSheet::resetAnimations() {
		for (auto& animation : m_Animations)
			animation.currentState = 0;
	}

	void SpriteSheet::reflect(bool reflect) {
		if (m_Reflected && !reflect) {
			m_Reflected = false;
			m_CurrentUVBuffer = m_UV;
		} else if (!m_Reflected && reflect) {
			m_Reflected = true;
			m_CurrentUVBuffer = m_ReflectedUV;
		}
	}
}
