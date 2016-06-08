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

#include <imguial_log.h>
#include <stdio.h>

ImGuiAl::Log::Log()
{
  m_Level = kDebug;
  m_Cumulative = true;
  m_History = 256;
  
  SetColor( kDebug, 0.0f, 0.6f, 1.0f );
  SetColor( kInfo,  0.0f, 1.0f, 0.4f );
  SetColor( kWarn,  0.8f, 0.8f, 0.0f );
  SetColor( kError, 1.0f, 0.3f, 0.3f );
}

ImGuiAl::Log::~Log()
{
  Clear();
}

void ImGuiAl::Log::SetColor( Level level, float r, float g, float b )
{
  float h, s, v;
  ImGui::ColorConvertRGBtoHSV( r, g, b, h, s, v );
  
  v -= 0.3f;
  
  m_Colors[ level ][ 0 ] = ImColor( r, g, b );
  m_Colors[ level ][ 1 ] = ImColor::HSV( h, s, v );
  m_Colors[ level ][ 2 ] = ImColor::HSV( h, s, v + 0.1f );
  m_Colors[ level ][ 3 ] = ImColor::HSV( h, s, v + 0.2f );
}

void ImGuiAl::Log::VPrintf( Level level, const char* format, va_list args )
{
  if ( level >= 0 && level <= 3 )
  {
    char buffer[ 1024 ];
    
    buffer[ 0 ] = '0' + level;
    
    vsnprintf( buffer + 1, sizeof( buffer ) - 1, format, args );
    buffer[ sizeof( buffer ) - 1 ] = 0;
    
    const char* line = strdup( buffer );
    
    if ( line )
    {
      m_Items.push_back( line );
      m_ScrollToBottom = true;
    }
    
    if ( m_Items.Size > m_History )
    {
      free( (void*)m_Items[ 0 ] );
      m_Items.erase( m_Items.begin() );
    }
  }
}

void ImGuiAl::Log::Debug( const char* format, ... )
{
  va_list args;
  va_start( args, format );
  VPrintf( kDebug, format, args );
  va_end( args );
}

void ImGuiAl::Log::Info( const char* format, ... )
{
  va_list args;
  va_start( args, format );
  VPrintf( kInfo, format, args );
  va_end( args );
}

void ImGuiAl::Log::Warn( const char* format, ... )
{
  va_list args;
  va_start( args, format );
  VPrintf( kWarn, format, args );
  va_end( args );
}

void ImGuiAl::Log::Error( const char* format, ... )
{
  va_list args;
  va_start( args, format );
  VPrintf( kError, format, args );
  va_end( args );
}

void ImGuiAl::Log::Clear()
{
  for ( int i = 0; i < m_Items.Size; i++ )
  {
    free( (void*)m_Items[ i ] );
  }
  
  m_Items.clear();
  m_ScrollToBottom = true;
}

void ImGuiAl::Log::Draw()
{
  if ( ImGui::CollapsingHeader( "Filters" ) )
  {
    ImGui::PushStyleColor( ImGuiCol_Button, m_Colors[ kDebug ][ 1 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, m_Colors[ kDebug ][ 2 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, m_Colors[ kDebug ][ 3 ] );
    bool ok = ImGui::Button( "Debug" );
    ImGui::PopStyleColor( 3 );

    if ( ok )
    {
      m_Level = kDebug;
      m_ScrollToBottom = true;
    }
    
    ImGui::SameLine();
    
    ImGui::PushStyleColor( ImGuiCol_Button, m_Colors[ kInfo ][ 1 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, m_Colors[ kInfo ][ 2 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, m_Colors[ kInfo ][ 3 ] );
    ok = ImGui::Button( "Info" );
    ImGui::PopStyleColor( 3 );

    if ( ok )
    {
      m_Level = kInfo;
      m_ScrollToBottom = true;
    }
    
    ImGui::SameLine();
    
    ImGui::PushStyleColor( ImGuiCol_Button, m_Colors[ kWarn ][ 1 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, m_Colors[ kWarn ][ 2 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, m_Colors[ kWarn ][ 3 ] );
    ok = ImGui::Button( "Warn" );
    ImGui::PopStyleColor( 3 );

    if ( ok )
    {
      m_Level = kWarn;
      m_ScrollToBottom = true;
    }
    
    ImGui::SameLine();
    
    ImGui::PushStyleColor( ImGuiCol_Button, m_Colors[ kError ][ 1 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonHovered, m_Colors[ kError ][ 2 ] );
    ImGui::PushStyleColor( ImGuiCol_ButtonActive, m_Colors[ kError ][ 3 ] );
    ok = ImGui::Button( "Error" );
    ImGui::PopStyleColor( 3 );

    if ( ok )
    {
      m_Level = kError;
      m_ScrollToBottom = true;
    }
    
    ImGui::SameLine();
    
    ImGui::Checkbox( "Cumulative", &m_Cumulative );
    
    ImGui::SameLine();
    
    if ( ImGui::Button( "Clear" ) )
    {
      Clear();
    }
    
    m_Filter.Draw();
  }
  
  // Do I need an unique id in BeginChild?
  char id[ 64 ];
  snprintf( id, sizeof( id ), "console_%p", this );
  id[ sizeof( id ) - 1 ] = 0;
  
  ImGui::BeginChild( id, ImVec2( 0, -ImGui::GetItemsLineHeightWithSpacing() ), false, ImGuiWindowFlags_HorizontalScrollbar );
  
  ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 4, 1 ) );
  
  for ( int i = 0; i < m_Items.Size; i++ )
  {
    const char* item = m_Items[ i ];
    int level = *item++ - '0';
    
    bool show = ( m_Cumulative && level >= m_Level ) || level == m_Level;
    
    if ( show && m_Filter.PassFilter( item ) )
    {
      ImGui::PushStyleColor( ImGuiCol_Text, m_Colors[ level ][ 0 ].Value );
      ImGui::TextUnformatted( item );
      ImGui::PopStyleColor();
    }
  }
  
  if ( m_ScrollToBottom )
  {
    ImGui::SetScrollHere();
    m_ScrollToBottom = false;
  }
  
  ImGui::PopStyleVar();
  ImGui::EndChild();
}
