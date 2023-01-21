#pragma once

#define STRINGIFY(str) #str
#define XSTRINGIFY(str) STRINGIFY(str)

#define TWO_TRUE( A, B, C ) A && ( B || C ) || ( B && C)
