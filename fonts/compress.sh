#!/bin/sh

# Needs cURL

# Needs https://github.com/ocornut/imgui/blob/master/misc/fonts/$COMPRESS.cpp
# g++ -O3 imgui/misc/fonts/$COMPRESS.cpp -o $COMPRESS
COMPRESS="`pwd`/binary_to_compressed_c"

rm *.inl
mkdir -p temp && cd temp

# Random fonts

curl -o cft.ttf "https://raw.githubusercontent.com/chrissimpkins/codeface/master/fonts/coding-font-tobi/cft.ttf"
$COMPRESS cft.ttf CodingFontTobi > ../CodingFontTobi.inl

curl -o Cousine.zip "https://fonts.google.com/download?family=Cousine"
unzip -oj Cousine.zip
$COMPRESS Cousine-BoldItalic.ttf CousineBoldItalic > ../CousineBoldItalic.inl
$COMPRESS Cousine-Bold.ttf CousineBold > ../CousineBold.inl
$COMPRESS Cousine-Italic.ttf CousineItalic > ../CousineItalic.inl
$COMPRESS Cousine-Regular.ttf CousineRegular > ../CousineRegular.inl

curl -o Crisp.ttf "https://raw.githubusercontent.com/chrissimpkins/codeface/master/fonts/crisp/Crisp.ttf"
$COMPRESS Crisp.ttf Crisp > ../Crisp.inl

curl -o Roboto.zip "https://fonts.google.com/download?family=Roboto"
unzip -oj Roboto.zip
$COMPRESS Roboto-Thin.ttf RobotoThin > ../RobotoThin.inl
$COMPRESS Roboto-ThinItalic.ttf RobotoThinItalic > ../RobotoThinItalic.inl
$COMPRESS Roboto-Light.ttf RobotoLight > ../RobotoLight.inl
$COMPRESS Roboto-LightItalic.ttf RobotoLightItalic. > ../RobotoLightItalic.inl
$COMPRESS Roboto-Regular.ttf RobotoRegular > ../RobotoRegular.inl
$COMPRESS Roboto-Italic.ttf RobotoItalic > ../RobotoItalic.inl
$COMPRESS Roboto-Medium.ttf RobotoMedium > ../RobotoMedium.inl
$COMPRESS Roboto-MediumItalic.ttf RobotoMediumItalic > ../RobotoMediumItalic.inl
$COMPRESS Roboto-Bold.ttf RobotoBold > ../RobotoBold.inl
$COMPRESS Roboto-BoldItalic.ttf RobotoBoldItalic > ../RobotoBoldItalic.inl
$COMPRESS Roboto-Black.ttf RobotoBlack > ../RobotoBlack.inl
$COMPRESS Roboto-BlackItalic.ttf RobotoBlackItalic > ../RobotoBlackItalic.inl

curl -o Karla.zip "https://fonts.google.com/download?family=Karla"
unzip -oj Karla.zip
$COMPRESS Karla-ExtraLight.ttf KarlaExtraLight > ../KarlaExtraLight.inl
$COMPRESS Karla-Light.ttf KarlaLight > ../KarlaLight.inl
$COMPRESS Karla-Regular.ttf KarlaRegular > ../KarlaRegular.inl
$COMPRESS Karla-Medium.ttf KarlaMedium > ../KarlaMedium.inl
$COMPRESS Karla-SemiBold.ttf KarlaSemiBold > ../KarlaSemiBold.inl
$COMPRESS Karla-Bold.ttf KarlaBold > ../KarlaBold.inl
$COMPRESS Karla-ExtraBold.ttf KarlaExtraBold > ../KarlaExtraBold.inl
$COMPRESS Karla-ExtraLightItalic.ttf KarlaExtraLightItalic > ../KarlaExtraLightItalic.inl
$COMPRESS Karla-LightItalic.ttf KarlaLightItalic > ../KarlaLightItalic.inl
$COMPRESS Karla-Italic.ttf KarlaItalic > ../KarlaItalic.inl
$COMPRESS Karla-MediumItalic.ttf KarlaMediumItalic > ../KarlaMediumItalic.inl
$COMPRESS Karla-SemiBoldItalic.ttf KarlaSemiBoldItalic > ../KarlaSemiBoldItalic.inl
$COMPRESS Karla-BoldItalic.ttf KarlaBoldItalic > ../KarlaBoldItalic.inl
$COMPRESS Karla-ExtraBoldItalic.ttf KarlaExtraBoldItalic > ../KarlaExtraBoldItalic.inl
$COMPRESS Karla-VariableFont_wght.ttf KarlaVariableFont > ../KarlaVariableFont.inl
$COMPRESS Karla-Italic-VariableFont_wght.ttf KarlaItalicVariableFont > ../KarlaItalicVariableFont.inl

curl -o PixelCarnageMono.ttf.zip "http://www.proggyfonts.net/download/PixelCarnageMono.ttf.zip"
unzip -oj PixelCarnageMono.ttf.zip
$COMPRESS PixelCarnageMono.ttf PixelCarnageMono > ../PixelCarnageMono.inl

