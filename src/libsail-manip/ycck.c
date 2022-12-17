/*  This file is part of SAIL (https://github.com/HappySeaFox/sail)

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

#include "sail-manip.h"

#include "cmyk.h"
#include "ycbcr.h"

/*
 * Pre-compiled intermediate values for YCCK -> RGB conversion like that:
 *
 *    for (int i = 0; i < 256; i++) {
 *        CR_R[i] = (int)round(1.40200 * i);
 *        CB_G[i] = (int)round(0.34414 * i);
 *        CR_G[i] = (int)round(0.71414 * i);
 *        CB_B[i] = (int)round(1.77200 * i);
 *    }
 *
 * See also https://en.wikipedia.org/wiki/YCbCr
 */

static const uint16_t CR_R[256] = { 0,    1,    3,    4,    6,    7,    8,   10,   11,   13,   14,   15,   17,   18,   20,   21,   22,   24,   25,   27,   28,   29,   31,   32,   34,   35,   36,   38,   39,   41,   42,   43,   45,   46,   48,   49,   50,   52,   53,   55,   56,   57,   59,   60,   62,   63,   64,   66,   67,   69,   70,   72,   73,   74,   76,   77,   79,   80,   81,   83,   84,   86,   87,   88,   90,   91,   93,   94,   95,   97,   98,  100,  101,  102,  104,  105,  107,  108,  109,  111,  112,  114,  115,  116,  118,  119,  121,  122,  123,  125,  126,  128,  129,  130,  132,  133,  135,  136,  137,  139,  140,  142,  143,  144,  146,  147,  149,  150,  151,  153,  154,  156,  157,  158,  160,  161,  163,  164,  165,  167,  168,  170,  171,  172,  174,  175,  177,  178,  179,  181,  182,  184,  185,  186,  188,  189,  191,  192,  193,  195,  196,  198,  199,  200,  202,  203,  205,  206,  207,  209,  210,  212,  213,  215,  216,  217,  219,  220,  222,  223,  224,  226,  227,  229,  230,  231,  233,  234,  236,  237,  238,  240,  241,  243,  244,  245,  247,  248,  250,  251,  252,  254,  255,  257,  258,  259,  261,  262,  264,  265,  266,  268,  269,  271,  272,  273,  275,  276,  278,  279,  280,  282,  283,  285,  286,  287,  289,  290,  292,  293,  294,  296,  297,  299,  300,  301,  303,  304,  306,  307,  308,  310,  311,  313,  314,  315,  317,  318,  320,  321,  322,  324,  325,  327,  328,  329,  331,  332,  334,  335,  336,  338,  339,  341,  342,  343,  345,  346,  348,  349,  351,  352,  353,  355,  356,  358, };
static const uint16_t CB_G[256] = { 0,    0,    1,    1,    1,    2,    2,    2,    3,    3,    3,    4,    4,    4,    5,    5,    6,    6,    6,    7,    7,    7,    8,    8,    8,    9,    9,    9,   10,   10,   10,   11,   11,   11,   12,   12,   12,   13,   13,   13,   14,   14,   14,   15,   15,   15,   16,   16,   17,   17,   17,   18,   18,   18,   19,   19,   19,   20,   20,   20,   21,   21,   21,   22,   22,   22,   23,   23,   23,   24,   24,   24,   25,   25,   25,   26,   26,   26,   27,   27,   28,   28,   28,   29,   29,   29,   30,   30,   30,   31,   31,   31,   32,   32,   32,   33,   33,   33,   34,   34,   34,   35,   35,   35,   36,   36,   36,   37,   37,   38,   38,   38,   39,   39,   39,   40,   40,   40,   41,   41,   41,   42,   42,   42,   43,   43,   43,   44,   44,   44,   45,   45,   45,   46,   46,   46,   47,   47,   47,   48,   48,   49,   49,   49,   50,   50,   50,   51,   51,   51,   52,   52,   52,   53,   53,   53,   54,   54,   54,   55,   55,   55,   56,   56,   56,   57,   57,   57,   58,   58,   59,   59,   59,   60,   60,   60,   61,   61,   61,   62,   62,   62,   63,   63,   63,   64,   64,   64,   65,   65,   65,   66,   66,   66,   67,   67,   67,   68,   68,   68,   69,   69,   70,   70,   70,   71,   71,   71,   72,   72,   72,   73,   73,   73,   74,   74,   74,   75,   75,   75,   76,   76,   76,   77,   77,   77,   78,   78,   78,   79,   79,   79,   80,   80,   81,   81,   81,   82,   82,   82,   83,   83,   83,   84,   84,   84,   85,   85,   85,   86,   86,   86,   87,   87,   87,   88, };
static const uint16_t CR_G[256] = { 0,    1,    1,    2,    3,    4,    4,    5,    6,    6,    7,    8,    9,    9,   10,   11,   11,   12,   13,   14,   14,   15,   16,   16,   17,   18,   19,   19,   20,   21,   21,   22,   23,   24,   24,   25,   26,   26,   27,   28,   29,   29,   30,   31,   31,   32,   33,   34,   34,   35,   36,   36,   37,   38,   39,   39,   40,   41,   41,   42,   43,   44,   44,   45,   46,   46,   47,   48,   49,   49,   50,   51,   51,   52,   53,   54,   54,   55,   56,   56,   57,   58,   59,   59,   60,   61,   61,   62,   63,   64,   64,   65,   66,   66,   67,   68,   69,   69,   70,   71,   71,   72,   73,   74,   74,   75,   76,   76,   77,   78,   79,   79,   80,   81,   81,   82,   83,   84,   84,   85,   86,   86,   87,   88,   89,   89,   90,   91,   91,   92,   93,   94,   94,   95,   96,   96,   97,   98,   99,   99,  100,  101,  101,  102,  103,  104,  104,  105,  106,  106,  107,  108,  109,  109,  110,  111,  111,  112,  113,  114,  114,  115,  116,  116,  117,  118,  119,  119,  120,  121,  121,  122,  123,  124,  124,  125,  126,  126,  127,  128,  129,  129,  130,  131,  131,  132,  133,  134,  134,  135,  136,  136,  137,  138,  139,  139,  140,  141,  141,  142,  143,  144,  144,  145,  146,  146,  147,  148,  149,  149,  150,  151,  151,  152,  153,  154,  154,  155,  156,  156,  157,  158,  159,  159,  160,  161,  161,  162,  163,  164,  164,  165,  166,  166,  167,  168,  169,  169,  170,  171,  171,  172,  173,  174,  174,  175,  176,  176,  177,  178,  179,  179,  180,  181,  181,  182, };
static const uint16_t CB_B[256] = { 0,    2,    4,    5,    7,    9,   11,   12,   14,   16,   18,   19,   21,   23,   25,   27,   28,   30,   32,   34,   35,   37,   39,   41,   43,   44,   46,   48,   50,   51,   53,   55,   57,   58,   60,   62,   64,   66,   67,   69,   71,   73,   74,   76,   78,   80,   82,   83,   85,   87,   89,   90,   92,   94,   96,   97,   99,  101,  103,  105,  106,  108,  110,  112,  113,  115,  117,  119,  120,  122,  124,  126,  128,  129,  131,  133,  135,  136,  138,  140,  142,  144,  145,  147,  149,  151,  152,  154,  156,  158,  159,  161,  163,  165,  167,  168,  170,  172,  174,  175,  177,  179,  181,  183,  184,  186,  188,  190,  191,  193,  195,  197,  198,  200,  202,  204,  206,  207,  209,  211,  213,  214,  216,  218,  220,  222,  223,  225,  227,  229,  230,  232,  234,  236,  237,  239,  241,  243,  245,  246,  248,  250,  252,  253,  255,  257,  259,  260,  262,  264,  266,  268,  269,  271,  273,  275,  276,  278,  280,  282,  284,  285,  287,  289,  291,  292,  294,  296,  298,  299,  301,  303,  305,  307,  308,  310,  312,  314,  315,  317,  319,  321,  323,  324,  326,  328,  330,  331,  333,  335,  337,  338,  340,  342,  344,  346,  347,  349,  351,  353,  354,  356,  358,  360,  361,  363,  365,  367,  369,  370,  372,  374,  376,  377,  379,  381,  383,  385,  386,  388,  390,  392,  393,  395,  397,  399,  400,  402,  404,  406,  408,  409,  411,  413,  415,  416,  418,  420,  422,  424,  425,  427,  429,  431,  432,  434,  436,  438,  439,  441,  443,  445,  447,  448,  450,  452, };

void convert_ycck32_to_rgba32(uint8_t y, uint8_t cb, uint8_t cr, uint8_t k, sail_rgba32_t *rgba32) {

    rgba32->component1 = (uint8_t)(SAIL_MAX(0, SAIL_MIN(255, y            + CR_R[cr] - 179.45600)));
    rgba32->component2 = (uint8_t)(SAIL_MAX(0, SAIL_MIN(255, y - CB_G[cb] - CR_G[cr] + 135.45984)));
    rgba32->component3 = (uint8_t)(SAIL_MAX(0, SAIL_MIN(255, y + CB_B[cb]            - 226.81600)));
    rgba32->component4 = 255;

    rgba32->component1 = 255 - rgba32->component1;
    rgba32->component2 = 255 - rgba32->component2;
    rgba32->component3 = 255 - rgba32->component3;

    convert_cmyk32_to_rgba32(rgba32->component1, rgba32->component2, rgba32->component3, k, rgba32);
}
