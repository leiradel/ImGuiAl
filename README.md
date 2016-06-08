# ImGuiAl
Some widgets for [imgui](https://github.com/ocornut/imgui).

## ImGuiAl::Log

A logger that can be filtered by message priority (`kDebug`, `kInfo`, `kWarn` and `kError`) and keywords.

### Usage

To use, declare a `ImGuiAl::Log` variable somewhere, configure it, and then call `Draw` where you want the logger to appear. To change the number of lines kept in the log, call `SetHistory`. To change the the colors used for the different priorities, use `SetColor`.

Call `Debug`, `Info`, `Warn`, `Error` or `VPrintf` to add messages to the logger. Use `Clear` to clear the entire log.

# License

All widgets are released under the MIT license.
