/* Initialization */
#include "System_model.h"
#include "System_11mix.h"
#include "System_12jac.h"
#if defined(__cplusplus)
extern "C" {
#endif

void System_functionInitialEquations_0(DATA *data, threadData_t *threadData);

/*
equation index: 1
type: ALGORITHM

  generator.delta := $START.generator.delta;
  generator.delta := 20.0;
*/
void System_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[2] /* generator.delta variable */ = data->modelData->realVarsData[2].attribute /* generator.delta variable */.start;

  data->localData[0]->realVars[2] /* generator.delta variable */ = 20.0;
  TRACE_POP
}

/*
equation index: 2
type: ALGORITHM

  rag.ra_meal := $START.rag.ra_meal;
  rag.ra_meal := 10.0 + generator.delta;
*/
void System_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[5] /* rag.ra_meal variable */ = data->modelData->realVarsData[5].attribute /* rag.ra_meal variable */.start;

  data->localData[0]->realVars[5] /* rag.ra_meal variable */ = 10.0 + data->localData[0]->realVars[2] /* generator.delta variable */;
  TRACE_POP
}

void System_eqFunction_3(DATA*, threadData_t*);
void System_eqFunction_5(DATA*, threadData_t*);
void System_eqFunction_4(DATA*, threadData_t*);
/*
equation index: 6
indexNonlinear: 0
type: NONLINEAR

vars: {patient.glucose}
eqns: {3, 5, 4}
*/
void System_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  int retValue;
  if(ACTIVE_STREAM(LOG_DT))
  {
    infoStreamPrint(LOG_DT, 1, "Solving nonlinear system 6 (STRICT TEARING SET if tearing enabled) at time = %18.10e", data->localData[0]->timeValue);
    messageClose(LOG_DT);
  }
  /* get old value */
  data->simulationInfo->nonlinearSystemData[0].nlsxOld[0] = data->localData[0]->realVars[3] /* patient.glucose variable */;
  retValue = solve_nonlinear_system(data, threadData, 0);
  /* check if solution process was successful */
  if (retValue > 0){
    const int indexes[2] = {1,6};
    throwStreamPrintWithEquationIndexes(threadData, indexes, "Solving non-linear system 6 failed at time=%.15g.\nFor more information please use -lv LOG_NLS.", data->localData[0]->timeValue);
  }
  /* write solution */
  data->localData[0]->realVars[3] /* patient.glucose variable */ = data->simulationInfo->nonlinearSystemData[0].nlsx[0];
  TRACE_POP
}
OMC_DISABLE_OPT
void System_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  System_eqFunction_1(data, threadData);
  System_eqFunction_2(data, threadData);
  System_eqFunction_6(data, threadData);
  TRACE_POP
}

int System_functionInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->discreteCall = 1;
  System_functionInitialEquations_0(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
  TRACE_POP
  return 0;
}

/* No System_functionInitialEquations_lambda0 function */

int System_functionRemovedInitialEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int *equationIndexes = NULL;
  double res = 0.0;

  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

