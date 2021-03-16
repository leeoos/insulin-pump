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
rag.Qsto1 = $START.rag.Qsto1
*/
void System_eqFunction_1(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,1};
  data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */ = data->modelData->realVarsData[3].attribute /* rag.Qsto1 STATE(1) */.start;
  TRACE_POP
}

/*
equation index: 2
type: SIMPLE_ASSIGN
$PRE.gen.delta = $START.gen.delta
*/
void System_eqFunction_2(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,2};
  data->simulationInfo->realVarsPre[16] /* gen.delta DISCRETE */ = data->modelData->realVarsData[16].attribute /* gen.delta DISCRETE */.start;
  TRACE_POP
}

/*
equation index: 3
type: SIMPLE_ASSIGN
gen.delta = $PRE.gen.delta
*/
void System_eqFunction_3(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,3};
  data->localData[0]->realVars[16] /* gen.delta DISCRETE */ = data->simulationInfo->realVarsPre[16] /* gen.delta DISCRETE */;
  TRACE_POP
}
extern void System_eqFunction_72(DATA *data, threadData_t *threadData);


/*
equation index: 5
type: SIMPLE_ASSIGN
pu.insulin_out = 0.0
*/
void System_eqFunction_5(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,5};
  data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */ = 0.0;
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
  data->simulationInfo->realVarsPre[22] /* pu.insulin_out DISCRETE */ = data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */;
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
extern void System_eqFunction_60(DATA *data, threadData_t *threadData);


/*
equation index: 9
type: SIMPLE_ASSIGN
$DER.rag.Qsto2 = rag.K.kmax * rag.Qsto1 - k_empt(rag.K, rag.Qsto) * rag.Qsto2
*/
void System_eqFunction_9(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,9};
  data->localData[0]->realVars[9] /* der(rag.Qsto2) STATE_DER */ = (data->simulationInfo->realParameter[20] /* rag.K.kmax PARAM */) * (data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */) - ((omc_k__empt(threadData, omc_KPar(threadData, data->simulationInfo->realParameter[15] /* rag.K.Dose PARAM */, data->simulationInfo->realParameter[16] /* rag.K.b PARAM */, data->simulationInfo->realParameter[17] /* rag.K.d PARAM */, data->simulationInfo->realParameter[20] /* rag.K.kmax PARAM */, data->simulationInfo->realParameter[21] /* rag.K.kmin PARAM */, data->simulationInfo->realParameter[19] /* rag.K.kabs PARAM */, data->simulationInfo->realParameter[14] /* rag.K.BW PARAM */, data->simulationInfo->realParameter[18] /* rag.K.f PARAM */), data->localData[0]->realVars[14] /* rag.Qsto variable */)) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */));
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
  data->localData[0]->realVars[0] /* pa.Gp STATE(1) */ = DIVISION_SIM(data->simulationInfo->realParameter[5] /* pa.Gb PARAM */,data->simulationInfo->realParameter[7] /* pa.Vg PARAM */,"pa.Vg",equationIndexes);
  TRACE_POP
}
extern void System_eqFunction_53(DATA *data, threadData_t *threadData);

extern void System_eqFunction_56(DATA *data, threadData_t *threadData);


/*
equation index: 13
type: SIMPLE_ASSIGN
pa.I = pa.Ib
*/
void System_eqFunction_13(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,13};
  data->localData[0]->realVars[12] /* pa.I variable */ = data->simulationInfo->realParameter[6] /* pa.Ib PARAM */;
  TRACE_POP
}

/*
equation index: 14
type: SIMPLE_ASSIGN
pa.Ip = pa.I * pa.Vi - pu.insulin_out
*/
void System_eqFunction_14(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,14};
  data->localData[0]->realVars[1] /* pa.Ip STATE(1) */ = (data->localData[0]->realVars[12] /* pa.I variable */) * (data->simulationInfo->realParameter[8] /* pa.Vi PARAM */) - data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */;
  TRACE_POP
}
extern void System_eqFunction_58(DATA *data, threadData_t *threadData);


