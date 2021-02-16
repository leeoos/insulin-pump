/* Non Linear Systems */
#include "System_model.h"
#include "System_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* inner equations */

/*
equation index: 9
type: ALGORITHM

  patient.glucose := $START.patient.glucose;
  patient.glucose := rag.ra_meal + pump.insulin_out;
*/
void System_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[3] /* patient.glucose variable */ = data->modelData->realVarsData[3].attribute /* patient.glucose variable */.start;

  data->localData[0]->realVars[3] /* patient.glucose variable */ = data->localData[0]->realVars[5] /* rag.ra_meal variable */ + data->localData[0]->realVars[4] /* pump.insulin_out variable */;
  TRACE_POP
}
/*
equation index: 11
type: ALGORITHM

  $TMP_pump.insulin_out_10 := $START.pump.insulin_out;
  $TMP_pump.insulin_out_10 := 10.0 + patient.glucose;
*/
void System_eqFunction_11(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,11};
  data->localData[0]->realVars[1] /* $TMP_pump.insulin_out_10 variable */ = data->modelData->realVarsData[4].attribute /* pump.insulin_out variable */.start;

  data->localData[0]->realVars[1] /* $TMP_pump.insulin_out_10 variable */ = 10.0 + data->localData[0]->realVars[3] /* patient.glucose variable */;
  TRACE_POP
}

void residualFunc12(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,12};
  int i;
  /* iteration variables */
  for (i=0; i<1; i++) {
    if (isinf(xloc[i]) || isnan(xloc[i])) {
      for (i=0; i<1; i++) {
        res[i] = NAN;
      }
      return;
    }
  }
  data->localData[0]->realVars[4] /* pump.insulin_out variable */ = xloc[0];
  /* backup outputs */
  /* pre body */
  /* local constraints */
  System_eqFunction_9(data, threadData);

  /* local constraints */
  System_eqFunction_11(data, threadData);
  /* body */
  res[0] = data->localData[0]->realVars[1] /* $TMP_pump.insulin_out_10 variable */ - data->localData[0]->realVars[4] /* pump.insulin_out variable */;
  /* restore known outputs */
  TRACE_POP
}
void initializeSparsePatternNLS12(NONLINEAR_SYSTEM_DATA* inSysData)
{
  /* no sparsity pattern available */
  inSysData->isPatternAvailable = 0;
}
void initializeStaticDataNLS12(void *inData, threadData_t *threadData, void *inSystemData)
{
  DATA* data = (DATA*) inData;
  NONLINEAR_SYSTEM_DATA* sysData = (NONLINEAR_SYSTEM_DATA*) inSystemData;
  int i=0;
  /* static nls data for pump.insulin_out */
  sysData->nominal[i] = data->modelData->realVarsData[4].attribute /* pump.insulin_out */.nominal;
  sysData->min[i]     = data->modelData->realVarsData[4].attribute /* pump.insulin_out */.min;
  sysData->max[i++]   = data->modelData->realVarsData[4].attribute /* pump.insulin_out */.max;
  /* initial sparse pattern */
  initializeSparsePatternNLS12(sysData);
}

void getIterationVarsNLS12(struct DATA *inData, double *array)
{
  DATA* data = (DATA*) inData;
  array[0] = data->localData[0]->realVars[4] /* pump.insulin_out variable */;
}


/* inner equations */

/*
equation index: 3
type: ALGORITHM

  pump.insulin_out := $START.pump.insulin_out;
  pump.insulin_out := 10.0 + patient.glucose;
*/
void System_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[4] /* pump.insulin_out variable */ = data->modelData->realVarsData[4].attribute /* pump.insulin_out variable */.start;

  data->localData[0]->realVars[4] /* pump.insulin_out variable */ = 10.0 + data->localData[0]->realVars[3] /* patient.glucose variable */;
  TRACE_POP
}
/*
equation index: 5
type: ALGORITHM

  $TMP_patient.glucose_4 := $START.patient.glucose;
  $TMP_patient.glucose_4 := rag.ra_meal + pump.insulin_out;
*/
void System_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[0] /* $TMP_patient.glucose_4 variable */ = data->modelData->realVarsData[3].attribute /* patient.glucose variable */.start;

  data->localData[0]->realVars[0] /* $TMP_patient.glucose_4 variable */ = data->localData[0]->realVars[5] /* rag.ra_meal variable */ + data->localData[0]->realVars[4] /* pump.insulin_out variable */;
  TRACE_POP
}

