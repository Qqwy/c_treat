#include "char.ih"

struct _TreatTypesCharModule Char = {
    .type.size = sizeof(TChar),
    .type.ctor = &Char_ctor,
    .type.dtor = &Char_dtor,

    .new = &Char_new,
    .destroy = &Char_destroy,
};
