#pragma once

using namespace MinGui;

namespace Proxy {
	static void GetTextSize(const std::string& text, int& width, int& height);

	static void Setup()
	{
		// Create font
	}

	static void DrawLine(const Vec2& form, const Vec2 to, const Color& color)
	{
		// DrawLine(...);
	}

	static void FillRect(const Vec2& pos, const Vec2& size, const Color& color)
	{
		// FillRectangle(...);
	}

	static void DrawRect(const Vec2& pos, const Vec2& size, const Color& color)
	{

		// DrawRectangle(...);
	}

	static void DrawText(const std::string& text, const Vec2& pos, const Color& color, AlignMode mode)
	{
		switch (mode)
		{
		case MinGui::AlignMode::LEFT_TOP:
			// ...
			break;
		case MinGui::AlignMode::LEFT_CENTER:
			// ...
			break;
		case MinGui::AlignMode::CENTER:
			// ...
			break;
		}

	}

	static void GetTextSize(const std::string& text, int& width, int& height)
	{
		// Get text size
	}

}