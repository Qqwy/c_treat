#include "string.ih"

struct _TreatTypesStringModule String = {
    .type.size = sizeof(TString),
    .type.ctor = &String_ctor,
    .type.dtor = &String_dtor,

    .new = &String_new,
    .destroy = &String_destroy,
};
