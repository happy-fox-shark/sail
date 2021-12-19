/*  This file is part of SAIL (https://github.com/smoked-herring/sail)

    Copyright (c) 2021 Dmitry Baryshev

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

#ifndef SAIL_IO_MEM_CPP_H
#define SAIL_IO_MEM_CPP_H

#include <cstddef>

#ifdef SAIL_BUILD
    #include "io_base-c++.h"
#else
    #include <sail-c++/io_base-c++.h>
#endif

namespace sail
{

/*
 * Memory I/O stream.
 */
class SAIL_EXPORT io_mem : public io_base
{
public:
    /*
     * Opens the specified memory buffer for reading.
     */
    io_mem(const void *buffer, std::size_t buffer_length);

    /*
     * Opens the specified memory buffer for writing.
     */
    io_mem(void *buffer, std::size_t buffer_length);

    /*
     * Destroys the memory I/O stream.
     */
    ~io_mem() override;
};

}

#endif