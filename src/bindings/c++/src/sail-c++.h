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

#ifndef SAIL_SAIL_CPP_H
#define SAIL_SAIL_CPP_H

// Universal include
//
#ifdef SAIL_BUILD
    #include "sail-common.h"

    #include "at_scope_exit-c++.h"
    #include "context-c++.h"
    #include "iccp-c++.h"
    #include "image-c++.h"
    #include "image_reader-c++.h"
    #include "image_writer-c++.h"
    #include "io_common-c++.h"
    #include "palette-c++.h"
    #include "plugin_info-c++.h"
    #include "read_features-c++.h"
    #include "read_options-c++.h"
    #include "write_features-c++.h"
    #include "write_options-c++.h"
    #include "utils-c++.h"
#else
    #include <sail-common/sail-common.h>

    #include <sail-c++/at_scope_exit-c++.h>
    #include <sail-c++/context-c++.h>
    #include <sail-c++/iccp-c++.h>
    #include <sail-c++/image-c++.h>
    #include <sail-c++/image_reader-c++.h>
    #include <sail-c++/image_writer-c++.h>
    #include <sail-c++/io_common-c++.h>
    #include <sail-c++/palette-c++.h>
    #include <sail-c++/plugin_info-c++.h>
    #include <sail-c++/read_features-c++.h>
    #include <sail-c++/read_options-c++.h>
    #include <sail-c++/write_features-c++.h>
    #include <sail-c++/write_options-c++.h>
    #include <sail-c++/utils-c++.h>
#endif

#endif
