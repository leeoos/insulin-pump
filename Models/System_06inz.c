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
type: SIMPLE_ASSIGN
$PRE.gen.delta = $START.gen.delta
*/
void System_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->simulationInfo->realVarsPre[16] /* gen.delta DISCRETE */ = data->modelData->realVarsData[16].attribute /* gen.delta DISCRETE */.start;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
gen.delta = $PRE.gen.delta
*/
void System_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->localData[0]->realVars[16] /* gen.delta DISCRETE */ = data->simulationInfo->realVarsPre[16] /* gen.delta DISCRETE */;
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
rag.Qsto1 = $START.rag.Qsto1
*/
void System_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */ = data->modelData->realVarsData[3].attribute /* rag.Qsto1 STATE(1) */.start;
  TRACE_POP
}
extern void System_eqFunction_53(DATA *data, threadData_t *threadData);


/*
equation index: 5
type: SIMPLE_ASSIGN
pu.insulin_out = 0.0
*/
void System_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 6
type: SIMPLE_ASSIGN
$PRE.pu.insulin_out = pu.insulin_out
*/
void System_eqFunction_6(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,6};
  data->simulationInfo->realVarsPre[17] /* pu.insulin_out DISCRETE */ = data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */;
  TRACE_POP
}

/*
equation index: 7
type: SIMPLE_ASSIGN
rag.Qsto2 = $START.rag.Qsto2
*/
void System_eqFunction_7(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,7};
  data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */ = data->modelData->realVarsData[4].attribute /* rag.Qsto2 STATE(1) */.start;
  TRACE_POP
}
extern void System_eqFunction_41(DATA *data, threadData_t *threadData);


/*
equation index: 9
type: SIMPLE_ASSIGN
$DER.rag.Qsto2 = rag.K.kmax * rag.Qsto1 - k_empt(rag.K, rag.Qsto) * rag.Qsto2
*/
void System_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[9] /* der(rag.Qsto2) STATE_DER */ = (data->simulationInfo->realParameter[17] /* rag.K.kmax PARAM */) * (data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */) - ((omc_k__empt(threadData, omc_KPar(threadData, data->simulationInfo->realParameter[12] /* rag.K.Dose PARAM */, data->simulationInfo->realParameter[13] /* rag.K.b PARAM */, data->simulationInfo->realParameter[14] /* rag.K.d PARAM */, data->simulationInfo->realParameter[17] /* rag.K.kmax PARAM */, data->simulationInfo->realParameter[18] /* rag.K.kmin PARAM */, data->simulationInfo->realParameter[16] /* rag.K.kabs PARAM */, data->simulationInfo->realParameter[11] /* rag.K.BW PARAM */, data->simulationInfo->realParameter[15] /* rag.K.f PARAM */), data->localData[0]->realVars[14] /* rag.Qsto variable */)) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */));
  TRACE_POP
}

/*
equation index: 10
type: SIMPLE_ASSIGN
pa.Gp = pa.Gb / pa.Vg
*/
void System_eqFunction_10(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,10};
  data->localData[0]->realVars[0] /* pa.Gp STATE(1) */ = DIVISION_SIM(data->simulationInfo->realParameter[3] /* pa.Gb PARAM */,data->simulationInfo->realParameter[5] /* pa.Vg PARAM */,"pa.Vg",equationIndexes);
  TRACE_POP
}
extern void System_eqFunction_36(DATA *data, threadData_t *threadData);


/*
equation index: 12
type: ALGORITHM

  $whenCondition5 := $START.$whenCondition5;
  pu.fail := $START.pu.fail;
  if pa.G >= 250.0 or pa.G <= 75.0 then
    pu.fail := true;
  end if;
  $whenCondition5 := false;
*/
void System_eqFunction_12(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,12};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = data->modelData->booleanVarsData[4].attribute /* $whenCondition5 DISCRETE */.start;

  data->localData[0]->booleanVars[7] /* pu.fail DISCRETE */ = data->modelData->booleanVarsData[7].attribute /* pu.fail DISCRETE */.start;

  tmp0 = GreaterEq(data->localData[0]->realVars[11] /* pa.G variable */,250.0);
  tmp1 = LessEq(data->localData[0]->realVars[11] /* pa.G variable */,75.0);
  if((tmp0 || tmp1))
  {
    data->localData[0]->booleanVars[7] /* pu.fail DISCRETE */ = 1;
  }

  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = 0;
  TRACE_POP
}
extern void System_eqFunction_37(DATA *data, threadData_t *threadData);


