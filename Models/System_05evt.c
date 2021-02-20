/* Events: Sample, Zero Crossings, Relations, Discrete Changes */
#include "System_model.h"
#if defined(__cplusplus)
extern "C" {
#endif

/* Initializes the raw time events of the simulation using the now
   calcualted parameters. */
void System_function_initSample(DATA *data, threadData_t *threadData)
{
  long i=0;
  /* sample 1 */
  data->modelData->samplesInfo[i].index = 1;
  data->modelData->samplesInfo[i].start = 0.0;
  data->modelData->samplesInfo[i].interval = data->simulationInfo->realParameter[7] /* pu.T PARAM */;
  assertStreamPrint(threadData,data->modelData->samplesInfo[i].interval > 0.0, "sample-interval <= 0.0");
  i++;
  /* sample 2 */
  data->modelData->samplesInfo[i].index = 2;
  data->modelData->samplesInfo[i].start = 0.0;
  data->modelData->samplesInfo[i].interval = DIVISION(data->simulationInfo->realParameter[1] /* gen.Meal_period PARAM */,2.0,"2.0");
  assertStreamPrint(threadData,data->modelData->samplesInfo[i].interval > 0.0, "sample-interval <= 0.0");
  i++;
  /* sample 3 */
  data->modelData->samplesInfo[i].index = 3;
  data->modelData->samplesInfo[i].start = data->simulationInfo->realParameter[0] /* gen.Meal_length PARAM */;
  data->modelData->samplesInfo[i].interval = DIVISION(data->simulationInfo->realParameter[1] /* gen.Meal_period PARAM */,2.0,"2.0");
  assertStreamPrint(threadData,data->modelData->samplesInfo[i].interval > 0.0, "sample-interval <= 0.0");
  i++;
}

const char *System_zeroCrossingDescription(int i, int **out_EquationIndexes)
{
  static const char *res[] = {"pa.G >= 250.0 or pa.G <= 75.0"};
  static const int occurEqs0[] = {1,38};
  static const int *occurEqs[] = {occurEqs0};
  *out_EquationIndexes = (int*) occurEqs[i];
  return res[i];
}

/* forwarded equations */
extern void System_eqFunction_34(DATA* data, threadData_t *threadData);
extern void System_eqFunction_35(DATA* data, threadData_t *threadData);
extern void System_eqFunction_36(DATA* data, threadData_t *threadData);
extern void System_eqFunction_37(DATA* data, threadData_t *threadData);
extern void System_eqFunction_38(DATA* data, threadData_t *threadData);
extern void System_eqFunction_39(DATA* data, threadData_t *threadData);
extern void System_eqFunction_40(DATA* data, threadData_t *threadData);
extern void System_eqFunction_41(DATA* data, threadData_t *threadData);
extern void System_eqFunction_42(DATA* data, threadData_t *threadData);
extern void System_eqFunction_43(DATA* data, threadData_t *threadData);
extern void System_eqFunction_44(DATA* data, threadData_t *threadData);
extern void System_eqFunction_45(DATA* data, threadData_t *threadData);
extern void System_eqFunction_46(DATA* data, threadData_t *threadData);
extern void System_eqFunction_48(DATA* data, threadData_t *threadData);
extern void System_eqFunction_50(DATA* data, threadData_t *threadData);
extern void System_eqFunction_53(DATA* data, threadData_t *threadData);

int System_function_ZeroCrossingsEquations(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  data->simulationInfo->callStatistics.functionZeroCrossingsEquations++;

  System_eqFunction_34(data, threadData);

  System_eqFunction_35(data, threadData);

  System_eqFunction_36(data, threadData);

  System_eqFunction_37(data, threadData);

  System_eqFunction_38(data, threadData);

  System_eqFunction_39(data, threadData);

  System_eqFunction_40(data, threadData);

  System_eqFunction_41(data, threadData);

  System_eqFunction_42(data, threadData);

  System_eqFunction_43(data, threadData);

  System_eqFunction_44(data, threadData);

  System_eqFunction_45(data, threadData);

  System_eqFunction_46(data, threadData);

  System_eqFunction_48(data, threadData);

  System_eqFunction_50(data, threadData);

  System_eqFunction_53(data, threadData);
  
  TRACE_POP
  return 0;
}

int System_function_ZeroCrossings(DATA *data, threadData_t *threadData, double *gout)
{
  TRACE_PUSH
  modelica_boolean tmp0;
  modelica_boolean tmp1;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_ZC);
#endif
  data->simulationInfo->callStatistics.functionZeroCrossings++;

  tmp0 = GreaterEqZC(data->localData[0]->realVars[11] /* pa.G variable */, 250.0, data->simulationInfo->storedRelations[0]);
  tmp1 = LessEqZC(data->localData[0]->realVars[11] /* pa.G variable */, 75.0, data->simulationInfo->storedRelations[1]);
  gout[0] = ((tmp0 || tmp1)) ? 1 : -1;

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_ZC);
#endif

  TRACE_POP
  return 0;
}

const char *System_relationDescription(int i)
{
  const char *res[] = {"pa.G >= 250.0",
  "pa.G <= 75.0"};
  return res[i];
}

int System_function_updateRelations(DATA *data, threadData_t *threadData, int evalforZeroCross)
{
  TRACE_PUSH
  modelica_boolean tmp2;
  modelica_boolean tmp3;
  
  if(evalforZeroCross) {
    tmp2 = GreaterEqZC(data->localData[0]->realVars[11] /* pa.G variable */, 250.0, data->simulationInfo->storedRelations[0]);
    data->simulationInfo->relations[0] = tmp2;
    tmp3 = LessEqZC(data->localData[0]->realVars[11] /* pa.G variable */, 75.0, data->simulationInfo->storedRelations[1]);
    data->simulationInfo->relations[1] = tmp3;
  } else {
    data->simulationInfo->relations[0] = (data->localData[0]->realVars[11] /* pa.G variable */ >= 250.0);
    data->simulationInfo->relations[1] = (data->localData[0]->realVars[11] /* pa.G variable */ <= 75.0);
  }
  
  TRACE_POP
  return 0;
}

#if defined(__cplusplus)
}
#endif

