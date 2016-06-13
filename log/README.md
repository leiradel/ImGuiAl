# ImGuiAl::Log

A logger that can be filtered by message priority (`kDebug`, `kInfo`, `kWarn` and `kError`) and keywords.

## Usage

To use, include `imguial_log.h` and declare a `ImGuiAl::Log` variable somewhere, initialize it with the desired buffer size, and then call `Draw` where you want the logger to appear. You can pass `false` to `Draw` to disable the log filters. To change the the default colors used for the different priorities (blue, green, yellow, red), use `SetColor`.

Call `Debug`, `Info`, `Warn`, `Error` or `VPrintf` to add messages to the logger. Use `Clear` to clear the entire log.

Please note that, in order to avoid lots of `malloc`s and `free`s, the logger uses a ring buffer to hold the lines, which means that the oldest lines can be removed to open up space for new ones. That also means there's no way to know how many lines the logger can hold before removing old ones, since lines can have arbitrary lenghts.