/*
equation index: 16
type: SIMPLE_ASSIGN
rag.Qgut = $START.rag.Qgut
*/
void System_eqFunction_16(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,16};
  data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */ = data->modelData->realVarsData[2].attribute /* rag.Qgut STATE(1) */.start;
  TRACE_POP
}

/*
equation index: 17
type: SIMPLE_ASSIGN
$DER.rag.Qgut = k_empt(rag.K, rag.Qsto) * rag.Qsto2 - rag.K.kabs * rag.Qgut
*/
void System_eqFunction_17(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,17};
  data->localData[0]->realVars[7] /* der(rag.Qgut) STATE_DER */ = (omc_k__empt(threadData, omc_KPar(threadData, data->simulationInfo->realParameter[15] /* rag.K.Dose PARAM */, data->simulationInfo->realParameter[16] /* rag.K.b PARAM */, data->simulationInfo->realParameter[17] /* rag.K.d PARAM */, data->simulationInfo->realParameter[20] /* rag.K.kmax PARAM */, data->simulationInfo->realParameter[21] /* rag.K.kmin PARAM */, data->simulationInfo->realParameter[19] /* rag.K.kabs PARAM */, data->simulationInfo->realParameter[14] /* rag.K.BW PARAM */, data->simulationInfo->realParameter[18] /* rag.K.f PARAM */), data->localData[0]->realVars[14] /* rag.Qsto variable */)) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */) - ((data->simulationInfo->realParameter[19] /* rag.K.kabs PARAM */) * (data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */));
  TRACE_POP
}
extern void System_eqFunction_64(DATA *data, threadData_t *threadData);

extern void System_eqFunction_65(DATA *data, threadData_t *threadData);


/*
equation index: 20
type: ALGORITHM

  $whenCondition5 := $START.$whenCondition5;
  $whenCondition5 := false;
*/
void System_eqFunction_20(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,20};
  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = data->modelData->booleanVarsData[4].attribute /* $whenCondition5 DISCRETE */.start;

  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 21
type: ALGORITHM

  $whenCondition6 := $START.$whenCondition6;
  $whenCondition6 := false;
*/
void System_eqFunction_21(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,21};
  data->localData[0]->booleanVars[5] /* $whenCondition6 DISCRETE */ = data->modelData->booleanVarsData[5].attribute /* $whenCondition6 DISCRETE */.start;

  data->localData[0]->booleanVars[5] /* $whenCondition6 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 22
type: ALGORITHM

  $whenCondition7 := $START.$whenCondition7;
  $whenCondition7 := false;
*/
void System_eqFunction_22(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,22};
  data->localData[0]->booleanVars[6] /* $whenCondition7 DISCRETE */ = data->modelData->booleanVarsData[6].attribute /* $whenCondition7 DISCRETE */.start;

  data->localData[0]->booleanVars[6] /* $whenCondition7 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 23
type: SIMPLE_ASSIGN
$whenCondition1 = false
*/
void System_eqFunction_23(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,23};
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 24
type: SIMPLE_ASSIGN
$whenCondition2 = false
*/
void System_eqFunction_24(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,24};
  data->localData[0]->booleanVars[1] /* $whenCondition2 DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 25
type: SIMPLE_ASSIGN
gen.meal_on = false
*/
void System_eqFunction_25(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,25};
  data->localData[0]->booleanVars[8] /* gen.meal_on DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 26
type: SIMPLE_ASSIGN
$PRE.gen.meal_on = gen.meal_on
*/
void System_eqFunction_26(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,26};
  data->simulationInfo->booleanVarsPre[8] /* gen.meal_on DISCRETE */ = data->localData[0]->booleanVars[8] /* gen.meal_on DISCRETE */;
  TRACE_POP
}

/*
equation index: 27
type: SIMPLE_ASSIGN
$whenCondition4 = gen.meal_on and not $PRE.gen.meal_on
*/
void System_eqFunction_27(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,27};
  data->localData[0]->booleanVars[3] /* $whenCondition4 DISCRETE */ = (data->localData[0]->booleanVars[8] /* gen.meal_on DISCRETE */ && (!data->simulationInfo->booleanVarsPre[8] /* gen.meal_on DISCRETE */));
  TRACE_POP
}

