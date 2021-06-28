#include "../MinGui.h"

using namespace MinGui::Global;

bool MinGui::Window(const std::wstring& title, const Vec2& pos, const Vec2& size, const WindowFlags& flags)
{
	if (!Ctx.IsReady) {
		return false;
	}

	if (Ctx.FirstTime) {
		Functions.Setup();
		Ctx.Size = size;
		Ctx.Pos = pos;
		Ctx.FirstTime = false;
	}

	Ctx.CurIndex = 0;
	Ctx.CurLevel = 0;

	if (!flags.KeepOpen) {
		if (KeyOb.IsPressed(Config.ToggleKey)) {
			Ctx.Visible = !Ctx.Visible;
		}
	}
	else {
		Ctx.Visible = true;
	}

	if (Ctx.Visible) {
		if (flags.Moveable && flags.Bordered) {
			if (Misc::Utils::IsMouseInRegion({ Ctx.Pos.x  ,Ctx.Pos.y - 17 }, { Ctx.Size.x , 20 })
				&& KeyOb.IsPressed(VK_LBUTTON) && !Ctx.Dragging){
				Ctx.Dragging = true;
			}
			else if (KeyOb.IsDown(VK_LBUTTON) && Ctx.Dragging) {
				Vec2 Delta = { CurrMousePos.x - PrevMousePos.x, CurrMousePos.y - PrevMousePos.y };
				Ctx.Pos += Delta;
			}
			else if (!KeyOb.IsDown(VK_LBUTTON) && Ctx.Dragging) {
				Ctx.Dragging = false;
			}
		}

		if (flags.Bordered) {
			Functions.FillRect({ Ctx.Pos.x - 6, Ctx.Pos.y - 10 }, { Ctx.Size.x + 12, Ctx.Size.y + 16 }, global_colors.window_border_inner_fill);
			Functions.FillRect({ Ctx.Pos.x - 5, Ctx.Pos.y - 9 }, { Ctx.Size.x + 10, Ctx.Size.y + 14 }, global_colors.window_border_color);
			Functions.FillRect({ Ctx.Pos.x - 4, Ctx.Pos.y - 8 }, { Ctx.Size.x + 8, Ctx.Size.y + 12 }, global_colors.window_border_fill);
			Functions.FillRect({ Ctx.Pos.x, Ctx.Pos.y + 7 }, { Ctx.Size.x, Ctx.Size.y - 7 }, global_colors.window_border_color);
			Functions.FillRect({ Ctx.Pos.x + 1, Ctx.Pos.y + 8 }, { Ctx.Size.x - 2, Ctx.Size.y - 9 }, global_colors.window_border_inner_fill);
			Functions.FillRect({ Ctx.Pos.x + 8, Ctx.Pos.y + 15 }, { Ctx.Size.x - 16, Ctx.Size.y - 23 }, global_colors.window_border_color);
			Functions.DrawText(title, { Ctx.Pos.x + Ctx.Size.x / 2, Ctx.Pos.y }, global_colors.color_text, AlignMode::CENTER);
		}

		Functions.FillRect({ Ctx.Pos.x + 9, Ctx.Pos.y + 16 }, { Ctx.Size.x - 18, Ctx.Size.y - 25 }, global_colors.window_background);

		int Tmp;

		Functions.GetTextSize(L" ", Tmp, BaseTextHeight);
		Ctx.Pass = false;
		Ctx.Offset.push(Config.BaseObjectPos);
	}


	return Ctx.Visible;
}