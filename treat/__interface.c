#include "treat.ih"

struct _TreatModule Treat = {
  .new = &Treat_new,
  .destroy = &Treat_destroy,
  .init = &Treat_init,
};
