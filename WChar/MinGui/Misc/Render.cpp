#include "../MinGui.h"

using namespace MinGui::Global;

__forceinline void MinGui::Global::Render::AddFilledRect(const Vec2& pos, const Vec2& size, const Color& color, int level)
{
	Ctx.Render.emplace_back(RenderElement{ ElementType::FILLED_RECT,color,pos,size,level });
}

__forceinline void MinGui::Global::Render::AddRect(const Vec2& pos, const Vec2& size, const Color& color, int level)
{
	Ctx.Render.emplace_back(RenderElement{ ElementType::RECT,color,pos,size,level });
}

__forceinline void MinGui::Global::Render::AddLine(const Vec2& form, const Vec2& to, const Color& color, int level)
{
	Ctx.Render.emplace_back(RenderElement{ ElementType::LINE,color,form,to,level });
}

__forceinline void MinGui::Global::Render::AddText(const Vec2& pos, const std::wstring& text, const Color& color, AlignMode mode, int level)
{
	Ctx.Render.emplace_back(RenderElement{ ElementType::TEXT,color,pos,{},level,text ,mode });
}