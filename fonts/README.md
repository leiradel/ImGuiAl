# ImGuiAl::Fonts

This is not really a widget, but some fonts conveniently packed for use with [imgui](https://github.com/ocornut/imgui):

* Codeface
    * [Coding Font Tobi](https://github.com/chrissimpkins/codeface/tree/master/fonts/coding-font-tobi)
    * [Crisp](https://github.com/chrissimpkins/codeface/tree/master/fonts/crisp)
* [Fontaudio](https://github.com/fefanto/fontaudio)
* Font Awesome
    * [Font Awesome 4](https://github.com/FortAwesome/Font-Awesome/tree/4.x/fonts)
    * [Font Awesome 5](https://fontawesome.com/v5/download)
    * [Font Awesome 6](https://fontawesome.com/download)
* [Fork Awesome](https://forkaweso.me/Fork-Awesome/)
* Google
    * [Cousine](https://fonts.google.com/specimen/Cousine)
    * [Karla](https://fonts.google.com/specimen/Karla)
    * [Material Icons / Material Symbols](https://github.com/google/material-design-icons)
    * [Roboto](https://fonts.google.com/specimen/Roboto)
* Kenney
    * [Kenney Game Icons](https://www.kenney.nl/assets/game-icons)
    * [Kenney Game Icons Expansion](https://www.kenney.nl/assets/game-icons-expansion)
* [proggy_fonts](http://www.proggyfonts.net/)
    * Pixel Carnage
    * Proggy Clean
    * Proggy Clean (Centered Ponctuation)
    * Proggy Clean (Slashed Zero)
    * Proggy Small
    * Proggy Square
    * Proggy Square (Slashed Zero)
    * Proggy Tiny
    * Proggy Tiny (Slashed Zero)

The fonts are presented compressed and as C arrays, ready to be embedded:

```cpp
#include "IconsMaterialDesign.h"
#include "MaterialDesign.inl"

static const ImWchar ranges[] = {ICON_MIN_MD, ICON_MAX_MD, 0};
ImFontConfig config;
config.MergeMode = true;
ImGuiIO& io = ImGui::GetIO();
io.Fonts->AddFontDefault();
io.Fonts->AddFontFromMemoryCompressedTTF(MaterialDesign_compressed_data, MaterialDesign_compressed_size, 24.0f, &config, ranges);
```

Also use Juliette Foucaut's [IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders) to easily add icons to your captions:

```cpp
bool loadGamePressed = ImGui::Button(ICON_FA_ROCKET " Load game...");
```
