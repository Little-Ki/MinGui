#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::Lable(const std::string& text)
{
	const Vec2 Offset = Ctx.Offset.top();
	Ctx.Offset.pop();
	const Vec2 DrawPos = Ctx.Pos + Offset;

	int TextWidth, TextHeight;
	Functions.GetTextSize(text, TextWidth, TextHeight);

	Render::AddText(DrawPos, text, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ static_cast<float>(TextWidth + Config.ItemSpace),0 });
	Ctx.Offset.push(Offset + Vec2{ 0,static_cast<float>(TextHeight + Config.ItemSpace) });
}

bool MinGui::ClickableLable(const std::string& text)
{
	const Vec2 Offset = Ctx.Offset.top();
	Ctx.Offset.pop();
	const Vec2 DrawPos = Ctx.Pos + Offset;
	bool Clicked = false;
	bool Focoused = Ctx.Focous == Ctx.CurIndex;

	int TextWidth, TextHeight;
	Functions.GetTextSize(text, TextWidth, TextHeight);

	Vec2 TextSize = { static_cast<float>(TextWidth),static_cast<float>(TextHeight) };
	if (!Ctx.Pass) {
		if (Misc::Utils::IsMouseInRegion(DrawPos, TextSize) && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
		}


		if (KeyOb.IsReleased(VK_LBUTTON) && Focoused) {
			if (Misc::Utils::IsMouseInRegion(DrawPos, TextSize)) {
				Ctx.Pass = true;
				Clicked = true;
			}
			Ctx.Focous = -1;
		}
	}
	Render::AddText(DrawPos, text, Focoused ? global_colors.control_active_or_clicked : global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ static_cast<float>(TextWidth + Config.ItemSpace),0 });
	Ctx.Offset.push(Offset + Vec2{ 0,static_cast<float>(TextHeight + Config.ItemSpace) });

	return Clicked;
	return false;
}