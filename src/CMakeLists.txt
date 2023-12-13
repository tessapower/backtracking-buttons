set(ALG_HEADERS "${backtracking_buttons_SOURCE_DIR}/include/alg/algorithms.h")

add_library(alg STATIC alg/algorithms.cpp ${ALG_HEADERS})

target_compile_definitions(alg PRIVATE "-DPPM_FILES=\"${PROJECT_SOURCE_DIR}//ppm//\"")

# Support <alg/algorithms.h> imports in public headers
target_include_directories(alg PUBLIC ../include)
# Support "algorithms.h" imports in private headers and source files
target_include_directories(alg PRIVATE ../include/alg)

set(GEOM_HEADERS
        "${backtracking_buttons_SOURCE_DIR}/include/geom/circle.h"
        "${backtracking_buttons_SOURCE_DIR}/include/geom/color.h"
        "${backtracking_buttons_SOURCE_DIR}/include/geom/point.h"
        "${backtracking_buttons_SOURCE_DIR}/include/geom/rect.h"
        )

add_library(geom STATIC
        geom/circle.cpp
        geom/point.cpp
        geom/rect.cpp
        ${ALG_HEADERS}
        )

# Support <geom/circle.h> imports in public headers
target_include_directories(geom PUBLIC ../include)
# Support "circle.h" imports in private headers and source files
target_include_directories(geom PRIVATE ../include/geom)

set(IMG_HEADERS
        "${backtracking_buttons_SOURCE_DIR}/include/img/pixel.h"
        "${backtracking_buttons_SOURCE_DIR}/include/img/scan.h"
        )

add_library(img STATIC img/scan.cpp ${ALG_HEADERS})

target_compile_definitions(img PRIVATE "-DPPM_FILES=\"${PROJECT_SOURCE_DIR}//ppm//\"")

# Support <alg/algorithms.h> imports in public headers
target_include_directories(img PUBLIC ../include)
# Support "algorithms.h" imports in private headers and source files
target_include_directories(img PRIVATE ../include/img)