curl -o ProggyClean.ttf.zip "http://www.proggyfonts.net/download/ProggyClean.ttf.zip"
unzip -oj ProggyClean.ttf.zip
$COMPRESS ProggyCleanCE.ttf ProggyCleanCE > ../ProggyCleanCE.inl
$COMPRESS ProggyClean.ttf ProggyClean > ../ProggyClean.inl

curl -o ProggyCleanSZ.ttf.zip "http://www.proggyfonts.net/download/ProggyCleanSZ.ttf.zip"
unzip -oj ProggyCleanSZ.ttf.zip
$COMPRESS ProggyCleanSZ.ttf ProggyCleanSZ > ../ProggyCleanSZ.inl

curl -o ProggySmall.ttf.zip "http://www.proggyfonts.net/download/ProggySmall.ttf.zip"
unzip -oj ProggySmall.ttf.zip
$COMPRESS ProggySmall.ttf ProggySmall > ../ProggySmall.inl

curl -o ProggySquare.ttf.zip "http://www.proggyfonts.net/download/ProggySquare.ttf.zip"
unzip -oj ProggySquare.ttf.zip
$COMPRESS ProggySquare.ttf ProggySquare > ../ProggySquare.inl

curl -o ProggySquareSZ.ttf.zip "http://www.proggyfonts.net/download/ProggySquareSZ.ttf.zip"
unzip -oj ProggySquareSZ.ttf.zip
$COMPRESS ProggySquareSZ.ttf ProggySquareSZ > ../ProggySquareSZ.inl

curl -o ProggyTiny.ttf.zip "http://www.proggyfonts.net/download/ProggyTiny.ttf.zip"
unzip -oj ProggyTiny.ttf.zip
$COMPRESS ProggyTiny.ttf ProggyTiny > ../ProggyTiny.inl

curl -o ProggyTinySZ.ttf.zip "http://www.proggyfonts.net/download/ProggyTinySZ.ttf.zip"
unzip -oj ProggyTinySZ.ttf.zip
$COMPRESS ProggyTinySZ.ttf ProggyTinySZ > ../ProggyTinySZ.inl

# Fonts supported by https://github.com/juliettef/IconFontCppHeaders

# Font Awesome 4
curl -o FontAwesome.otf "https://raw.githubusercontent.com/FortAwesome/Font-Awesome/4.x/fonts/FontAwesome.otf"
$COMPRESS FontAwesome.otf FontAwesome4 > ../FontAwesome4.inl

# Font Awesome 5 free
curl -o fontawesome-free-5.15.4-desktop.zip "https://use.fontawesome.com/releases/v5.15.4/fontawesome-free-5.15.4-desktop.zip"
unzip -oj fontawesome-free-5.15.4-desktop.zip
$COMPRESS "Font Awesome 5 Brands-Regular-400.otf" FontAwesome5Brands400 > ../FontAwesome5Brands400.inl
$COMPRESS "Font Awesome 5 Free-Regular-400.otf" FontAwesome5Regular400 > ../FontAwesome5Regular400.inl
$COMPRESS "Font Awesome 5 Free-Solid-900.otf" FontAwesome5Solid900 > ../FontAwesome5Solid900.inl

# Font Awesome 6 free
curl -o fontawesome-free-6.1.1-desktop.zip "https://use.fontawesome.com/releases/v6.1.1/fontawesome-free-6.1.1-desktop.zip"
unzip -oj fontawesome-free-6.1.1-desktop.zip
$COMPRESS "Font Awesome 6 Brands-Regular-400.otf" FontAwesome6Brands400 > ../FontAwesome6Brands400.inl
$COMPRESS "Font Awesome 6 Free-Regular-400.otf" FontAwesome6Regular400 > ../FontAwesome6Regular400.inl
$COMPRESS "Font Awesome 6 Free-Solid-900.otf" FontAwesome6Solid900 > ../FontAwesome6Solid900.inl

# Fork Awesome
curl -o Fork-Awesome-1.2.0.zip "https://codeload.github.com/ForkAwesome/Fork-Awesome/zip/refs/tags/1.2.0"
unzip -oj Fork-Awesome-1.2.0.zip
$COMPRESS forkawesome-webfont.ttf ForkAwesome > ../ForkAwesome.inl

# Google Material Design icons
curl -o MaterialIcons-Regular.ttf "https://raw.githubusercontent.com/google/material-design-icons/master/font/MaterialIcons-Regular.ttf"
$COMPRESS MaterialIcons-Regular.ttf MaterialDesign > ../MaterialDesign.inl

# Kenney Game icons and Game icons expansion
curl -o kenney-icon-font.ttf "https://raw.githubusercontent.com/nicodinh/kenney-icon-font/master/fonts/kenney-icon-font.ttf"
$COMPRESS kenney-icon-font.ttf KenneyIcons > ../KenneyIcons.inl

# Fontaudio
curl -o fontaudio.ttf "https://raw.githubusercontent.com/fefanto/fontaudio/master/font/fontaudio.ttf"
$COMPRESS fontaudio.ttf FontAudio > ../FontAudio.inl

# Clean up
cd ..
rm -rf temp
