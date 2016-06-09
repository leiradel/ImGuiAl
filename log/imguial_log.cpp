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
#include <stdlib.h>
#include <stdio.h>

// Must be at most 65535
#define MAX_LINE_SIZE 1024

ImGuiAl::Log::~Log()
{
  free( m_Buffer );
}

bool ImGuiAl::Log::Init( size_t buf_size )
{
  if ( buf_size < MAX_LINE_SIZE + 2 )
  {
    // buf_size must be enough to hold one line plus its length encoded in two bytes.
    return false;
  }
  
  m_Buffer = (char*)malloc( buf_size );
  
  if ( m_Buffer == NULL )
  {
    return false;
  }
  
  m_Size = buf_size;
  m_Avail = buf_size;
  m_Level = kDebug;
  m_Cumulative = true;
  m_First = m_Last = 0;
  
  SetColor( kDebug, 0.0f, 0.6f, 1.0f );
  SetColor( kInfo,  0.0f, 1.0f, 0.4f );
  SetColor( kWarn,  0.8f, 0.8f, 0.0f );
  SetColor( kError, 1.0f, 0.3f, 0.3f );
  
  return true;
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
  level = (Level)( level & 3 );
  
  char line[ MAX_LINE_SIZE ];
  size_t length = vsnprintf( line, sizeof( line ), format, args );
  
  if ( length > sizeof( line ) )
  {
    // Line size too small, truncated. Consider increasing the array size.
    length = sizeof( line );
  }
  
  length += 3; // Add one byte for the level and two bytes for the length.
  
  if ( length > m_Avail )
  {
    do
    {
      // Remove content until we have enough space.
      unsigned char meta[ 3 ];
      Read( meta, 3 );
      Skip( meta[ 1 ] | meta[ 2 ] << 8 ); // Little endian.
    }
    while ( length > m_Avail );
  }
  
  unsigned char meta[ 3 ];
  length -= 3;
  
  meta[ 0 ] = level;
  meta[ 1 ] = length & 0xff;
  meta[ 2 ] = length >> 8;
  
  Write( meta, 3 );
  Write( line, length );
  
  m_ScrollToBottom = true;
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

void ImGuiAl::Log::Draw( bool filters )
{
  if ( filters && ImGui::CollapsingHeader( "Filters" ) )
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
  
  size_t pos = m_First;
  
  while ( pos != m_Last )
  {
    char line[ MAX_LINE_SIZE + 1 ];
    unsigned char meta[ 3 ];
    pos = Peek( pos, meta, 3 );
    
    Level level = (Level)meta[ 0 ];
    size_t length = meta[ 1 ] | meta[ 2 ] << 8;
    pos = Peek( pos, line, length );
    line[ length ] = 0;
    
    bool show = ( m_Cumulative && level >= m_Level ) || level == m_Level;
    
    if ( show && m_Filter.PassFilter( line ) )
    {
      ImGui::PushStyleColor( ImGuiCol_Text, m_Colors[ level ][ 0 ].Value );
      ImGui::TextUnformatted( line );
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

void ImGuiAl::Log::Write( const void* data, size_t size )
{
  size_t first = size;
  size_t second = 0;
  
  if ( first > m_Size - m_Last )
  {
    first = m_Size - m_Last;
    second = size - first;
  }
  
  char* dest = m_Buffer + m_Last;
  memcpy( dest, data, first );
  memcpy( m_Buffer, (char*)data + first, second );
  
  m_Last = ( m_Last + size ) % m_Size;
  m_Avail -= size;
}

void ImGuiAl::Log::Read( void* data, size_t size )
{
  size_t first = size;
  size_t second = 0;
  
  if ( first > m_Size - m_First )
  {
    first = m_Size - m_First;
    second = size - first;
  }
  
  char* src = m_Buffer + m_First;
  memcpy( data, src, first );
  memcpy( (char*)data + first, m_Buffer, second );
  
  m_First = ( m_First + size ) % m_Size;
  m_Avail += size;
}

size_t ImGuiAl::Log::Peek( size_t pos, void* data, size_t size )
{
  size_t first = size;
  size_t second = 0;
  
  if ( first > m_Size - pos )
  {
    first = m_Size - pos;
    second = size - first;
  }
  
  char* src = m_Buffer + pos;
  memcpy( data, src, first );
  memcpy( (char*)data + first, m_Buffer, second );
  
  return ( pos + size ) % m_Size;
}
