/**
 * This file includes a Single-Header-Library (SHL) [1] and sets all
 * necessary flags.
 *
 * SHL: nuklear
 */

#ifndef UNIRENDER_NUKLEAR_H
#define UNIRENDER_NUKLEAR_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// set nuklear flags
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_KEYSTATE_BASED_INPUT

#include <nuklear/nuklear.h>
#include <nuklear/nuklear_glfw_gl3.h>

#endif // UNIRENDER_NUKLEAR_H
