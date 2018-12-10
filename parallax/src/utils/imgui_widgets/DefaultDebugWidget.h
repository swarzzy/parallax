#pragma once

#include "ImGUIWidget.h"
#include "../../Application/Application.h"
#include "../../window/Window.h"
#include "../../ext/imgui/imgui.h"
#include "../../renderer/DFR2DMetrics.h"

namespace prx {

	class DefaultDebugWidget : public ImGuiWidget {
	PRX_DISALLOW_COPY_AND_MOVE(DefaultDebugWidget)
	private:
		bool m_LogFlag;
		bool m_InfoFlag;
		bool m_DebugMenu;
		bool m_RendererMetrics;
		std::string m_MetricsCache;
		size_t m_MericsUpdateCounter;
	public:
		DefaultDebugWidget()
			: ImGuiWidget(),
			m_LogFlag(false),
			m_InfoFlag(false),
			m_DebugMenu(false),
			m_RendererMetrics(false)
		{}

		bool isDebugMenuEnabled() const {
			return m_DebugMenu;
		};

		void show() override {
			//ImGui::ShowDemoWindow();
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("Exit"))
						Window::getInstance()->closeWindow();
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Tools"))
				{
					if (ImGui::MenuItem("Log", nullptr, &m_LogFlag)) {}
					if (ImGui::MenuItem("Info", nullptr, &m_InfoFlag)) {}
					if (ImGui::MenuItem("Debug menu", nullptr, &m_DebugMenu)) {}
					if (ImGui::MenuItem("Renderer metrics", nullptr, &m_RendererMetrics)) {}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();

			}
			if (m_LogFlag) {
				ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
				if (ImGui::Begin("log", &m_LogFlag)) {
					ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
					for (auto message : Log::getBuffer()) {
						ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
						if (message.m_Level == LogLevel::LOG_WARN)
							color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
						else if (message.m_Level == LogLevel::LOG_ERROR)
							color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
						else if (message.m_Level == LogLevel::LOG_FATAL)
							color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

						ImGui::TextColored(color, message.m_Message.c_str());
						//ImGui::TextUnformatted();
					}
					ImGui::EndChild();
				}
				ImGui::End();
			}
			if (m_InfoFlag) {
				ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
				ImGui::Begin("Info", &m_InfoFlag);
				ImGui::Text(("Resolution: " + std::to_string(Window::getInstance()->getWidth()) + "x" + std::to_string(Window::getInstance()->getWidth())).c_str());
				ImGui::Text((std::to_string(Application::getInstance()->getFPS()) + " fps").c_str());
				ImGui::Text((std::to_string(Application::getInstance()->getUPS()) + " ups").c_str());
				ImGui::End();
			}
			if (m_RendererMetrics) {
				if (m_MericsUpdateCounter > Application::getInstance()->getFPS()) {
					m_MetricsCache = DFR2DMetrics::getFormatted();
					m_MericsUpdateCounter = 0;
				}
				m_MericsUpdateCounter++;
				ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_FirstUseEver);
				ImGui::Begin("Renderer metrics", &m_RendererMetrics);
				ImGui::Text(m_MetricsCache.c_str());
				ImGui::End();
			}

		}
	};
}
