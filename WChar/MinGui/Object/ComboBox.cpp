#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::ComboBox(const std::vector<std::wstring>& items, const Vec2& size, int& value, const std::wstring& desc)
{
	const Vec2	Offset		= Ctx.Offset.top();
	Ctx.Offset.pop();
	Vec2		DrawPos		= Ctx.Pos + Offset;
	bool		Focoused	= Ctx.Focous == Ctx.CurIndex;
	float		Pad			= 0;

	if (!desc.empty()) {
		Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Pad = static_cast<float>(DescHeight + 3);
		DrawPos.y += Pad;
	}

	value = std::clamp(value, 0, static_cast<int>(items.size()) - 1);

	Render::AddText(DrawPos + Vec2{ size.x - 10, size.y / 2 }, L"+", global_colors.color_text, AlignMode::CENTER, Ctx.CurLevel + 2);
	Render::AddText(DrawPos + Vec2{ 6, size.y  / 2 }, items[value] , global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 2);
	Render::AddFilledRect(DrawPos + Vec2{ 1,1 }, size - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurLevel);


	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(DrawPos, size) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
			Ctx.Pass = true;
		}
		else if (Focoused) {
			const float	ItemHeight = static_cast<float>(BaseTextHeight + 8);
			const Vec2  ItemSize = { size.x, ItemHeight };
			for (int i = 0; i < items.size(); i++) {
				bool Hovered = Misc::Utils::IsMouseInRegion(DrawPos + Vec2{ 0, size.y + (ItemHeight - 1) * i }, ItemSize - Vec2{ 0,1 });

				if (KeyOb.IsPressed(VK_LBUTTON)) {
					Ctx.Focous = -1;
					if (Hovered) {
						Ctx.Pass = true;
						value = i;
					}
				}
				bool Selected = value == i;
				Render::AddText(DrawPos + Vec2{ 6, size.y + (ItemHeight - 1) * i + ItemHeight / 2 }, items[i], global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 257);
				Render::AddFilledRect(DrawPos + Vec2{ 1, size.y + (ItemHeight - 1) * i + 1 }, ItemSize - Vec2{ 2,2 }, (Hovered || Selected) ? global_colors.color_combo_bg : global_colors.control_idle, Ctx.CurLevel + 256);
				Render::AddFilledRect(DrawPos + Vec2{ 0, size.y + (ItemHeight - 1) * i }, ItemSize, global_colors.control_outline, Ctx.CurLevel + 255);
			}
		}
	}



	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace, Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Pad + Config.ItemSpace });
}

void MinGui::MultiComboBox(std::vector<MultiItem> items, const Vec2& size, const std::wstring& desc)
{

	const Vec2 Offset = Ctx.Offset.top();
	Ctx.Offset.pop();

	Vec2 DrawPos	= Ctx.Pos + Offset;
	bool Focoused	= Ctx.Focous == Ctx.CurIndex;

	float Pad = 0;

	if (!desc.empty()) {
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Pad = static_cast<float>(DescHeight + 3);
		Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
		DrawPos.y += Pad;
	}

	std::wstring Display;
	for (auto& i : items) {
		if (*i.value) {
			if (Display.length() > 0)
				Display += L", ";
			Display += i.name;
		}
	}

	int TextWidth, TextHeight;
	Functions.GetTextSize(Display.c_str(), TextWidth, TextHeight);

	if (TextWidth > size.x - 18) {
		Display.resize(static_cast<int>(size.x) / 10);
		Display += L" ...";
	}
	if (!Display.length())
		Display += L"нч";

	Render::AddText(DrawPos + Vec2{ size.x - 10, size.y / 2 }, L"+", global_colors.color_text, AlignMode::CENTER, Ctx.CurLevel + 2);
	Render::AddText(DrawPos + Vec2{ 6, size.y / 2 }, Display, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 2);
	Render::AddFilledRect(DrawPos + Vec2{ 1,1 }, size - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurLevel);



	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(DrawPos, size) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
			Ctx.Pass = true;
		}
		else if (Focoused) {
			const float	ItemHeight = static_cast<float>(BaseTextHeight + 8);
			const Vec2  ItemSize = { size.x, ItemHeight };
			for (int i = 0; i < items.size(); i++) {
				bool Hovered = Misc::Utils::IsMouseInRegion(DrawPos + Vec2{ 0, size.y + (ItemHeight - 1) * i }, ItemSize - Vec2{ 0,1 });
				const bool InBound = Misc::Utils::IsMouseInRegion(DrawPos + Vec2{ 0, size.y }, Vec2{ size.x, (ItemHeight - 1) * items.size() });
				if (KeyOb.IsPressed(VK_LBUTTON)) {
					if (Hovered) {
						Ctx.Pass = true;
						*items[i].value = !*items[i].value;
					}
					if (!InBound) {
						Ctx.Focous = -1;
					}
				}
				bool Selected = *items[i].value;

				Render::AddText(DrawPos + Vec2{ 6, size.y + (ItemHeight - 1) * i + ItemHeight / 2 }, items[i].name, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 257);
				Render::AddFilledRect(DrawPos + Vec2{ 1, size.y + (ItemHeight - 1) * i + 1 }, ItemSize - Vec2{ 2,2 }, (Hovered || Selected) ? global_colors.color_combo_bg : global_colors.control_idle, Ctx.CurLevel + 256);
				Render::AddFilledRect(DrawPos + Vec2{ 0, size.y + (ItemHeight - 1) * i }, ItemSize, global_colors.control_outline, Ctx.CurLevel + 255);
			}
		}
	}

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace, Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Pad + Config.ItemSpace });
}

