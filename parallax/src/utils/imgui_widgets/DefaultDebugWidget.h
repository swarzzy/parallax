#pragma once

#include "ImGUIWidget.h"
#include "../../Application/Application.h"
#include "../../window/Window.h"
#include "../../ext/imgui/imgui.h"

namespace prx {

	class DefaultDebugWidget : public ImGuiWidget {
	PRX_DISALLOW_COPY_AND_MOVE(DefaultDebugWidget)
	private:
		bool m_LogFlag;
		bool m_InfoFlag;
	public:
		DefaultDebugWidget()
			: ImGuiWidget(),
			m_LogFlag(false),
			m_InfoFlag(false)
		{}

	private:
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

		}
	};
}
