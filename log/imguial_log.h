/*
The MIT License (MIT)

Copyright (c) 2016 Andre Leiradella

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <imgui.h>
#include <stdarg.h>

namespace ImGuiAl
{
  class Log
  {
  public:
    enum Level
    {
      kDebug = 0,
      kInfo  = 1,
      kWarn  = 2,
      kError = 3
    };
    
    Log();
    virtual ~Log();
    
    inline void SetHistory( int lines )
    {
      m_History = lines > 0 ? lines : 1;
    }
    
    void SetColor( Level level, float r, float g, float b );
    
    void VPrintf( Level level, const char* format, va_list args );
    
    void Debug( const char* format, ... );
    void Info( const char* format, ... );
    void Warn( const char* format, ... );
    void Error( const char* format, ... );
    
    void Clear();
    
    void Draw();
    
  protected:
    ImVector< const char* > m_Items;
    int             m_History;
    Level           m_Level;
    bool            m_Cumulative;
    ImGuiTextFilter m_Filter;
    bool            m_ScrollToBottom;
    ImColor         m_Colors[ 4 ][ 4 ];
  };
}
