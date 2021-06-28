#include "../MinGui.h"

using namespace MinGui::Global;
constexpr MinGui::KeyCode SpecialChars[22]{
		{48,  L'0',  L')'},
		{49,  L'1',  L'!'},
		{50,  L'2',  L'@'},
		{51,  L'3',  L'#'},
		{52,  L'4',  L'$'},
		{53,  L'5',  L'%'},
		{54,  L'6',  L'^'},
		{55,  L'7',  L'&'},
		{56,  L'8',  L'*'},
		{57,  L'9',  L'('},
		{32,  L' ',  L' '},
		{192, L'`',  L'~'},
		{189, L'-',  L'_'},
		{187, L'=',  L'+'},
		{219, L'[',  L'{'},
		{220, L'\\', L'|'},
		{221, L']',  L'}'},
		{186, L';',  L':'},
		{222, L'\'', L'"'},
		{188, L',',  L'<'},
		{190, L'.',  L'>'},
		{191, L'/',  L'?'}
};

void MinGui::TextBox(const Vec2& size, std::wstring& value, const int max_length, const std::wstring& desc, const wchar_t& mask)
{
	const Vec2	Offset		= Ctx.Offset.top();
	Ctx.Offset.pop();
	Vec2		DrawPos		= Ctx.Pos + Offset;
	bool		Focoused	= Ctx.Focous == Ctx.CurIndex;
	float		Pad			= 0;

	if (!desc.empty()) {
		Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
		int DescWidth, DescHeight;
		Functions.GetTextSize(desc, DescWidth, DescHeight);
		Pad = static_cast<float>(DescHeight + 5);
		DrawPos.y += Pad;
	}

	if (!Ctx.Pass) {
		const bool Hovered = Misc::Utils::IsMouseInRegion(DrawPos, size);
		if (Hovered && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
			Ctx.Focous = Ctx.CurIndex;
			Ctx.Pass = true;
		}
		else if (Focoused) {
			if (KeyOb.IsPressed(VK_ESCAPE) || KeyOb.IsPressed(VK_RETURN) || (!Hovered && KeyOb.IsPressed(VK_LBUTTON))) {
				Ctx.Focous = -1;
			}
			else if (KeyOb.IsPressed(VK_BACK) && !value.empty()) {
				value.pop_back();
			}
			else if (value.length() < max_length) {
				for (int i = 32; i <= 222; i++) {
					if ((i > 32 && i < 48) || (i > 57 && i < 65) || (i > 90 && i < 186))
						continue;

					if (i > 57 && i <= 90) {
						if (KeyOb.IsPressed(i))
							value += KeyOb.IsDown(VK_SHIFT) ? static_cast<char>(i) : static_cast<char>(i + 32);
					}
					else {
						if (KeyOb.IsPressed(i)) {
							for (auto& k : SpecialChars) {
								if (k.VK == i)
									value += KeyOb.IsDown(VK_SHIFT) ? k.Shift : k.Regular;
							}
						}
					}
				}
			}
			Ctx.Pass = true;
		}
	}
	Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurIndex);
	Render::AddFilledRect(DrawPos + Vec2{ 1,1 }, size - Vec2{ 2,2 }, Focoused ? global_colors.control_active_or_clicked : global_colors.control_idle, Ctx.CurIndex + 1);
	Render::AddText(DrawPos + Vec2{ 6, size.y / 2 }, mask == L'\0' ? value : std::wstring(value.size(), mask), global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurIndex + 2);

	Ctx.CurIndex++;
	Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace,Pad });
	Ctx.Offset.push(Offset + Vec2{ 0,size.y + Config.ItemSpace + Pad });
}
