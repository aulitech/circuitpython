#include "shared-bindings/neutonml/Neuton.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "py/obj.h"
#include "py/objproperty.h"
#include "py/runtime.h"
#include "py/runtime0.h"
#include "shared-bindings/util.h"
#include "shared/runtime/context_manager_helpers.h"

STATIC mp_obj_t neutonml_neuton_make_new(const mp_obj_type_t *type,
    size_t n_args, size_t n_kw,
    const mp_obj_t *all_args) {
    enum { ARG_outputs };
    static const mp_arg_t allowed_args[] = {
        {MP_QSTR_outputs, MP_ARG_OBJ | MP_ARG_REQUIRED},
    };
    mp_arg_val_t args[MP_ARRAY_SIZE(allowed_args)];
    mp_arg_parse_all_kw_array(n_args, n_kw, all_args,
        MP_ARRAY_SIZE(allowed_args), allowed_args, args);
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(args[ARG_outputs].u_obj, &bufinfo, MP_BUFFER_READ);

    neutonml_neuton_obj_t *self = m_new_obj(neutonml_neuton_obj_t);
    self->base.type = &neutonml_neuton_type;

    float *f;
    f = bufinfo.buf;
    printf("Neuton: Constructing buffer from %c [%f %f %f %f %f %f %f %f]",
        (char)bufinfo.typecode, (double)f[0], (double)f[1], (double)f[2],
        (double)f[3], (double)f[4], (double)f[5], (double)f[6],
        (double)f[7]);

    shared_module_neutonml_neuton_construct(self, (float *)bufinfo.buf,
        bufinfo.len);
    return MP_OBJ_FROM_PTR(self);
}

STATIC mp_obj_t neutonml_neuton_deinit(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    shared_module_neutonml_neuton_deinit(self);
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_deinit_obj,
    neutonml_neuton_deinit);

STATIC mp_obj_t neutonml_neuton_obj___exit__(size_t n_args,
    const mp_obj_t *args) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(args[0]);
    shared_module_neutonml_neuton_deinit(self);
    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(neutonml_neuton___exit___obj, 4, 4,
    neutonml_neuton_obj___exit__);

STATIC mp_obj_t neutonml_neuton_obj_get_inputs_count(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_inputs_count(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_inputs_count_obj,
    neutonml_neuton_obj_get_inputs_count);
MP_PROPERTY_GETTER(neutonml_neuton_inputs_count_obj,
    (mp_obj_t)&neutonml_neuton_get_inputs_count_obj);

STATIC mp_obj_t neutonml_neuton_obj_set_inputs(mp_obj_t self_in,
    mp_obj_t inputs) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    size_t len;
    int status = 0;
    mp_obj_t *items;
    mp_obj_get_array(inputs, &len, &items);
    status =
        shared_module_neutonml_neuton_model_set_inputs(self, (input_t *)&items);
    return mp_obj_new_int((mp_int_t)status);
}
MP_DEFINE_CONST_FUN_OBJ_2(neutonml_neuton_set_inputs_obj,
    neutonml_neuton_obj_set_inputs);

STATIC mp_obj_t neutonml_neuton_obj_get_inputs_ptr(mp_obj_t self_in) {
    float *inputs;
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);

    inputs = shared_module_neutonml_neuton_model_get_inputs_ptr(self);
    return MP_OBJ_FROM_PTR(inputs);
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_inputs_ptr_obj,
    neutonml_neuton_obj_get_inputs_ptr);

STATIC mp_obj_t neutonml_neuton_obj_set_ready_flag(mp_obj_t self_in,
    mp_obj_t dummy) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    shared_module_neutonml_neuton_model_set_ready_flag(self);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_2(neutonml_neuton_set_ready_flag_obj,
    neutonml_neuton_obj_set_ready_flag);

STATIC mp_obj_t neutonml_neuton_obj_reset_inputs(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    shared_module_neutonml_neuton_model_reset_inputs(self);
    return mp_const_none;
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_reset_inputs_obj,
    neutonml_neuton_obj_reset_inputs);

