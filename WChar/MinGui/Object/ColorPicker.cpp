#include "../MinGui.h"

using namespace MinGui::Global;

static int PickerFocous = 0;

void MinGui::ColorPicker(const Vec2& size, Color& value, const std::wstring& desc)
{
	const Vec2 Offset = Ctx.Offset.top();
	Ctx.Offset.pop();

	Vec2 DrawPos = Ctx.Pos + Offset;
	bool Focoused = Ctx.Focous == Ctx.CurIndex;

	float Pad = 0;

	if (!desc.empty()) {
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Pad = static_cast<float>(DescWidth + 5);
		Render::AddText(DrawPos + Vec2{ 0,size.y / 2 }, desc, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel);
		DrawPos.x += Pad;
	}

	Render::AddFilledRect(DrawPos + Vec2{ 1,1 }, size - Vec2{ 2,2 }, value, Ctx.CurLevel + 1);
	Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurLevel);


	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(DrawPos, size) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
			Ctx.Pass = true;
		}
		else if (Focoused) {
			Vec2 BoundPos = DrawPos + Vec2{ 0,size.y };
			Vec2 BoundSize = Vec2{ 110,90 };

			bool InBound = Misc::Utils::IsMouseInRegion(BoundPos, BoundSize);
			if (KeyOb.IsPressed(VK_LBUTTON)) {
				if (!InBound) {
					Ctx.Focous = -1;
				}
				else {
					Ctx.Pass = true;
				}
			}

			Vec2 RSliderPos = BoundPos + Vec2{ 20,10 };
			Vec2 GSliderPos = BoundPos + Vec2{ 20,36 };
			Vec2 BSliderPos = BoundPos + Vec2{ 20,62 };
			Vec2 SliderSize = { 80,19 };

			Render::AddText(RSliderPos + Vec2{ -12, SliderSize.y / 2 }, L"R", global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 257);
			Render::AddText(GSliderPos + Vec2{ -12, SliderSize.y / 2 }, L"G", global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 257);
			Render::AddText(BSliderPos + Vec2{ -12, SliderSize.y / 2 }, L"B", global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 257);

			bool SliderFocoused;
			float FillWidth;
			{
				SliderFocoused = PickerFocous == 1;
				if (Misc::Utils::IsMouseInRegion(RSliderPos, SliderSize) && !SliderFocoused && KeyOb.IsPressed(VK_LBUTTON)) {
					PickerFocous = 1;
					Ctx.Pass = true;
				}
				else if (KeyOb.IsDown(VK_LBUTTON) && SliderFocoused) {
					float	UnmappedValue = std::clamp(CurrMousePos.x - RSliderPos.x, 0.0f, static_cast<float>(SliderSize.x));
					int		MappedValue = static_cast<int>(UnmappedValue / SliderSize.x * 255);
					value.r = static_cast<float>( MappedValue);
					Ctx.Pass = true;
				}
				else if (!KeyOb.IsDown(VK_LBUTTON) && SliderFocoused) {
					PickerFocous = 0;
					Ctx.Pass = true;
				}

				FillWidth = static_cast<float>(value.r) / 255.f * (SliderSize.x - 2.f);
				Render::AddFilledRect(RSliderPos + Vec2{ 1,1 }, Vec2{ FillWidth,SliderSize.y - 2}, global_colors.color_slider, Ctx.CurLevel + 259);
				Render::AddFilledRect(RSliderPos + Vec2{ 1,1 }, SliderSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 258);
				Render::AddFilledRect(RSliderPos, SliderSize, global_colors.control_outline, Ctx.CurLevel + 257);

			}
			{
				SliderFocoused = PickerFocous == 2;
				if (Misc::Utils::IsMouseInRegion(GSliderPos, SliderSize) && !SliderFocoused && KeyOb.IsPressed(VK_LBUTTON)) {
					PickerFocous = 2;
					Ctx.Pass = true;
				}
				else if (KeyOb.IsDown(VK_LBUTTON) && SliderFocoused) {
					float	UnmappedValue = std::clamp(CurrMousePos.x - GSliderPos.x, 0.0f, static_cast<float>(SliderSize.x));
					int		MappedValue = static_cast<int>(UnmappedValue / SliderSize.x * 255);
					value.g = static_cast<float>(MappedValue);
					Ctx.Pass = true;
				}
				else if (!KeyOb.IsDown(VK_LBUTTON) && SliderFocoused) {
					PickerFocous = 0;
					Ctx.Pass = true;
				}

				FillWidth = static_cast<float>(value.g) / 255.f * (SliderSize.x - 2.f);
				Render::AddFilledRect(GSliderPos + Vec2{ 1,1 }, Vec2{ FillWidth,SliderSize.y - 2 }, global_colors.color_slider, Ctx.CurLevel + 259);
				Render::AddFilledRect(GSliderPos + Vec2{ 1,1 }, SliderSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 258);
				Render::AddFilledRect(GSliderPos, SliderSize, global_colors.control_outline, Ctx.CurLevel + 257);

			} 
			{
				SliderFocoused = PickerFocous == 3;
				if (Misc::Utils::IsMouseInRegion(BSliderPos, SliderSize) && !SliderFocoused && KeyOb.IsPressed(VK_LBUTTON)) {
					PickerFocous = 3;
					Ctx.Pass = true;
				}
				else if (KeyOb.IsDown(VK_LBUTTON) && SliderFocoused) {
					float	UnmappedValue = std::clamp(CurrMousePos.x - BSliderPos.x, 0.0f, static_cast<float>(SliderSize.x));
					int		MappedValue = static_cast<int>(UnmappedValue / SliderSize.x * 255);
					value.b = static_cast<float>(MappedValue);
					Ctx.Pass = true;
				}
				else if (!KeyOb.IsDown(VK_LBUTTON) && SliderFocoused) {
					PickerFocous = 0;
					Ctx.Pass = true;
				}

				FillWidth = static_cast<float>(value.b) / 255.f * (SliderSize.x - 2.f);
				Render::AddFilledRect(BSliderPos + Vec2{ 1,1 }, Vec2{ FillWidth,SliderSize.y - 2 }, global_colors.color_slider, Ctx.CurLevel + 259);
				Render::AddFilledRect(BSliderPos + Vec2{ 1,1 }, SliderSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 258);
				Render::AddFilledRect(BSliderPos, SliderSize, global_colors.control_outline, Ctx.CurLevel + 257);

			}

			Render::AddFilledRect(BoundPos + Vec2{ 1, 1 }, BoundSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 256);
			Render::AddFilledRect(BoundPos, BoundSize, global_colors.control_outline, Ctx.CurLevel + 255);
		}
	}

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace + Pad, 0 });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Config.ItemSpace });
}