/*
equation index: 14
type: SIMPLE_ASSIGN
pa.I = pa.Ib
*/
void System_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->localData[0]->realVars[12] /* pa.I variable */ = data->simulationInfo->realParameter[4] /* pa.Ib PARAM */;
  TRACE_POP
}

/*
equation index: 15
type: SIMPLE_ASSIGN
pa.Ip = pa.I * pa.Vi - pu.insulin_out
*/
void System_eqFunction_15(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,15};
  data->localData[0]->realVars[1] /* pa.Ip STATE(1) */ = (data->localData[0]->realVars[12] /* pa.I variable */) * (data->simulationInfo->realParameter[6] /* pa.Vi PARAM */) - data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */;
  TRACE_POP
}
extern void System_eqFunction_39(DATA *data, threadData_t *threadData);


/*
equation index: 17
type: SIMPLE_ASSIGN
rag.Qgut = $START.rag.Qgut
*/
void System_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */ = data->modelData->realVarsData[2].attribute /* rag.Qgut STATE(1) */.start;
  TRACE_POP
}

/*
equation index: 18
type: SIMPLE_ASSIGN
$DER.rag.Qgut = k_empt(rag.K, rag.Qsto) * rag.Qsto2 - rag.K.kabs * rag.Qgut
*/
void System_eqFunction_18(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,18};
  data->localData[0]->realVars[7] /* der(rag.Qgut) STATE_DER */ = (omc_k__empt(threadData, omc_KPar(threadData, data->simulationInfo->realParameter[12] /* rag.K.Dose PARAM */, data->simulationInfo->realParameter[13] /* rag.K.b PARAM */, data->simulationInfo->realParameter[14] /* rag.K.d PARAM */, data->simulationInfo->realParameter[17] /* rag.K.kmax PARAM */, data->simulationInfo->realParameter[18] /* rag.K.kmin PARAM */, data->simulationInfo->realParameter[16] /* rag.K.kabs PARAM */, data->simulationInfo->realParameter[11] /* rag.K.BW PARAM */, data->simulationInfo->realParameter[15] /* rag.K.f PARAM */), data->localData[0]->realVars[14] /* rag.Qsto variable */)) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */) - ((data->simulationInfo->realParameter[16] /* rag.K.kabs PARAM */) * (data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */));
  TRACE_POP
}
extern void System_eqFunction_45(DATA *data, threadData_t *threadData);

extern void System_eqFunction_46(DATA *data, threadData_t *threadData);


/*
equation index: 21
type: SIMPLE_ASSIGN
$whenCondition1 = false
*/
void System_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 22
type: SIMPLE_ASSIGN
$whenCondition2 = false
*/
void System_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  data->localData[0]->booleanVars[1] /* $whenCondition2 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 23
type: SIMPLE_ASSIGN
gen.meal_on = false
*/
void System_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->localData[0]->booleanVars[6] /* gen.meal_on DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 24
type: SIMPLE_ASSIGN
$PRE.gen.meal_on = gen.meal_on
*/
void System_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->simulationInfo->booleanVarsPre[6] /* gen.meal_on DISCRETE */ = data->localData[0]->booleanVars[6] /* gen.meal_on DISCRETE */;
  TRACE_POP
}

/*
equation index: 25
type: SIMPLE_ASSIGN
$whenCondition4 = gen.meal_on and not $PRE.gen.meal_on
*/
void System_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->localData[0]->booleanVars[3] /* $whenCondition4 DISCRETE */ = (data->localData[0]->booleanVars[6] /* gen.meal_on DISCRETE */ && (!data->simulationInfo->booleanVarsPre[6] /* gen.meal_on DISCRETE */));
  TRACE_POP
}

