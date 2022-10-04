#ifndef MICROPY_INCLUDED_NEUTONML_NEUTON_H
#define MICROPY_INCLUDED_NEUTONML_NEUTON_H

#include "lib/neuton/neuton/neuton.h"
#include "py/obj.h"

typedef struct {
    mp_obj_base_t base;
    bool deinited;
    uint8_t state;
    uint16_t length;
    float *outputs;
} neutonml_neuton_obj_t;

#endif  // MICROPY_INCLUDED_NEUTONML_NEUTON_H
