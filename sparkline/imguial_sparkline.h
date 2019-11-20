/*
The MIT License (MIT)

Copyright (c) 2019 Andre Leiradella

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
#include <stddef.h>
#include <stdio.h>

namespace ImGuiAl {
    template<typename T, size_t L>
    class Sparkline {
        public:
            Sparkline() {
                setLimits(0, 1);
                clear();
            }

            void setLimits(T const min, T const max) {
                _min = static_cast<float>(min);
                _max = static_cast<float>(max);
            }

            void add(T const value) {
                _offset = (_offset + 1) % L;
                _values[_offset] = value;
            }

            void clear() {
                memset(_values, 0, L * sizeof(T));
                _offset = L - 1;
            }

            void draw(char const* const label = "", ImVec2 const size = ImVec2()) const {
                char overlay[32];
                print(overlay, sizeof(overlay), _values[_offset]);
                ImGui::PlotLines(label, getValue, const_cast<Sparkline*>(this), L, 0, overlay, _min, _max, size);
            }

        protected:
            float _min, _max;
            T _values[L];
            size_t _offset;

            static float getValue(void* const data, int const idx) {
                Sparkline const* const self = static_cast<Sparkline*>(data);
                size_t const index = (idx + self->_offset + 1) % L;
                return static_cast<float>(self->_values[index]);
            }

            static void print(char* const buffer, size_t const bufferLen, int const value) {
                snprintf(buffer, bufferLen, "%d", value);
            }

            static void print(char* const buffer, size_t const bufferLen, double const value) {
                snprintf(buffer, bufferLen, "%f", value);
            }
    };
}
