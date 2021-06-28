#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::GroupBox(const std::wstring& title, const Vec2& size, bool center, std::function<void()> inner)
{
	const Vec2	Offset		= Ctx.Offset.top();
	Ctx.Offset.pop();
	Vec2		DrawPos		= Ctx.Pos + Offset;
	float		Pad			= 0;
	int			TextHeight, TextWidth;
	Ctx.CurLevel			+= 32;


	if (!title.empty()) {
		Functions.GetTextSize(title, TextWidth, TextHeight);
		Pad = static_cast<float>(TextHeight / 2);
		DrawPos.y += Pad;
	}

	Functions.FillRect(DrawPos , size - Vec2{ 0,Pad }, global_colors.control_outline);
	Functions.FillRect(DrawPos + Vec2{ 1,1 }, size - Vec2{ 2, 2 + Pad }, global_colors.color_groupbox_bg);

	if(center){
		if (!title.empty()) {
			Functions.DrawText(title, DrawPos + Vec2{ size.x / 2,0 }, global_colors.color_text, AlignMode::CENTER);
		}
	}
	else {
		if (!title.empty()) {
			Functions.DrawText(title, DrawPos + Vec2{ 6,-Pad }, global_colors.color_text, AlignMode::LEFT_CENTER);
		}
	}

	Ctx.Offset.push(Offset + Config.InnerObjectPos + Vec2{ 0,Pad });
	inner();

	Ctx.CurLevel -= 32;

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace, Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Config.ItemSpace + Pad });
}