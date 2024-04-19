/**
* This file implements all Single-Header-Libraries (SHL) [1] used in this
* project. If additional SHLs are included, they can also be implemented here.
*
* If the SHLs were implemented where they are used, this would lead to
* the library's implementation being recompiled with every change to the own source code file.
* By outsourcing all implementations to this file, which is comparatively rarely changed,
* compilation time can be saved.
*
* [1]: https://nicolashollmann.de/de/blog/single-header-libraries/
*/

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <unirender/stb_image.h>

#define STB_DS_IMPLEMENTATION
#include <unirender/stb_ds.h>

#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include <unirender/nuklear.h>

#define SHEREDOM_JSON_IMPLEMENTATION
#include <unirender/json.h>

