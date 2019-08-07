/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Dan Halbert for Adafruit Industries
 * Copyright (c) 2018 Artur Pacholec
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef MICROPY_INCLUDED_SHARED_BINDINGS_BLEIO_CHARACTERISTIC_H
#define MICROPY_INCLUDED_SHARED_BINDINGS_BLEIO_CHARACTERISTIC_H

#include "shared-bindings/bleio/Attribute.h"
#include "shared-module/bleio/Characteristic.h"
#include "common-hal/bleio/Characteristic.h"

extern const mp_obj_type_t bleio_characteristic_type;

extern void common_hal_bleio_characteristic_construct(bleio_characteristic_obj_t *self, bleio_uuid_obj_t *uuid, bleio_characteristic_properties_t props, bleio_attribute_security_mode_t read_perm, bleio_attribute_security_mode_t write_perm, mp_obj_list_t *descriptor_list);
extern mp_obj_t common_hal_bleio_characteristic_get_value(bleio_characteristic_obj_t *self);
extern void common_hal_bleio_characteristic_set_value(bleio_characteristic_obj_t *self, mp_buffer_info_t *bufinfo);
extern bleio_characteristic_properties_t common_hal_bleio_characteristic_get_properties(bleio_characteristic_obj_t *self);
extern bleio_uuid_obj_t *common_hal_bleio_characteristic_get_uuid(bleio_characteristic_obj_t *self);
extern mp_obj_list_t *common_hal_bleio_characteristic_get_descriptor_list(bleio_characteristic_obj_t *self);
extern bleio_service_obj_t *common_hal_bleio_characteristic_get_service(bleio_characteristic_obj_t *self);
extern void common_hal_bleio_characteristic_set_cccd(bleio_characteristic_obj_t *self, bool notify, bool indicate);

#endif // MICROPY_INCLUDED_SHARED_BINDINGS_BLEIO_CHARACTERISTIC_H
