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

void MinGui::Misc::Positioning::SameLineWithOffset(std::function<void()> inner, const Vec2& offset)
{

	bool Backup = false;
	Vec2 Old;
	if (Ctx.Offset.size() >= 2) {
		Backup = true;
		Old = Ctx.Offset.top();
		Ctx.Offset.pop();
	}
	Vec2 This = Ctx.Offset.top();
	Ctx.Offset.push(This + offset);
	inner();
	if (Backup) {
		Ctx.Offset.push(Old);
	}
}

void MinGui::Misc::Positioning::AddOffset(const Vec2& offset)
{
	if (Ctx.Offset.size() > 0) {
		Vec2 This = Ctx.Offset.top();
		Ctx.Offset.push(This + offset);
	}
}
