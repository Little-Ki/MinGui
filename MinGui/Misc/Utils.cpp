#include "../MinGui.h"

using namespace MinGui::Global;

bool MinGui::Misc::Utils::IsMouseInRegion(const Vec2& Pos, const Vec2& Size)
{
	return 
		CurrMousePos.x >= Pos.x && CurrMousePos.x < Pos.x + Size.x &&
		CurrMousePos.y >= Pos.y && CurrMousePos.y < Pos.y + Size.y;
}