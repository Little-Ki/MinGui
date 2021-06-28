#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::Begin(HWND hwnd)
{
	KeyOb.Update();

	POINT Point;
	GetCursorPos(&Point);
	ScreenToClient(hwnd, &Point);

	PrevMousePos = CurrMousePos;

	CurrMousePos = { static_cast<float>( Point.x), static_cast<float>(Point.y) };

	Ctx.Render.clear();
	while (!Ctx.Offset.empty())
		Ctx.Offset.pop();

	Ctx.IsReady = true;
}

void MinGui::End()
{
	std::sort(Ctx.Render.begin(), Ctx.Render.end(), [](auto& l, auto& r)->bool { return l.Z < r.Z; });

	for (auto r : Ctx.Render) {
		switch (r.Type)
		{
		case ElementType::RECT:
			Functions.DrawRect(r.Pos, r.Size, r.Color);
			break;
		case ElementType::FILLED_RECT:
			Functions.FillRect(r.Pos, r.Size, r.Color);
			break;
		case ElementType::TEXT:
			Functions.DrawText(r.Text, r.Pos, r.Color, r.Mode);
			break;
		case ElementType::LINE:
			Functions.DrawLine(r.Pos, r.Size, r.Color);
			break;
		}
	}
	Ctx.IsReady = false;
}

void MinGui::SetupFunctions(const ProxyFuncs& functions)
{
	Functions = functions;
}