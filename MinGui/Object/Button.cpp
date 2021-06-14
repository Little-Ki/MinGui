#include "../MinGui.h"

using namespace MinGui::Global;

bool MinGui::Button(const std::string& text, const Vec2& size)
{
	const Vec2 Offset	= Ctx.Offset.top();
	Ctx.Offset.pop();
	const Vec2 DrawPos	= Ctx.Pos + Offset;
	bool Clicked		= false;
	bool Focoused		= Ctx.Focous == Ctx.CurIndex;

	if(!Ctx.Pass){
		if (Misc::Utils::IsMouseInRegion(DrawPos, size) && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
		}


		if (KeyOb.IsReleased(VK_LBUTTON) && Focoused) {
			if (Misc::Utils::IsMouseInRegion(DrawPos, size)) {
				Clicked = true;
				Ctx.Pass = true;
			}
			Ctx.Focous = -1;
		}

	}

	Vec2 TextPos = {
		DrawPos.x + size.x / 2,
		DrawPos.y + size.y / 2
	};

	Render::AddFilledRect(DrawPos, size,  global_colors.control_outline, Ctx.CurLevel);
	Render::AddFilledRect(DrawPos + Vec2{ 1, 1 }, size - Vec2{ 2,2 }, Focoused ? global_colors.control_active_or_clicked : global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddText(TextPos, text, global_colors.color_text, AlignMode::CENTER, Ctx.CurLevel + 2);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace,0 });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Config.ItemSpace });

	return Clicked;
}

void MinGui::ToggleButton(const std::string& text, const Vec2& size, bool& value)
{
	const Vec2 Offset	= Ctx.Offset.top();
	Ctx.Offset.pop();
	const Vec2 DrawPos	= Ctx.Pos + Offset;
	bool Clicked		= false;
	bool Focoused		= Ctx.Focous == Ctx.CurIndex;

	if (Misc::Utils::IsMouseInRegion(DrawPos, size) && KeyOb.IsPressed(VK_LBUTTON)) {
		Ctx.Focous = Ctx.CurIndex;
	}


	if (KeyOb.IsReleased(VK_LBUTTON) && Focoused) {
		if (Misc::Utils::IsMouseInRegion(DrawPos, size)) {
			value = !value;
		}
		Ctx.Focous = -1;
	}


	Vec2 TextPos = {
		DrawPos.x + size.x / 2,
		DrawPos.y + size.y / 2
	}
	;
	Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurLevel);
	Render::AddFilledRect(DrawPos + Vec2{ 1, 1 }, size - Vec2{ 2,2 }, (Focoused || value)? global_colors.control_active_or_clicked : global_colors.control_idle, Ctx.CurLevel + 1);
	Render::AddText(TextPos, text, global_colors.color_text, AlignMode::CENTER, Ctx.CurLevel + 2);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace,0 });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Config.ItemSpace });
}