/*
equation index: 26
type: SIMPLE_ASSIGN
gen.meal_off = false
*/
void System_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->localData[0]->booleanVars[5] /* gen.meal_off DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 27
type: SIMPLE_ASSIGN
$PRE.gen.meal_off = gen.meal_off
*/
void System_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->simulationInfo->booleanVarsPre[5] /* gen.meal_off DISCRETE */ = data->localData[0]->booleanVars[5] /* gen.meal_off DISCRETE */;
  TRACE_POP
}

/*
equation index: 28
type: SIMPLE_ASSIGN
$whenCondition3 = gen.meal_off and not $PRE.gen.meal_off
*/
void System_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  data->localData[0]->booleanVars[2] /* $whenCondition3 DISCRETE */ = (data->localData[0]->booleanVars[5] /* gen.meal_off DISCRETE */ && (!data->simulationInfo->booleanVarsPre[5] /* gen.meal_off DISCRETE */));
  TRACE_POP
}

/*
equation index: 29
type: SIMPLE_ASSIGN
pu.z = 0.0
*/
void System_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  data->localData[0]->realVars[18] /* pu.z DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 30
type: SIMPLE_ASSIGN
$PRE.pu.z = pu.z
*/
void System_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  data->simulationInfo->realVarsPre[18] /* pu.z DISCRETE */ = data->localData[0]->realVars[18] /* pu.z DISCRETE */;
  TRACE_POP
}
OMC_DISABLE_OPT
void System_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  System_eqFunction_1(data, threadData);
  System_eqFunction_2(data, threadData);
  System_eqFunction_3(data, threadData);
  System_eqFunction_53(data, threadData);
  System_eqFunction_5(data, threadData);
  System_eqFunction_6(data, threadData);
  System_eqFunction_7(data, threadData);
  System_eqFunction_41(data, threadData);
  System_eqFunction_9(data, threadData);
  System_eqFunction_10(data, threadData);
  System_eqFunction_36(data, threadData);
  System_eqFunction_12(data, threadData);
  System_eqFunction_37(data, threadData);
  System_eqFunction_14(data, threadData);
  System_eqFunction_15(data, threadData);
  System_eqFunction_39(data, threadData);
  System_eqFunction_17(data, threadData);
  System_eqFunction_18(data, threadData);
  System_eqFunction_45(data, threadData);
  System_eqFunction_46(data, threadData);
  System_eqFunction_21(data, threadData);
  System_eqFunction_22(data, threadData);
  System_eqFunction_23(data, threadData);
  System_eqFunction_24(data, threadData);
  System_eqFunction_25(data, threadData);
  System_eqFunction_26(data, threadData);
  System_eqFunction_27(data, threadData);
  System_eqFunction_28(data, threadData);
  System_eqFunction_29(data, threadData);
  System_eqFunction_30(data, threadData);
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

  res = (!((!data->localData[0]->booleanVars[7] /* pu.fail DISCRETE */ && !0) || (data->localData[0]->booleanVars[7] /* pu.fail DISCRETE */ && 0)));
  if(fabs(res) > 1e-5)
  {
    errorStreamPrint(LOG_INIT, 0, "The initialization problem is inconsistent due to the following equation: 0 != %g = not pu.fail == false", res);
    return 1;
  }
  res = (data->simulationInfo->realParameter[4] /* pa.Ib PARAM */) * (data->simulationInfo->realParameter[6] /* pa.Vi PARAM */) - data->localData[0]->realVars[1] /* pa.Ip STATE(1) */;
  if(fabs(res) > 1e-5)
  {
    errorStreamPrint(LOG_INIT, 0, "The initialization problem is inconsistent due to the following equation: 0 != %g = pa.Ib * pa.Vi - pa.Ip", res);
    return 1;
  }
  res = data->simulationInfo->realParameter[3] /* pa.Gb PARAM */ - data->localData[0]->realVars[11] /* pa.G variable */;
  if(fabs(res) > 1e-5)
  {
    errorStreamPrint(LOG_INIT, 0, "The initialization problem is inconsistent due to the following equation: 0 != %g = pa.Gb - pa.G", res);
    return 1;
  }
  
  TRACE_POP
  return 0;
}


#if defined(__cplusplus)
}
#endif