void residualFunc6(void** dataIn, const double* xloc, double* res, const int* iflag)
{
  TRACE_PUSH
  DATA *data = (DATA*) ((void**)dataIn[0]);
  threadData_t *threadData = (threadData_t*) ((void**)dataIn[1]);
  const int equationIndexes[2] = {1,6};
  int i;
  /* iteration variables */
  for (i=0; i<1; i++) {
    if (isinf(xloc[i]) || isnan(xloc[i])) {
      for (i=0; i<1; i++) {
        res[i] = NAN;
      }
      return;
    }
  }
  data->localData[0]->realVars[3] /* patient.glucose variable */ = xloc[0];
  /* backup outputs */
  /* pre body */
  /* local constraints */
  System_eqFunction_3(data, threadData);

  /* local constraints */
  System_eqFunction_5(data, threadData);
  /* body */
  res[0] = data->localData[0]->realVars[0] /* $TMP_patient.glucose_4 variable */ - data->localData[0]->realVars[3] /* patient.glucose variable */;
  /* restore known outputs */
  TRACE_POP
}
void initializeSparsePatternNLS6(NONLINEAR_SYSTEM_DATA* inSysData)
{
  /* no sparsity pattern available */
  inSysData->isPatternAvailable = 0;
}
void initializeStaticDataNLS6(void *inData, threadData_t *threadData, void *inSystemData)
{
  DATA* data = (DATA*) inData;
  NONLINEAR_SYSTEM_DATA* sysData = (NONLINEAR_SYSTEM_DATA*) inSystemData;
  int i=0;
  /* static nls data for patient.glucose */
  sysData->nominal[i] = data->modelData->realVarsData[3].attribute /* patient.glucose */.nominal;
  sysData->min[i]     = data->modelData->realVarsData[3].attribute /* patient.glucose */.min;
  sysData->max[i++]   = data->modelData->realVarsData[3].attribute /* patient.glucose */.max;
  /* initial sparse pattern */
  initializeSparsePatternNLS6(sysData);
}

void getIterationVarsNLS6(struct DATA *inData, double *array)
{
  DATA* data = (DATA*) inData;
  array[0] = data->localData[0]->realVars[3] /* patient.glucose variable */;
}

/* Prototypes for the strict sets (Dynamic Tearing) */

/* Global constraints for the casual sets */
/* function initialize non-linear systems */
void System_initialNonLinearSystem(int nNonLinearSystems, NONLINEAR_SYSTEM_DATA* nonLinearSystemData)
{
  
  nonLinearSystemData[1].equationIndex = 12;
  nonLinearSystemData[1].size = 1;
  nonLinearSystemData[1].homotopySupport = 0;
  nonLinearSystemData[1].mixedSystem = 0;
  nonLinearSystemData[1].residualFunc = residualFunc12;
  nonLinearSystemData[1].strictTearingFunctionCall = NULL;
  nonLinearSystemData[1].analyticalJacobianColumn = NULL;
  nonLinearSystemData[1].initialAnalyticalJacobian = NULL;
  nonLinearSystemData[1].jacobianIndex = -1;
  nonLinearSystemData[1].initializeStaticNLSData = initializeStaticDataNLS12;
  nonLinearSystemData[1].getIterationVars = getIterationVarsNLS12;
  nonLinearSystemData[1].checkConstraints = NULL;
  
  
  nonLinearSystemData[0].equationIndex = 6;
  nonLinearSystemData[0].size = 1;
  nonLinearSystemData[0].homotopySupport = 0;
  nonLinearSystemData[0].mixedSystem = 0;
  nonLinearSystemData[0].residualFunc = residualFunc6;
  nonLinearSystemData[0].strictTearingFunctionCall = NULL;
  nonLinearSystemData[0].analyticalJacobianColumn = NULL;
  nonLinearSystemData[0].initialAnalyticalJacobian = NULL;
  nonLinearSystemData[0].jacobianIndex = -1;
  nonLinearSystemData[0].initializeStaticNLSData = initializeStaticDataNLS6;
  nonLinearSystemData[0].getIterationVars = getIterationVarsNLS6;
  nonLinearSystemData[0].checkConstraints = NULL;
}

#if defined(__cplusplus)
}
#endif

