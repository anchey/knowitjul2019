#!/bin/sh

(printf '#include <stddef.h>\n\nunsigned int const coordinates[][2] = {\n' && cat coords.csv | grep -v '^#' | sed -e 's/\(.*\)/\t{\1},/g' && printf '};\nsize_t const coordinates_l = sizeof(coordinates) / sizeof(*coordinates);\n') > coordinates.c
