#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::CheckBox(const std::string& text, bool& value)
{
	const Vec2 Offset	= Ctx.Offset.top();
	Ctx.Offset.pop();
	const Vec2 DrawPos	= Ctx.Pos + Offset;
	bool Focoused		= Ctx.Focous == Ctx.CurIndex;
	Vec2 DrawSize		= Vec2{ 10,10 };

	int TextWidth,TextHeight;
	Functions.GetTextSize(text, TextWidth, TextHeight);

	DrawSize.x += TextWidth;
	DrawSize.y = TextHeight > 10.f ? TextHeight : 10.f;
	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(DrawPos, DrawSize) && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
		}

		if (KeyOb.IsReleased(VK_LBUTTON) && Focoused) {
			if (Misc::Utils::IsMouseInRegion(DrawPos, DrawSize)) {
				value = !value;
				Ctx.Pass = true;
			}
			Ctx.Focous = -1;
		}
	}
	Render::AddFilledRect(DrawPos + Vec2{ 1,DrawSize.y / 2 - 5 }, { 10,10 }, global_colors.control_outline, Ctx.CurLevel);
	Render::AddFilledRect(DrawPos + Vec2{ 2,DrawSize.y / 2 - 4 }, { 8,8 }, value ? global_colors.control_active_or_clicked : global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddText(DrawPos + Vec2{ 14,DrawSize.y / 2 }, text, value ? global_colors.color_text : global_colors.color_text_dimmer, AlignMode::LEFT_CENTER, Ctx.CurLevel + 2);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ DrawSize.x + Config.ItemSpace,0 });
	Ctx.Offset.push(Offset + Vec2{ 0,DrawSize.y + Config.ItemSpace });
}