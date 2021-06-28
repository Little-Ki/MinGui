#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::ListBox(std::vector<MultiItem>& items, const Vec2& item_size, const std::wstring& desc)
{
	const Vec2	Offset		= Ctx.Offset.top();
	Ctx.Offset.pop();
	bool		Focoused	= Ctx.Focous == Ctx.CurIndex;
	float		Pad			= 0;
	Vec2		DrawPos		= Ctx.Pos + Offset;
	Vec2		DrawSize	= Vec2{ item_size.x + 2,item_size.y * items.size() + 2 };

	if (!desc.empty()) {
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
		Pad = static_cast<float>(DescHeight + 5);
		DrawPos.y += Pad;
	}

	Render::AddFilledRect(DrawPos, DrawSize, global_colors.control_outline, Ctx.CurLevel);
	Render::AddFilledRect(DrawPos + Vec2{ 1,1 }, DrawSize - Vec2{ 2,2 }, global_colors.control_idle, Ctx.CurLevel + 1);

	if (!Ctx.Pass) {
		int TextWidth, TextHeight;
		for (int i = 0; i < items.size(); i++) {
			const bool Hovered = Misc::Utils::IsMouseInRegion(DrawPos + Vec2{ 1 , 1 + item_size.y * i }, item_size);
			if (!Ctx.Pass) {
				if (Hovered && KeyOb.IsPressed(VK_LBUTTON)) {
					Ctx.Focous = -1;
					Ctx.Pass = true;
					*items[i].value = !*items[i].value;
				}
			}
			Functions.GetTextSize(items[i].name, TextWidth, TextHeight);
			Render::AddText(DrawPos + Vec2{ 6, 1 + item_size.y * i + item_size.y / 2 }, items[i].name, *items[i].value || Hovered ? global_colors.control_active_or_clicked : global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 2);
		}
		if (Misc::Utils::IsMouseInRegion(DrawPos, DrawSize) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
		}

	}
	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ DrawSize.x + Config.ItemSpace, Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,DrawSize.y + Pad + Config.ItemSpace });
}