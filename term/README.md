# ImGuiAl::Crt

A line-based text output window that wanted to be a full terminal emulator but has limited capabilities. Each line can have an `unsigned` of metadata for use by the caller.

The buffer is used as a circular byte buffer, meaning that as new lines are added to the terminal, old lines may be erased to make up space. There's an overhead of `sizeof(ImGuiAl::Crt::Info)` plus the null character terminator for each line.

## Usage

Declare a `ImGuiAl::Crt` variable somewhere. Pass the buffer and its size to the constructor, or alternatively instantiate a `ImGuiAl::BufferedCrt` with the desired buffer size:

```cpp
char buffer[4096];
ImGuiAl::Crt crt(static_cast<void*>(buffer), sizeof(buffer));

// or

ImGuiAl::BufferedCrt<4096> crt();
```

Available methods:

```cpp
// Set the new color for the text.
void setForegroundColor(ImU32 const color);
// Set the new metadata for the text.
void setMetaData(unsigned const meta_data);

// Put a line onto the screen.
void printf(char const* const format, ...);
void vprintf(char const* const format, va_list args);

// Make sure the last line is visible.
void scrollToBottom();
// Clear the terminal.
void clear();

// Iterate over all lines of the terminal. The iterator receives
// The line color, length, and metadata for each line. If the iterator
// returns false, the interation ends.
void iterate(const std::function<bool(Info const& header, char const* const line)>& iterator) const;

// Draw the terminal at the current position.
void draw(ImVec2 const& size = ImVec2(0.0f, 0.0f));
```

# ImGuiAl::Log

A logger that can be filtered by message priority (`Debug`, `Info`, `Warn` and `Error`) and keywords. It inherits from `ImGuiAl::Crt`, so space for new messages may reuse space from old messages and make them disappear.

It supports four log levels: debug, info, warning, and error. Colors and labels for each level can be configured.

## Usage

Declare a `ImGuiAl::Log` variable somewhere. Pass the buffer and its size to the constructor, or alternatively instantiate a `ImGuiAl::BufferedLog` with the desired buffer size:

```cpp
char buffer[4096];
ImGuiAl::Log log(static_cast<void*>(buffer), sizeof(buffer));

// or

ImGuiAl::BufferedLog<4096> log();
```

Methods:

```cpp
// Output log messages.
void debug(char const* const format, ...);
void info(char const* const format, ...);
void warning(char const* const format, ...);
void error(char const* const format, ...);

void debug(char const* const format, va_list args);
void info(char const* const format, va_list args);
void warning(char const* const format, va_list args);
void error(char const* const format, va_list args);

// Clear the log.
void clear();

// As the Crt parent class. The metadata is the log level of the line.
void iterate(const std::function<bool(Info const& header, char const* const line)>& iterator);

// Make sure the last line of the log is visible.
void scrollToBottom();

// Draw the log and returns the 1-based index of the action that was pressed.
int draw(ImVec2 const& size = ImVec2(0.0f, 0.0f));

// Set the color for a log level.
void setColor(Level const level, ImU32 const color);
// Set the label for a log level.
void setLabel(Level const level, char const* const label);
// Set the label for the cummulative button.
void setCumulativeLabel(char const* const label);
// Set the label for the filter text input.
void setFilterLabel(char const* const label);
// Set the label for the filters collapsing header.
void setFilterHeaderLabel(char const* const label);
// Define an array of labels that will be drawn as buttons before the log.
// The draw function will return a 1-based index of the button that was
// pressed, if any, otherwise it will return 0.
void setActions(char const* actions[]);
```

# ImGuiAl::Terminal

A `ImGuiAl::Crt` with an embedded command input box. It is identical to its parent class, with the exception of the `execute` and `callback` functions passed to the constructor which will be called when the command input box has some content in it and Enter is pressed, and when the Up or Down arrows are pressed, respectively.

As the other two classes above, it also has a template that takes a buffer size and allocates the buffer, `ImGuiAl::BufferedTerminal`.