/*
equation index: 28
type: SIMPLE_ASSIGN
gen.meal_off = false
*/
void System_eqFunction_28(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,28};
  data->localData[0]->booleanVars[7] /* gen.meal_off DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 29
type: SIMPLE_ASSIGN
$PRE.gen.meal_off = gen.meal_off
*/
void System_eqFunction_29(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,29};
  data->simulationInfo->booleanVarsPre[7] /* gen.meal_off DISCRETE */ = data->localData[0]->booleanVars[7] /* gen.meal_off DISCRETE */;
  TRACE_POP
}

/*
equation index: 30
type: SIMPLE_ASSIGN
$whenCondition3 = gen.meal_off and not $PRE.gen.meal_off
*/
void System_eqFunction_30(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,30};
  data->localData[0]->booleanVars[2] /* $whenCondition3 DISCRETE */ = (data->localData[0]->booleanVars[7] /* gen.meal_off DISCRETE */ && (!data->simulationInfo->booleanVarsPre[7] /* gen.meal_off DISCRETE */));
  TRACE_POP
}

/*
equation index: 31
type: SIMPLE_ASSIGN
mo_av.min_g = 10000.0
*/
void System_eqFunction_31(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,31};
  data->localData[0]->realVars[19] /* mo_av.min_g DISCRETE */ = 10000.0;
  TRACE_POP
}

/*
equation index: 32
type: SIMPLE_ASSIGN
$PRE.mo_av.min_g = mo_av.min_g
*/
void System_eqFunction_32(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,32};
  data->simulationInfo->realVarsPre[19] /* mo_av.min_g DISCRETE */ = data->localData[0]->realVars[19] /* mo_av.min_g DISCRETE */;
  TRACE_POP
}

/*
equation index: 33
type: SIMPLE_ASSIGN
mo_av.max_g = 0.0
*/
void System_eqFunction_33(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,33};
  data->localData[0]->realVars[18] /* mo_av.max_g DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 34
type: SIMPLE_ASSIGN
$PRE.mo_av.max_g = mo_av.max_g
*/
void System_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  data->simulationInfo->realVarsPre[18] /* mo_av.max_g DISCRETE */ = data->localData[0]->realVars[18] /* mo_av.max_g DISCRETE */;
  TRACE_POP
}

/*
equation index: 35
type: SIMPLE_ASSIGN
mo_av.average = 0.0
*/
void System_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  data->localData[0]->realVars[17] /* mo_av.average DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 36
type: SIMPLE_ASSIGN
$PRE.mo_av.average = mo_av.average
*/
void System_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  data->simulationInfo->realVarsPre[17] /* mo_av.average DISCRETE */ = data->localData[0]->realVars[17] /* mo_av.average DISCRETE */;
  TRACE_POP
}

/*
equation index: 37
type: SIMPLE_ASSIGN
mo_av.num_values = 0.0
*/
void System_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 38
type: SIMPLE_ASSIGN
$PRE.mo_av.num_values = mo_av.num_values
*/
void System_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  data->simulationInfo->realVarsPre[20] /* mo_av.num_values DISCRETE */ = data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */;
  TRACE_POP
}

/*
equation index: 39
type: SIMPLE_ASSIGN
mo_av.sim_step = 0.0
*/
void System_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  data->localData[0]->realVars[21] /* mo_av.sim_step DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 40
type: SIMPLE_ASSIGN
$PRE.mo_av.sim_step = mo_av.sim_step
*/
void System_eqFunction_40(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,40};
  data->simulationInfo->realVarsPre[21] /* mo_av.sim_step DISCRETE */ = data->localData[0]->realVars[21] /* mo_av.sim_step DISCRETE */;
  TRACE_POP
}

