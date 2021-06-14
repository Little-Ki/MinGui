#include "../MinGui.h"

using namespace MinGui::Global;

void MinGui::Misc::Positioning::SameLine(std::function<void()> inner)
{
	bool Backup = false;
	Vec2 Old;
	if (Ctx.Offset.size() >= 2) {
		Backup = true;
		Old = Ctx.Offset.top();
		Ctx.Offset.pop();
	}
	inner();
	if (Backup) {
		Ctx.Offset.push(Old);
	}
}