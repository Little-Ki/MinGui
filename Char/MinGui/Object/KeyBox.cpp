#include "../MinGui.h"

using namespace MinGui::Global;

constexpr std::string_view KeyNames[] ={
                "Error" , 
                "Left Mouse", "Right Mouse", "Break", "Middle Mouse", "Mouse 4", "Mouse 5",
                "Error" , 
                "Backspace", "TAB", "Error", "Error", "Error", "ENTER", "Error", "Error", "SHIFT",
                "CTRL"  , "ALT", "PAUSE", "CAPS LOCK", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error" , "Error", "Error", "Error", "Error", "SPACEBAR", "PG UP", "PG DOWN", "END", "HOME", "Left",
                "Up"    , "Right", "Down", "Error", "Print", "Error", "Print Screen", "Insert", "Delete", "Error",
                "0", "1","2", "3", "4", "5", "6", "7", "8", "9", 
                "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", 
                "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                "Left Win", "Right Win", "Error", "Error", "Error", 
                "NUM 0", "NUM 1","NUM 2", "NUM 3", "NUM 4", "NUM 5", "NUM 6", "NUM 7", "NUM 8", "NUM 9", 
                "*", "+", "_", "-", ".", "/", 
                "F1"    , "F2"  , "F3"  , "F4"  , "F5"  , "F6"  , "F7"  , "F8"  , "F9"  , "F10" , "F11" , "F12", 
                "F13"   , "F14" , "F15" , "F16" , "F17" , "F18" , "F19" , "F20" , "F21" , "F22" , "F23" , "F24", 
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "NUM LOCK", "SCROLL LOCK", 
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", 
                "Error", "Error", "Error", "Error", "Error", 
                "LSHIFT", "RSHIFT", "LCONTROL","RCONTROL", "LMENU", "RMENU", 
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", 
                "Error", 
                "Next Track", "Previous Track", "Stop", "Play/Pause", 
                "Error", "Error", "Error", "Error", "Error", "Error",
                ";", "+", ",", "-", ".", "/?", "~",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "[{", "\\|", "}]", "'\"", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error", "Error",
                "Error", "Error"
        };

void MinGui::KeyBox(const Vec2& size, int& value, const std::string& desc)
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
                    if (KeyNames[i] != "Error") {
                        Ctx.Pass = true;
                        value = i;
                    }
                    Ctx.Focous = -1;
                }
            }
        }
    }

    std::string Display = Focoused ? "°´ÏÂ°´¼ü" : KeyNames[value].data();

    int TextWidth, TextHeight;
    Functions.GetTextSize(Display, TextWidth, TextHeight);

    Render::AddFilledRect(DrawPos, size, global_colors.control_outline, Ctx.CurLevel);
    Render::AddFilledRect(DrawPos + Vec2{ 1, 1 }, size - Vec2{2,2}, Focoused ? global_colors.control_active_or_clicked : global_colors.control_idle, Ctx.CurLevel + 1);
    Render::AddText(DrawPos + Vec2{ 6,size.y / 2 }, Display, global_colors.color_text, AlignMode::LEFT_CENTER, Ctx.CurLevel + 2);

    Ctx.CurIndex++;
    Ctx.Offset.push(Offset + Vec2{ size.x + Config.ItemSpace,Pad });
    Ctx.Offset.push(Offset + Vec2{ 0,size.y + Pad + Config.ItemSpace }); 
}