/*
equation index: 41
type: SIMPLE_ASSIGN
mo_av.low_average = false
*/
void System_eqFunction_41(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,41};
  data->localData[0]->booleanVars[10] /* mo_av.low_average DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 42
type: SIMPLE_ASSIGN
$PRE.mo_av.low_average = mo_av.low_average
*/
void System_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  data->simulationInfo->booleanVarsPre[10] /* mo_av.low_average DISCRETE */ = data->localData[0]->booleanVars[10] /* mo_av.low_average DISCRETE */;
  TRACE_POP
}

/*
equation index: 43
type: SIMPLE_ASSIGN
mo_av.high_average = false
*/
void System_eqFunction_43(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,43};
  data->localData[0]->booleanVars[9] /* mo_av.high_average DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 44
type: SIMPLE_ASSIGN
$PRE.mo_av.high_average = mo_av.high_average
*/
void System_eqFunction_44(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,44};
  data->simulationInfo->booleanVarsPre[9] /* mo_av.high_average DISCRETE */ = data->localData[0]->booleanVars[9] /* mo_av.high_average DISCRETE */;
  TRACE_POP
}

/*
equation index: 45
type: SIMPLE_ASSIGN
pu_co.controller = false
*/
void System_eqFunction_45(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,45};
  data->localData[0]->booleanVars[11] /* pu_co.controller DISCRETE */ = 0;
  TRACE_POP
}

/*
equation index: 46
type: SIMPLE_ASSIGN
$PRE.pu_co.controller = pu_co.controller
*/
void System_eqFunction_46(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,46};
  data->simulationInfo->booleanVarsPre[11] /* pu_co.controller DISCRETE */ = data->localData[0]->booleanVars[11] /* pu_co.controller DISCRETE */;
  TRACE_POP
}

/*
equation index: 47
type: SIMPLE_ASSIGN
pu.z = 0.0
*/
void System_eqFunction_47(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,47};
  data->localData[0]->realVars[23] /* pu.z DISCRETE */ = 0.0;
  TRACE_POP
}

/*
equation index: 48
type: SIMPLE_ASSIGN
$PRE.pu.z = pu.z
*/
void System_eqFunction_48(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,48};
  data->simulationInfo->realVarsPre[23] /* pu.z DISCRETE */ = data->localData[0]->realVars[23] /* pu.z DISCRETE */;
  TRACE_POP
}
OMC_DISABLE_OPT
void System_functionInitialEquations_0(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  System_eqFunction_1(data, threadData);
  System_eqFunction_2(data, threadData);
  System_eqFunction_3(data, threadData);
  System_eqFunction_72(data, threadData);
  System_eqFunction_5(data, threadData);
  System_eqFunction_6(data, threadData);
  System_eqFunction_7(data, threadData);
  System_eqFunction_60(data, threadData);
  System_eqFunction_9(data, threadData);
  System_eqFunction_10(data, threadData);
  System_eqFunction_53(data, threadData);
  System_eqFunction_56(data, threadData);
  System_eqFunction_13(data, threadData);
  System_eqFunction_14(data, threadData);
  System_eqFunction_58(data, threadData);
  System_eqFunction_16(data, threadData);
  System_eqFunction_17(data, threadData);
  System_eqFunction_64(data, threadData);
  System_eqFunction_65(data, threadData);
  System_eqFunction_20(data, threadData);
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
  System_eqFunction_31(data, threadData);
  System_eqFunction_32(data, threadData);
  System_eqFunction_33(data, threadData);
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
  System_eqFunction_47(data, threadData);
  System_eqFunction_48(data, threadData);
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

  res = (data->simulationInfo->realParameter[6] /* pa.Ib PARAM */) * (data->simulationInfo->realParameter[8] /* pa.Vi PARAM */) - data->localData[0]->realVars[1] /* pa.Ip STATE(1) */;
  if(fabs(res) > 1e-5)
  {
    errorStreamPrint(LOG_INIT, 0, "The initialization problem is inconsistent due to the following equation: 0 != %g = pa.Ib * pa.Vi - pa.Ip", res);
    return 1;
  }
  res = data->simulationInfo->realParameter[5] /* pa.Gb PARAM */ - data->localData[0]->realVars[11] /* pa.G variable */;
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

