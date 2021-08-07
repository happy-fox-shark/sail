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

#include <utility>

#include "sail-c++.h"

#include "munit.h"

static MunitResult test_write_features(const MunitParameter params[], void *user_data) {
    (void)params;
    (void)user_data;

    const std::vector<sail::codec_info> codecs = sail::codec_info::list();
    munit_assert(codecs.size() > 0U);

    const sail::codec_info first_codec = codecs.front();

    // Access features
    {
        const int features = first_codec.write_features().features();
    }

    // Copy
    {
        const sail::write_features write_features = first_codec.write_features();
        munit_assert(write_features.features() == first_codec.write_features().features());
    }

    // Move
    {
        const sail::write_features write_features1 = std::move(first_codec.write_features());
        const sail::write_features write_features = std::move(write_features1);
        munit_assert(write_features.features() == first_codec.write_features().features());
    }

    // Construct write options
    {
        sail::write_options write_options;
        munit_assert(first_codec.write_features().to_write_options(&write_options) == SAIL_OK);
    }

    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { (char *)"/write-features", test_write_features, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char *)"/bindings/c++",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}