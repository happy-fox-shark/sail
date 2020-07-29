/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2020 Dmitry Baryshev

    The MIT License

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

#ifndef SAIL_TIFF_HELPERS_H
#define SAIL_TIFF_HELPERS_H

#include <stdarg.h>
#include <stdio.h>

#include "common.h"
#include "error.h"
#include "export.h"

SAIL_HIDDEN void my_error_fn(const char *module, const char *format, va_list ap);

SAIL_HIDDEN void my_warning_fn(const char *module, const char *format, va_list ap);

SAIL_HIDDEN sail_status_t supported_read_output_pixel_format(enum SailPixelFormat pixel_format);

SAIL_HIDDEN sail_status_t tiff_compression_to_sail_compression_type(int compression, enum SailCompressionType *compression_type);

SAIL_HIDDEN sail_status_t sail_compression_type_to_tiff_compression(enum SailCompressionType compression_type, int *compression);

#endif
