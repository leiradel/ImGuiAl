#pragma once

// Define these here or somewhere else to add fonts to your imgui app.
//#define IMGUIAL_FONTS_COUSINE_REGULAR
//#define IMGUIAL_FONTS_DROID_SANS
//#define IMGUIAL_FONTS_KARLA_REGULAR
//#define IMGUIAL_FONTS_PROGGY_TINY
//#define IMGUIAL_FONTS_FONT_AWESOME
//#define IMGUIAL_FONTS_MATERIAL_DESIGN
//#define IMGUIAL_FONTS_KENNEY_ICONS

#ifdef IMGUIAL_FONTS_FONT_AWESOME
#include "IconsFontAwesome_c.h"
#endif

#ifdef IMGUIAL_FONTS_MATERIAL_DESIGN
#include "IconsMaterialDesign_c.h"
#endif

#ifdef IMGUIAL_FONTS_KENNEY_ICONS
#include "IconsKenney_c.h"
#endif

namespace ImGuiAl
{
  namespace Fonts
  {
    enum Font
    {
      kCousineRegular,
      kDroidSans,
      kKarlaRegular,
      kProggyTiny,
      kFontAwesome,
      kMaterialDesign,
      kKenneyIcons
    };
    
    const void* GetCompressedData( Font font, int* size );
  }
}
