# ImGuiAl
Some widgets for [imgui](https://github.com/ocornut/imgui).

## ImGuiAl::Log

A logger that can be filtered by message priority (`kDebug`, `kInfo`, `kWarn` and `kError`) and keywords.

### Usage

To use, include `imguial_log.h` and declare a `ImGuiAl::Log` variable somewhere, configure it, and then call `Draw` where you want the logger to appear. You can pass `false` to `Draw` to disable the log filters. To change the number of lines kept in the log, call `SetHistory`. To change the the colors used for the different priorities, use `SetColor`.

Call `Debug`, `Info`, `Warn`, `Error` or `VPrintf` to add messages to the logger. Use `Clear` to clear the entire log.

## ImGuiAl::Fonts

This is not really a widget, but some additional fonts conveniently-packed for use with imgui:

* Steve Matteson's [Cousine Regular](https://www.google.com/fonts/specimen/Cousine), released under the **Apache License**, version 2.0
* Steve Matteson's [Droid Sans](https://www.google.com/fonts/specimen/Droid+Sans), released under the **Apache License**, version 2.0
* Jonny Pinhorn's [Karla Regular](https://www.google.com/fonts/specimen/Karla), released under the **SIL Open Font License**, version 1.1
* Tristan Grimmer's [Proggy Tiny](http://www.proggyfonts.net/), release under the **MIT** license
* Dave Gandy's [Font Awesome](http://fontawesome.io/), released under the **SIL Open Font License**, version 1.1
* Google's [Material Design Icons](https://design.google.com/icons/), released under the **CC-BY license**, version 4.0
* KenneyNL and SamBrishes' [Kenney Icon Font](https://github.com/SamBrishes/kenney-icon-font), released under the **CC0**, version 1.0

The fonts are embedded in compressed form, and for Font Awesome, Material Design Icons, and Kenney Icon Font, Juliette Foucaut's [IconFontCHeaders](https://github.com/juliettef/IconFontCppHeaders), released under the **MIT** license, for easy of use.

### Usage

Define one or more of the following macros before compiling `imguial_fonts.cpp` to embed them in your application:

* IMGUIAL_FONTS_COUSINE_REGULAR
* IMGUIAL_FONTS_DROID_SANS
* IMGUIAL_FONTS_KARLA_REGULAR
* IMGUIAL_FONTS_PROGGY_TINY
* IMGUIAL_FONTS_FONT_AWESOME
* IMGUIAL_FONTS_MATERIAL_DESIGN
* IMGUIAL_FONTS_KENNEY_ICONS

Include `imguial_fonts.h`, and use `ImGuiAl::Fonts::GetCompressedData` along with imgui's `AddFontFromMemoryCompressedTTF`:

```c++
int ttf_size;
const void* ttf_data = ImGuiAl::Fonts::GetCompressedData( ImGuiAl::Fonts::kMaterialDesign, &ttf_size );

if ( ttf_data ) {
  static const ImWchar ranges[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
  ImFontConfig config;
  config.MergeMode = true;
  ImGuiIO& io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
  io.Fonts->AddFontFromMemoryCompressedTTF( ttf_data, ttf_size, 24.0f, &config, ranges );
}
```

# License

ImGuiAl is released under the [MIT](https://github.com/leiradel/ImGuiAl/blob/master/LICENSE) license.
