#ifndef TREAT_H_
#define TREAT_H_


struct _TreatModule {
  void *(*new)(const void * type, ...);
  void (*destroy)(void *obj);
  void (*init)();
};
struct _TreatModule Treat;

#endif //TREAT_H_
