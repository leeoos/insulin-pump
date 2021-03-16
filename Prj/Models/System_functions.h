#ifndef System__H
#define System__H
#include "meta/meta_modelica.h"
#include "util/modelica.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "simulation/simulation_runtime.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  modelica_real _Dose;
  modelica_real _b;
  modelica_real _d;
  modelica_real _kmax;
  modelica_real _kmin;
  modelica_real _kabs;
  modelica_real _BW;
  modelica_real _f;
} KPar;
extern struct record_description KPar__desc;

void KPar_construct_p(threadData_t *threadData, void* v_ths );
#define KPar_construct(td, ths ) KPar_construct_p(td, &ths )
void KPar_copy_p(void* v_src, void* v_dst);
#define KPar_copy(src,dst) KPar_copy_p(&src, &dst)

// This function should eventualy replace the default 'modelica' record constructor funcition
// that omc used to generate, i.e., replace functionBodyRecordConstructor template.
// KPar omc_KPar(threadData_t *threadData , modelica_real in_Dose, modelica_real in_b, modelica_real in_d, modelica_real in_kmax, modelica_real in_kmin, modelica_real in_kabs, modelica_real in_BW, modelica_real in_f);

// This function is not needed anymore. If you want to know how a record
// is 'assigned to' in simulation context see assignRhsExpToRecordCrefSimContext and
// splitRecordAssignmentToMemberAssignments (simCode). Basically the record is
// split up assignments generated for each memeber individualy.
// void KPar_copy_to_vars_p(void* v_src , modelica_real* in_Dose, modelica_real* in_b, modelica_real* in_d, modelica_real* in_kmax, modelica_real* in_kmin, modelica_real* in_kabs, modelica_real* in_BW, modelica_real* in_f);
// #define KPar_copy_to_vars(src,...) KPar_copy_to_vars_p(&src, __VA_ARGS__)

typedef base_array_t KPar_array;
#define alloc_KPar_array(dst,ndims,...) generic_array_create(NULL, dst, KPar_construct_p, ndims, sizeof(KPar), __VA_ARGS__)
#define KPar_array_copy_data(src,dst)   generic_array_copy_data(src, &dst, KPar_copy_p, sizeof(KPar))
#define KPar_array_alloc_copy(src,dst)  generic_array_alloc_copy(src, &dst, KPar_copy_p, sizeof(KPar))
#define KPar_array_get(src,ndims,...)   (*(KPar*)(generic_array_get(&src, sizeof(KPar), __VA_ARGS__)))
#define KPar_set(dst,val,...)           generic_array_set(&dst, &val, KPar_copy_p, sizeof(KPar), __VA_ARGS__)

DLLExport
KPar omc_KPar (threadData_t *threadData, modelica_real omc_Dose, modelica_real omc_b, modelica_real omc_d, modelica_real omc_kmax, modelica_real omc_kmin, modelica_real omc_kabs, modelica_real omc_BW, modelica_real omc_f);

DLLExport
modelica_metatype boxptr_KPar(threadData_t *threadData, modelica_metatype _Dose, modelica_metatype _b, modelica_metatype _d, modelica_metatype _kmax, modelica_metatype _kmin, modelica_metatype _kabs, modelica_metatype _BW, modelica_metatype _f);
static const MMC_DEFSTRUCTLIT(boxvar_lit_KPar,2,0) {(void*) boxptr_KPar,0}};
#define boxvar_KPar MMC_REFSTRUCTLIT(boxvar_lit_KPar)


DLLExport
modelica_real omc_k__empt(threadData_t *threadData, KPar _K, modelica_real _Q);
DLLExport
modelica_metatype boxptr_k__empt(threadData_t *threadData, modelica_metatype _K, modelica_metatype _Q);
static const MMC_DEFSTRUCTLIT(boxvar_lit_k__empt,2,0) {(void*) boxptr_k__empt,0}};
#define boxvar_k__empt MMC_REFSTRUCTLIT(boxvar_lit_k__empt)
#include "System_model.h"


#ifdef __cplusplus
}
#endif
#endif

