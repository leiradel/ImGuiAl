# ImGuiAl::Log

A logger that can be filtered by message priority (`kDebug`, `kInfo`, `kWarn` and `kError`) and keywords.

## Usage

To use, include `imguial_log.h` and declare and initialize a `ImGuiAl::Log` variable somewhere with the `Init` method:

```C++
bool ImGuiAl::Log::Init( unsigned flags = 0, const char** more_actions = NULL );
```

The filters collapsing header is disable by default. To Show the filters, either pass `ImGuiAl::Log::kShowFilters` as the `flags` parameter to `ImGuiAl::Log::Init`, or set a label for the header using `ImGuiAl::Log::SetFilterHeaderLabel`.

The `more_actions` parameter can be an array of strings terminated by a `NULL` element. These strings will be shown as buttons at the top of the control, and `ImGuiAl::Log::Draw()` will return the 1-based index of the button of the user clicks on it, otherwise it returns 0:

```C++
// Initialize
static const char* actions[] =
{
  ICON_FA_FILES_O " Copy",
  ICON_FA_FILE_O " Clear",
  NULL
};

log.Init( 0, actions );
log.SetLabel( ImGuiAl::Log::kDebug, ICON_FA_BUG " Debug" );
log.SetLabel( ImGuiAl::Log::kInfo, ICON_FA_INFO " Info" );
log.SetLabel( ImGuiAl::Log::kWarn, ICON_FA_EXCLAMATION_TRIANGLE " Warn" );
log.SetLabel( ImGuiAl::Log::kError, ICON_FA_WRENCH " Error" );
log.SetCumulativeLabel( ICON_FA_SORT_AMOUNT_DESC " Cumulative" );
log.SetFilterHeaderLabel( ICON_FA_FILTER " Filters" );
log.SetFilterLabel( ICON_FA_SEARCH " Filter (inc,-exc)" );

// Draw
switch ( log.Draw() )
{
case 0: break; // no action button pressed.
case 1: /* insert code here */ break; // "Copy" button pressed, copy the log text to the clipboard
case 2: log.Clear(); break;
}
```

The functions used to customize the control are:

* `SetColor( Level level, float r, float g, float b )`: Sets a color for a log level.
* `SetLabel( Level level, const char* label )`: Replaces the default label for the buttons used to filter the log based on a log level.
* `SetCumulativeLabel( const char* label )`: Replaces the default label for the checkbox that controls if the level filters are cumulative or not.
* `SetFilterHeaderLabel( const char* label )`: Sets the lable for the filters header. If this label is not set, the filters header is hidden unless you pass `kShowFilters` to the `Init` method.
* `SetFilterLabel( const char* label )`: Sets the label for the text filter.

When the log is initialized, use one of the output functions to log to the control:

* `VPrintf( Level level, const char* format, va_list args )`: Can be used to interface with other libraries that have their own methods to hooks to a logger.
* `Debug( const char* format, ... )` and the similar `Info`, `Warn` and `Error` logs to the control using the corresponding `ImGuiAl::Log::Level`.

Finally, use the `ImGuiAl::Log::Clear` method to clear the entire log, and `ImGuiAl::Log::Iterate` to access the log line-by-line.

## Note

Please note that, in order to avoid lots of `malloc`s and `free`s, the logger uses a ring buffer to hold the lines, which means that the oldest lines can be removed to open up space for new ones. That also means there's no way to know the maximum number of lines the logger can hold, since lines can have arbitrary lenghts.
