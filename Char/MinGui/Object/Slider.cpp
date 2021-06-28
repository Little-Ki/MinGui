#include "../MinGui.h"

using namespace MinGui::Global;
void MinGui::IntSlider(const int min, const int max, const Vec2& size, int& value, const std::string& desc)
{
	const Vec2	Offset = Ctx.Offset.top();
	Ctx.Offset.pop();
	bool		Focoused = Ctx.Focous == Ctx.CurIndex;
	float		Pad = 0;
	Vec2		DrawPos = Ctx.Pos + Offset;

	if (!desc.empty()) {
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
		Pad = static_cast<float>(DescHeight + 5);
		DrawPos.y += Pad;
	}

	value = std::clamp(value, min, max);

	if (Ctx.Focous == -1 && Misc::Utils::IsMouseInRegion(DrawPos, Vec2{ 10, size.y }) && KeyOb.IsPressed(VK_LBUTTON)) {
		value = std::clamp(value - 1, min, max);
	}
	else if (Ctx.Focous == -1 && Misc::Utils::IsMouseInRegion(DrawPos + Vec2{ size.x - 10,0 }, Vec2{ 8, size.y }) && KeyOb.IsPressed(VK_LBUTTON)) {
		value = std::clamp(value + 1, min, max);
	}

	Vec2	SliderPos = DrawPos + Vec2{ 10,0 };
	Vec2	SliderSize = size - Vec2{ 20,0 };
	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(SliderPos, SliderSize) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
			Ctx.Pass = true;
		}
		else if (KeyOb.IsDown(VK_LBUTTON) && Focoused) {
			float	UnmappedValue = std::clamp(CurrMousePos.x - SliderPos.x, 0.0f, static_cast<float>(SliderSize.x));
			int		MappedValue = static_cast<int>(UnmappedValue / SliderSize.x * (max - min) + min);
			value = MappedValue;
			Ctx.Pass = true;
		}
		else if (!KeyOb.IsDown(VK_LBUTTON) && Focoused) {
			Ctx.Focous = -1;
			Ctx.Pass = true;
		}
	}
	float FillWidth = (static_cast<float>(value) - min) / (max - min) * (SliderSize.x - 2);
	std::string	DisplayValue = std::to_string(value);

	Render::AddText(DrawPos + Vec2{ 4, size.y / 2 }, "-", global_colors.color_text_dimmer, AlignMode::CENTER, Ctx.CurLevel);
	Render::AddText(DrawPos + Vec2{ size.x - 4,size.y / 2 }, "+", global_colors.color_text_dimmer, AlignMode::CENTER, Ctx.CurLevel);
	Render::AddText(SliderPos + Vec2{ 5,SliderSize.y / 2 }, DisplayValue, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 3);

	Render::AddFilledRect(SliderPos, SliderSize, global_colors.control_outline, Ctx.CurLevel);
	Render::AddFilledRect(SliderPos + Vec2{ 1,1 }, SliderSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddFilledRect(SliderPos + Vec2{ 1,1 }, Vec2{ FillWidth ,SliderSize.y - 2 }, global_colors.color_slider, Ctx.CurLevel + 2);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace, Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Pad + Config.ItemSpace });
}

void MinGui::FloatSlider(const float min, const float max, const float step, const Vec2& size, float& value, const std::string& desc)
{

	const Vec2	Offset = Ctx.Offset.top();
	Ctx.Offset.pop();
	bool		Focoused = Ctx.Focous == Ctx.CurIndex;
	float		Pad = 0;
	Vec2		DrawPos = Ctx.Pos + Offset;

	if (!desc.empty()) {
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
		Pad = static_cast<float>(DescHeight + 5);
		DrawPos.y += Pad;
	}

	value = std::clamp(value, min, max);

	if (Ctx.Focous == -1 && Misc::Utils::IsMouseInRegion(DrawPos, Vec2{ 10, size.y }) && KeyOb.IsPressed(VK_LBUTTON)) {
		value = std::clamp(value - step, min, max);
	}
	else if (Ctx.Focous == -1 && Misc::Utils::IsMouseInRegion(DrawPos + Vec2{ size.x - 10,0 }, Vec2{ 8, size.y }) && KeyOb.IsPressed(VK_LBUTTON)) {
		value = std::clamp(value + step, min, max);
	}

	Vec2	SliderPos = DrawPos + Vec2{ 10,0 };
	Vec2	SliderSize = size - Vec2{ 20,0 };
	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(SliderPos, SliderSize) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
			Ctx.Pass = true;
		}
		else if (KeyOb.IsDown(VK_LBUTTON) && Focoused) {
			float	UnmappedValue = std::clamp(CurrMousePos.x - SliderPos.x, 0.0f, static_cast<float>(SliderSize.x));
			float	MappedValue = (UnmappedValue / SliderSize.x * (max - min) + min);
			value = MappedValue;
			Ctx.Pass = true;
		}
		else if (!KeyOb.IsDown(VK_LBUTTON) && Focoused) {
			Ctx.Focous = -1;
			Ctx.Pass = true;
		}
	}
	float FillWidth = (static_cast<float>(value) - min) / (max - min) * (SliderSize.x - 2);

	std::stringstream ss;
	ss << std::fixed << std::setprecision(2) << value;
	std::string DisplayValue = ss.str();

	Render::AddText(DrawPos + Vec2{ 4, size.y / 2 }, "-", global_colors.color_text_dimmer, AlignMode::CENTER, Ctx.CurLevel);
	Render::AddText(DrawPos + Vec2{ size.x - 4,size.y / 2 }, "+", global_colors.color_text_dimmer, AlignMode::CENTER, Ctx.CurLevel);
	Render::AddText(SliderPos + Vec2{ 5,SliderSize.y / 2 }, DisplayValue, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 3);

	Render::AddFilledRect(SliderPos, SliderSize, global_colors.control_outline, Ctx.CurLevel);
	Render::AddFilledRect(SliderPos + Vec2{ 1,1 }, SliderSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddFilledRect(SliderPos + Vec2{ 1,1 }, Vec2{ FillWidth ,SliderSize.y - 2 }, global_colors.color_slider, Ctx.CurLevel + 2);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace, Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Pad + Config.ItemSpace });
}