# ImGuiAl
Some widgets for [imgui](https://github.com/ocornut/imgui).

## ImGuiAl::Log

A logger that can be filtered by message priority (`kDebug`, `kInfo`, `kWarn` and `kError`) and keywords.

### Usage

To use, include `imguial_log.h` and declare a `ImGuiAl::Log` variable somewhere, configure it, and then call `Draw` where you want the logger to appear. To change the number of lines kept in the log, call `SetHistory`. To change the the colors used for the different priorities, use `SetColor`.

Call `Debug`, `Info`, `Warn`, `Error` or `VPrintf` to add messages to the logger. Use `Clear` to clear the entire log.

## ImGuiAl::GetMDICompressedData

This is not really a widget, but Google's [Material Design Icons](https://design.google.com/icons/) conveniently-packed for use with imgui. The True Type font is embedded in compressed form, and Juliette Foucaut's [IconFontCHeaders](https://github.com/juliettef/IconFontCppHeaders) for the font are included in the header for easy of use.

### Usage

Include `imguial_mdi.h`, and use `GetMDICompressedData` along with `AddFontFromMemoryCompressedTTF`:

```c++
int mdi_size;
const void* mdi_data = ImGuiAl::GetMDICompressedData( &mdi_size ); 
static const ImWchar ranges[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
ImFontConfig config;
config.MergeMode = true;
ImGuiIO& io = ImGui::GetIO();
io.Fonts->AddFontDefault();
io.Fonts->AddFontFromMemoryCompressedTTF( mdi_data, mdi_size, 12.0f, &config, ranges );
```

# License

ImGuiAl is released under the [MIT](https://github.com/leiradel/ImGuiAl/blob/master/LICENSE) license. Other resources used by ImGuiAl have their own licenses:

* Material Design Icons is released under the [CC-BY](https://creativecommons.org/licenses/by/4.0/) license.
* IconFontCppHeaders is released under the [MIT](https://github.com/juliettef/IconFontCppHeaders/blob/master/LICENSE) license.