STATIC mp_obj_t neutonml_neuton_obj_get_outputs_count(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_outputs_count(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_outputs_count_obj,
    neutonml_neuton_obj_get_outputs_count);
MP_PROPERTY_GETTER(neutonml_neuton_outputs_count_obj,
    (mp_obj_t)&neutonml_neuton_get_outputs_count_obj);

STATIC mp_obj_t neutonml_neuton_obj_run_inference(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    uint16_t result;

    result = shared_module_neutonml_neuton_model_run_inference(self);
    return mp_obj_new_int(result);
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_run_inference_obj,
    neutonml_neuton_obj_run_inference);

STATIC mp_obj_t neutonml_neuton_obj_get_task_type(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(shared_module_neutonml_neuton_model_task_type(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_task_type_obj,
    neutonml_neuton_obj_get_task_type);
MP_PROPERTY_GETTER(neutonml_neuton_task_type_obj,
    (mp_obj_t)&neutonml_neuton_get_task_type_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_quantization_level(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_quantization_level(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_quantization_level_obj,
    neutonml_neuton_obj_get_quantization_level);
MP_PROPERTY_GETTER(neutonml_neuton_quantization_level_obj,
    (mp_obj_t)&neutonml_neuton_get_quantization_level_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_float_calculations(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_float_calculations(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_float_calculations_obj,
    neutonml_neuton_obj_get_float_calculations);
MP_PROPERTY_GETTER(neutonml_neuton_float_calculations_obj,
    (mp_obj_t)&neutonml_neuton_get_float_calculations_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_neurons_count(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_neurons_count(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_neurons_count_obj,
    neutonml_neuton_obj_get_neurons_count);
MP_PROPERTY_GETTER(neutonml_neuton_neurons_count_obj,
    (mp_obj_t)&neutonml_neuton_get_neurons_count_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_weights_count(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_weights_count(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_weights_count_obj,
    neutonml_neuton_obj_get_weights_count);
MP_PROPERTY_GETTER(neutonml_neuton_weights_count_obj,
    (mp_obj_t)&neutonml_neuton_get_weights_count_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_inputs_limits_count(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_inputs_limits_count(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_inputs_limits_count_obj,
    neutonml_neuton_obj_get_inputs_limits_count);
MP_PROPERTY_GETTER(neutonml_neuton_inputs_limits_count_obj,
    (mp_obj_t)&neutonml_neuton_get_inputs_limits_count_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_window_size(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_window_size(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_window_size_obj,
    neutonml_neuton_obj_get_window_size);
MP_PROPERTY_GETTER(neutonml_neuton_window_size_obj,
    (mp_obj_t)&neutonml_neuton_get_window_size_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_ram_usage(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(shared_module_neutonml_neuton_model_ram_usage(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_ram_usage_obj,
    neutonml_neuton_obj_get_ram_usage);
MP_PROPERTY_GETTER(neutonml_neuton_ram_usage_obj,
    (mp_obj_t)&neutonml_neuton_get_ram_usage_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_size(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(shared_module_neutonml_neuton_model_size(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_size_obj,
    neutonml_neuton_obj_get_size);
MP_PROPERTY_GETTER(neutonml_neuton_size_obj,
    (mp_obj_t)&neutonml_neuton_get_size_obj);

STATIC mp_obj_t neutonml_neuton_obj_get_size_with_meta(mp_obj_t self_in) {
    neutonml_neuton_obj_t *self = MP_OBJ_TO_PTR(self_in);
    return mp_obj_new_int(
        shared_module_neutonml_neuton_model_size_with_meta(self));
}
MP_DEFINE_CONST_FUN_OBJ_1(neutonml_neuton_get_size_with_meta_obj,
    neutonml_neuton_obj_get_size_with_meta);
MP_PROPERTY_GETTER(neutonml_neuton_size_with_meta_obj,
    (mp_obj_t)&neutonml_neuton_get_size_with_meta_obj);

STATIC const mp_rom_map_elem_t neutonml_neuton_locals_dict_table[] = {
    // Methods
    {MP_ROM_QSTR(MP_QSTR_deinit), MP_ROM_PTR(&neutonml_neuton_deinit_obj)},
    {MP_ROM_QSTR(MP_QSTR___enter__), MP_ROM_PTR(&default___enter___obj)},
    {MP_ROM_QSTR(MP_QSTR___exit__), MP_ROM_PTR(&neutonml_neuton___exit___obj)},
    {MP_ROM_QSTR(MP_QSTR_get_inputs_count),
     MP_ROM_PTR(&neutonml_neuton_inputs_count_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_inputs),
     MP_ROM_PTR(&neutonml_neuton_set_inputs_obj)},
    {MP_ROM_QSTR(MP_QSTR_set_ready_flag),
     MP_ROM_PTR(&neutonml_neuton_set_ready_flag_obj)},
    {MP_ROM_QSTR(MP_QSTR_reset_inputs),
     MP_ROM_PTR(&neutonml_neuton_reset_inputs_obj)},
    {MP_ROM_QSTR(MP_QSTR_outputs_count),
     MP_ROM_PTR(&neutonml_neuton_outputs_count_obj)},
    {MP_ROM_QSTR(MP_QSTR_inference),
     MP_ROM_PTR(&neutonml_neuton_run_inference_obj)},
    {MP_ROM_QSTR(MP_QSTR_task_type),
     MP_ROM_PTR(&neutonml_neuton_task_type_obj)},
    {MP_ROM_QSTR(MP_QSTR_quantization_level),
     MP_ROM_PTR(&neutonml_neuton_quantization_level_obj)},
    {MP_ROM_QSTR(MP_QSTR_float_calculations),
     MP_ROM_PTR(&neutonml_neuton_float_calculations_obj)},
    {MP_ROM_QSTR(MP_QSTR_neurons_count),
     MP_ROM_PTR(&neutonml_neuton_neurons_count_obj)},
    {MP_ROM_QSTR(MP_QSTR_weights_count),
     MP_ROM_PTR(&neutonml_neuton_weights_count_obj)},
    {MP_ROM_QSTR(MP_QSTR_inputs_limits_count),
     MP_ROM_PTR(&neutonml_neuton_inputs_limits_count_obj)},
    {MP_ROM_QSTR(MP_QSTR_window_size),
     MP_ROM_PTR(&neutonml_neuton_window_size_obj)},
    {MP_ROM_QSTR(MP_QSTR_ram_usage),
     MP_ROM_PTR(&neutonml_neuton_ram_usage_obj)},
    {MP_ROM_QSTR(MP_QSTR_size), MP_ROM_PTR(&neutonml_neuton_size_obj)},
    {MP_ROM_QSTR(MP_QSTR_size_with_meta),
     MP_ROM_PTR(&neutonml_neuton_size_with_meta_obj)},
};

STATIC MP_DEFINE_CONST_DICT(neutonml_neuton_locals_dict,
    neutonml_neuton_locals_dict_table);

const mp_obj_type_t neutonml_neuton_type = {
    {&mp_type_type},
    .name = MP_QSTR_Neuton,
    .make_new = neutonml_neuton_make_new,
    .locals_dict = (mp_obj_dict_t *)&neutonml_neuton_locals_dict,
};
