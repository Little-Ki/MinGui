#include "../MinGui.h"

using namespace MinGui::Global;

constexpr std::wstring_view KeyNames[] ={
                L"Error" ,
                L"Left Mouse", L"Right Mouse", L"Break", L"Middle Mouse", L"Mouse 4", L"Mouse 5",
                L"Error" ,
                L"Backspace", L"TAB", L"Error", L"Error", L"Error", L"ENTER", L"Error", L"Error", L"SHIFT",
                L"CTRL"  , L"ALT", L"PAUSE", L"CAPS LOCK", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error" , L"Error", L"Error", L"Error", L"Error", L"SPACEBAR", L"PG UP", L"PG DOWN", L"END", L"HOME", L"Left",
                L"Up"    , L"Right", L"Down", L"Error", L"Print", L"Error", L"Print Screen", L"Insert", L"Delete", L"Error",
                L"0", L"1",L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"A", L"B", L"C", L"D", L"E", L"F", L"G", L"H", L"I", L"J", L"K", L"L", L"M",
                L"N", L"O", L"P", L"Q", L"R", L"S", L"T", L"U", L"V", L"W", L"X", L"Y", L"Z",
                L"Left Win", L"Right Win", L"Error", L"Error", L"Error",
                L"NUM 0", L"NUM 1",L"NUM 2", L"NUM 3", L"NUM 4", L"NUM 5", L"NUM 6", L"NUM 7", L"NUM 8", L"NUM 9",
                L"*", L"+", L"_", L"-", L".", L"/",
                L"F1"    , L"F2"  , L"F3"  , L"F4"  , L"F5"  , L"F6"  , L"F7"  , L"F8"  , L"F9"  , L"F10" , L"F11" , L"F12",
                L"F13"   , L"F14" , L"F15" , L"F16" , L"F17" , L"F18" , L"F19" , L"F20" , L"F21" , L"F22" , L"F23" , L"F24",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"NUM LOCK", L"SCROLL LOCK",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error", L"Error", L"Error", L"Error", L"Error", 
                L"LSHIFT", L"RSHIFT", L"LCONTROL",L"RCONTROL", L"LMENU", L"RMENU", 
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", 
                L"Error", 
                L"Next Track", L"Previous Track", L"Stop", L"Play/Pause", 
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L";", L"+", L",", L"-", L".", L"/?", L"~",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"[{", L"\\|", L"}]", L"'\"", L"Error",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error", L"Error",
                L"Error", L"Error"
        };

void MinGui::KeyBox(const Vec2& size, int& value, const std::wstring& desc)
{
    const Vec2  Offset = Ctx.Offset.top();
    Ctx.Offset.pop();
    Vec2        DrawPos = Ctx.Pos + Offset;
    bool        Focoused = Ctx.Focous == Ctx.CurIndex;
    float       Pad = 0;

    if (!desc.empty()) {
        int DescWidth, DescHeight;
        Functions.GetTextSize(desc, DescWidth, DescHeight);
        Render::AddText(DrawPos + Vec2{ 2,0 }, desc, global_colors.color_text, AlignMode::LEFT_TOP, Ctx.CurLevel);
        Pad = static_cast<float>(DescHeight + 5);
        DrawPos.y += Pad;
    }

    value = std::clamp(value, 0, 255);

    if (!Ctx.Pass) {
        if (Misc::Utils::IsMouseInRegion(DrawPos, size) && !Focoused && KeyOb.IsPressed(VK_LBUTTON)) {
            Ctx.Focous = Ctx.CurIndex;
        }
        else if (Focoused) {
            for (int i = 0; i < 256; i++) {
                if (KeyOb.IsPressed(i)) {
                    if (KeyNames[i] != L"Error") {
                        Ctx.Pass = true;
                        value = i;
                    }
                    Ctx.Focous = -1;
                }
            }
        }
    }

    std::wstring Display = Focoused ? L"°´ÏÂ°´¼ü" : KeyNames[value].data();

    int TextWidth, TextHeight;
    Functions.GetTextSize(Display, TextWidth, TextHeight);

    Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurLevel);
    Render::AddFilledRect(DrawPos + Vec2{ 1, 1 }, size - Vec2{2,2}, Focoused ? global_colors.control_active_or_clicked : global_colors.control_idle, Ctx.CurLevel + 1);
    Render::AddText(DrawPos + Vec2{ 6,size.y / 2 }, Display, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 2);

    Ctx.CurIndex++;
    Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace,Pad });
    Ctx.Offset.push(Offset + Vec2{ 0,size.y + Pad + Config.ItemSpace }); 
}