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
#include <float.h>

namespace ImGuiAl {
    class Sparkline {
    public:
        Sparkline(void* const buffer, size_t const size) {
            _values = static_cast<float*>(buffer);
            _count = size / sizeof(float);
            _auto = true;
            clear();
        }

        void setLimits(float const min, float const max) {
            _min = min;
            _max = max;
            _auto = false;
        }

        void add(float const value) {
            _offset = (_offset + 1) % _count;
            _values[_offset] = value;
        }

        void clear() {
            memset(_values, 0, _count * sizeof(float));
            _offset = _count - 1;
        }

        void draw(char const* const label = "", ImVec2 const size = ImVec2()) const {
            char overlay[32];
            snprintf(overlay, sizeof(overlay), "%f", _values[_offset]);

            float min = _min, max = _max;

            if (_auto) {
                min = FLT_MAX;
                max = -FLT_MAX;

                for (size_t i = 0; i < _count; i++) {
                    float const value = _values[i];
                    min = std::min(min, value);
                    max = std::max(max, value);
                }
            }

            ImGui::PlotLines(label, getValue, const_cast<Sparkline*>(this), _count, 0, overlay, min, max, size);
        }

    protected:
        float* _values;
        size_t _count;
        bool _auto;
        float _min, _max;
        size_t _offset;

        static float getValue(void* const data, int const idx) {
            Sparkline const* const self = static_cast<Sparkline*>(data);
            size_t const index = (idx + self->_offset + 1) % self->_count;
            return self->_values[index];
        }
    };

    template<size_t S>
    class BufferedSparkline : public Sparkline {
    public:
        BufferedSparkline() : Sparkline(_buffer, sizeof(_buffer)) {}

    protected:
        float _buffer[S];
    };
}
