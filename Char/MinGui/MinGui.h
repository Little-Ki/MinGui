#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <iostream>
#include <functional>
#include <iomanip>
#include <sstream>

#pragma warning(disable:4267)
#pragma warning(disable:4244)

namespace MinGui {

	class KeyObserver {
	private:
		bool PrevState[256]{ false };
		bool CurrState[256]{ false };
	public:
		void Update() {
			for (int i = 0; i < 256; i++) {
				PrevState[i] = CurrState[i];
				CurrState[i] = GetAsyncKeyState(i);
			}
		}

		bool IsDown(unsigned char vk) {
			return CurrState[vk];
		}


		bool IsPressed(unsigned char vk) {
			return CurrState[vk] && !PrevState[vk];
		}

		bool IsReleased(unsigned char vk) {
			return !CurrState[vk] && PrevState[vk];
		}
	};

	struct Vec2 {
		float x, y;

		Vec2() : x(0), y(0) {}
		Vec2(float x, float y) :x(x), y(y) {}

		Vec2 operator+(const Vec2& other) const {
			return Vec2{
				x + other.x,
				y + other.y
			};
		}


		Vec2 operator-(const Vec2& other) const {
			return Vec2{
				x - other.x,
				y - other.y
			};
		}

		void operator+=(const Vec2& other) {
			x += other.x;
			y += other.y;
		}
	};

	struct MultiItem {
		std::string name;
		bool* value;
	};

	struct Color {
		float r, g, b, a;
	};

	enum class AlignMode {
		LEFT_TOP,
		LEFT_CENTER,
		CENTER
	};

	enum class ElementType {
		RECT,
		FILLED_RECT,
		TEXT,
		LINE
	};

	struct WindowFlags {
		bool Moveable = true;
		bool Sizeable = true;
		bool KeepOpen = true;
		bool Bordered = true;
	};

	struct RenderElement {
		ElementType		Type;
		Color			Color;
		Vec2			Pos, Size;
		int				Z;
		std::string		Text = std::string();
		AlignMode		Mode;
	};

	struct Context {
		Vec2						Pos, Size;
		std::vector<RenderElement>	Render;
		bool						Dragging;
		bool						Visible;

		std::stack<Vec2>			Offset;
		int							CurLevel = 0;

		int							CurIndex;
		int							Focous = -1;
		bool						FirstTime = true;
		bool						IsReady = false;
		bool						Pass = false;
	};

	struct KeyCode {
		int		VK;
		char	Regular;
		char	Shift;
	};


	namespace Global {
		extern Vec2			CurrMousePos;
		extern Vec2			PrevMousePos;

		extern int			BaseTextHeight;
		extern KeyObserver	KeyOb;

		static struct {
			int		ItemSpace = 7;
			Vec2	BaseObjectPos = { 16,23 };
			Vec2	InnerObjectPos = { 10,10 };
			int		ToggleKey = VK_INSERT;
		} Config;



		static struct {
			Color window_border_inner_fill{ 60, 60, 60, 255 };
			Color window_border_fill{ 40, 40, 40, 255 };
			Color window_border_color{ 10, 10, 10, 255 };
			Color window_background{ 40, 40, 40, 255 };

			Color control_outline{ 23, 23, 30, 255 };
			Color control_active_or_clicked{ 108, 92, 231, 255 };
			Color control_selected{ 10, 10, 10, 255 };
			Color control_idle{ 62, 62, 72, 255 };

			Color color_groupbox_bg{ 50, 50, 50, 255 };
			Color color_text{ 203, 203, 203, 255 };
			Color color_text_dimmer{ 99, 110, 114, 255 };
			Color color_slider{ 108, 92, 231, 255 };
			Color color_combo_bg{ 108, 92, 231, 255 };
			Color color_groupbox_header{ 26, 26, 26, 150 };
		} global_colors;

		// Window context
		extern Context Ctx;

		namespace Render {
			__forceinline extern void AddFilledRect(const Vec2& pos, const Vec2& size, const Color& color, int level);
			__forceinline extern void AddRect(const Vec2& pos, const Vec2& size, const Color& color, int level);
			__forceinline extern void AddLine(const Vec2& form, const Vec2& to, const Color& color, int level);
			__forceinline extern void AddText(const Vec2& pos, const std::string& text, const Color& color, AlignMode mode, int level);
		}
	}


	struct ProxyFuncs {
		std::function<void()> Setup;
		std::function<void(const Vec2&, const Vec2&, const Color&)> DrawLine;
		std::function<void(const Vec2&, const Vec2&, const Color&)> FillRect;
		std::function<void(const Vec2&, const Vec2&, const Color&)> DrawRect;
		std::function<void(const std::string&, const Vec2&, const Color&, AlignMode)> DrawText;
		std::function<void(const std::string&, int&, int&)> GetTextSize;
	};

	extern ProxyFuncs Functions;

	namespace Misc {
		namespace Utils {
			extern bool IsMouseInRegion(const Vec2& Pos, const Vec2& Size);
		}

		namespace Positioning {
			extern void SameLine(std::function<void()> inner);
			extern void SameLineWithOffset(std::function<void()> inner, const Vec2& offset);
			extern void AddOffset(const Vec2& offset);
		}
	}

	extern void SetupFunctions(const ProxyFuncs& functions);

	extern void Begin(HWND hwnd);
	extern void End();

	extern bool Window(const std::string& title, const Vec2& pos, const Vec2& size, const WindowFlags& flags);

	extern bool Button(const std::string& text, const Vec2& size);
	extern void ToggleButton(const std::string& text, const Vec2& size, bool& value);

	extern void CheckBox(const std::string& text, bool& value);

	extern void Lable(const std::string& text);
	extern bool ClickableLable(const std::string& text);

	extern void GroupBox(const std::string& title, const Vec2& size, bool center, std::function<void()> inner);

	extern void KeyBox(const Vec2& size, int& value, const std::string& desc);

	extern void ComboBox(const std::vector<std::string>& items, const Vec2& size, int& value, std::string desc);
	extern void MultiComboBox(std::vector<MultiItem> items, const Vec2& size, std::string desc);

	extern void ListBox(std::vector<MultiItem>& items, const Vec2& item_size, std::string desc);

	extern void IntSlider(const int min, const int max, const Vec2& size, int& value, const std::string& desc);
	extern void FloatSlider(const float min, const float max, const float step, const Vec2& size, float& value, const std::string& desc);

	extern void TextBox(const Vec2& size, std::string& value, const int max_length, const std::string& desc, const char& mask = '\0');

	extern void ColorPicker(const Vec2& size, Color& value, const std::string desc);
}