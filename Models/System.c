/* Main Simulation File */

#if defined(__cplusplus)
extern "C" {
#endif

#include "System_model.h"
#include "simulation/solver/events.h"

#define prefixedName_performSimulation System_performSimulation
#define prefixedName_updateContinuousSystem System_updateContinuousSystem
#include <simulation/solver/perform_simulation.c.inc>

#define prefixedName_performQSSSimulation System_performQSSSimulation
#include <simulation/solver/perform_qss_simulation.c.inc>


/* dummy VARINFO and FILEINFO */
const FILE_INFO dummyFILE_INFO = omc_dummyFileInfo;
const VAR_INFO dummyVAR_INFO = omc_dummyVarInfo;

int System_input_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_input_function_init(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_input_function_updateStartValues(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_inputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_data_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  TRACE_POP
  return 0;
}

int System_dataReconciliationInputNames(DATA *data, char ** names){
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_output_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}

int System_setc_function(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
}


/*
equation index: 34
type: SIMPLE_ASSIGN
$whenCondition2 = sample(3, gen.Meal_length, 0.5 * gen.Meal_period)
*/
void System_eqFunction_34(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,34};
  data->localData[0]->booleanVars[1] /* $whenCondition2 DISCRETE */ = data->simulationInfo->samples[2];
  TRACE_POP
}
/*
equation index: 35
type: SIMPLE_ASSIGN
$whenCondition1 = sample(2, 0.0, 0.5 * gen.Meal_period)
*/
void System_eqFunction_35(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,35};
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = data->simulationInfo->samples[1];
  TRACE_POP
}
/*
equation index: 36
type: SIMPLE_ASSIGN
pa.G = pa.Gp / pa.Vg
*/
void System_eqFunction_36(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,36};
  data->localData[0]->realVars[11] /* pa.G variable */ = DIVISION_SIM(data->localData[0]->realVars[0] /* pa.Gp STATE(1) */,data->simulationInfo->realParameter[5] /* pa.Vg PARAM */,"pa.Vg",equationIndexes);
  TRACE_POP
}
/*
equation index: 37
type: SIMPLE_ASSIGN
pu.err = pa.G - pu.ref
*/
void System_eqFunction_37(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,37};
  data->localData[0]->realVars[13] /* pu.err variable */ = data->localData[0]->realVars[11] /* pa.G variable */ - data->simulationInfo->realParameter[10] /* pu.ref PARAM */;
  TRACE_POP
}
/*
equation index: 38
type: ALGORITHM

  pu.insulin_out := pre(pu.insulin_out);
  pu.z := pre(pu.z);
  $whenCondition5 := pre($whenCondition5);
  pu.fail := pre(pu.fail);
  if pa.G >= 250.0 or pa.G <= 75.0 then
    pu.fail := true;
  end if;
  $whenCondition5 := sample(1, 0.0, pu.T);
  when $whenCondition5 then
    pu.z := pre(pu.z) + pu.T * pu.err;
    pu.insulin_out := max(0.0, pu.a * pu.err + pu.b * pre(pu.z));
  end when;
*/
void System_eqFunction_38(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,38};
  modelica_boolean tmp11;
  modelica_boolean tmp12;
  data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */ = data->simulationInfo->realVarsPre[17] /* pu.insulin_out DISCRETE */;

  data->localData[0]->realVars[18] /* pu.z DISCRETE */ = data->simulationInfo->realVarsPre[18] /* pu.z DISCRETE */;

  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = data->simulationInfo->booleanVarsPre[4] /* $whenCondition5 DISCRETE */;

  data->localData[0]->booleanVars[7] /* pu.fail DISCRETE */ = data->simulationInfo->booleanVarsPre[7] /* pu.fail DISCRETE */;

  RELATIONHYSTERESIS(tmp11, data->localData[0]->realVars[11] /* pa.G variable */, 250.0, 0, GreaterEq);
  RELATIONHYSTERESIS(tmp12, data->localData[0]->realVars[11] /* pa.G variable */, 75.0, 1, LessEq);
  if((tmp11 || tmp12))
  {
    data->localData[0]->booleanVars[7] /* pu.fail DISCRETE */ = 1;
  }

  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = data->simulationInfo->samples[0];

  if(data->simulationInfo->discreteCall == 1)
  {
    if((data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ && !data->simulationInfo->booleanVarsPre[4] /* $whenCondition5 DISCRETE */ /* edge */))
    {
      data->localData[0]->realVars[18] /* pu.z DISCRETE */ = data->simulationInfo->realVarsPre[18] /* pu.z DISCRETE */ + (data->simulationInfo->realParameter[7] /* pu.T PARAM */) * (data->localData[0]->realVars[13] /* pu.err variable */);

      data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */ = fmax(0.0,(data->simulationInfo->realParameter[8] /* pu.a PARAM */) * (data->localData[0]->realVars[13] /* pu.err variable */) + (data->simulationInfo->realParameter[9] /* pu.b PARAM */) * (data->simulationInfo->realVarsPre[18] /* pu.z DISCRETE */));
    }
  }
  TRACE_POP
}
/*
equation index: 39
type: SIMPLE_ASSIGN
$DER.pa.Ip = pu.insulin_out + (-0.1) * pa.Ip + 0.3 * pa.Gp
*/
void System_eqFunction_39(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,39};
  data->localData[0]->realVars[6] /* der(pa.Ip) STATE_DER */ = data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */ + (-0.1) * (data->localData[0]->realVars[1] /* pa.Ip STATE(1) */) + (0.3) * (data->localData[0]->realVars[0] /* pa.Gp STATE(1) */);
  TRACE_POP
}
/*
equation index: 40
type: SIMPLE_ASSIGN
pa.I = (pa.Ip + pu.insulin_out) / pa.Vi
*/
void System_eqFunction_40(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,40};
  data->localData[0]->realVars[12] /* pa.I variable */ = DIVISION_SIM(data->localData[0]->realVars[1] /* pa.Ip STATE(1) */ + data->localData[0]->realVars[17] /* pu.insulin_out DISCRETE */,data->simulationInfo->realParameter[6] /* pa.Vi PARAM */,"pa.Vi",equationIndexes);
  TRACE_POP
}
/*
equation index: 41
type: SIMPLE_ASSIGN
rag.Qsto = rag.Qsto1 + rag.Qsto2
*/
void System_eqFunction_41(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,41};
  data->localData[0]->realVars[14] /* rag.Qsto variable */ = data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */ + data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */;
  TRACE_POP
}
/*
equation index: 42
type: SIMPLE_ASSIGN
$cse1 = k_empt(rag.K, rag.Qsto)
*/
void System_eqFunction_42(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,42};
  data->localData[0]->realVars[10] /* $cse1 variable */ = omc_k__empt(threadData, omc_KPar(threadData, data->simulationInfo->realParameter[12] /* rag.K.Dose PARAM */, data->simulationInfo->realParameter[13] /* rag.K.b PARAM */, data->simulationInfo->realParameter[14] /* rag.K.d PARAM */, data->simulationInfo->realParameter[17] /* rag.K.kmax PARAM */, data->simulationInfo->realParameter[18] /* rag.K.kmin PARAM */, data->simulationInfo->realParameter[16] /* rag.K.kabs PARAM */, data->simulationInfo->realParameter[11] /* rag.K.BW PARAM */, data->simulationInfo->realParameter[15] /* rag.K.f PARAM */), data->localData[0]->realVars[14] /* rag.Qsto variable */);
  TRACE_POP
}
/*
equation index: 43
type: SIMPLE_ASSIGN
$DER.rag.Qsto2 = rag.K.kmax * rag.Qsto1 - $cse1 * rag.Qsto2
*/
void System_eqFunction_43(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,43};
  data->localData[0]->realVars[9] /* der(rag.Qsto2) STATE_DER */ = (data->simulationInfo->realParameter[17] /* rag.K.kmax PARAM */) * (data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */) - ((data->localData[0]->realVars[10] /* $cse1 variable */) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */));
  TRACE_POP
}
/*
equation index: 44
type: SIMPLE_ASSIGN
$DER.rag.Qgut = $cse1 * rag.Qsto2 - rag.K.kabs * rag.Qgut
*/
void System_eqFunction_44(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,44};
  data->localData[0]->realVars[7] /* der(rag.Qgut) STATE_DER */ = (data->localData[0]->realVars[10] /* $cse1 variable */) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */) - ((data->simulationInfo->realParameter[16] /* rag.K.kabs PARAM */) * (data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */));
  TRACE_POP
}
/*
equation index: 45
type: SIMPLE_ASSIGN
rag.Rameal = rag.K.f * rag.K.kabs * rag.Qgut / rag.K.BW
*/
void System_eqFunction_45(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,45};
  data->localData[0]->realVars[15] /* rag.Rameal variable */ = (data->simulationInfo->realParameter[15] /* rag.K.f PARAM */) * ((data->simulationInfo->realParameter[16] /* rag.K.kabs PARAM */) * (DIVISION_SIM(data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */,data->simulationInfo->realParameter[11] /* rag.K.BW PARAM */,"rag.K.BW",equationIndexes)));
  TRACE_POP
}
/*
equation index: 46
type: SIMPLE_ASSIGN
$DER.pa.Gp = 20.0 * rag.Rameal + (-0.1) * pa.Gp + (-1e-05) * pa.I * pa.Gp
*/
void System_eqFunction_46(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,46};
  data->localData[0]->realVars[5] /* der(pa.Gp) STATE_DER */ = (20.0) * (data->localData[0]->realVars[15] /* rag.Rameal variable */) + (-0.1) * (data->localData[0]->realVars[0] /* pa.Gp STATE(1) */) + (-1e-05) * ((data->localData[0]->realVars[12] /* pa.I variable */) * (data->localData[0]->realVars[0] /* pa.Gp STATE(1) */));
  TRACE_POP
}
/*
equation index: 47
type: WHEN

when {$whenCondition2} then
  gen.meal_off = not pre(gen.meal_off);
end when;
*/
void System_eqFunction_47(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,47};
  if((data->localData[0]->booleanVars[1] /* $whenCondition2 DISCRETE */ && !data->simulationInfo->booleanVarsPre[1] /* $whenCondition2 DISCRETE */ /* edge */))
  {
    data->localData[0]->booleanVars[5] /* gen.meal_off DISCRETE */ = (!data->simulationInfo->booleanVarsPre[5] /* gen.meal_off DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 48
type: SIMPLE_ASSIGN
$whenCondition3 = gen.meal_off and not pre(gen.meal_off)
*/
void System_eqFunction_48(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,48};
  data->localData[0]->booleanVars[2] /* $whenCondition3 DISCRETE */ = (data->localData[0]->booleanVars[5] /* gen.meal_off DISCRETE */ && (!data->simulationInfo->booleanVarsPre[5] /* gen.meal_off DISCRETE */));
  TRACE_POP
}
/*
equation index: 49
type: WHEN

when {$whenCondition1} then
  gen.meal_on = not pre(gen.meal_on);
end when;
*/
void System_eqFunction_49(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,49};
  if((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && !data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */ /* edge */))
  {
    data->localData[0]->booleanVars[6] /* gen.meal_on DISCRETE */ = (!data->simulationInfo->booleanVarsPre[6] /* gen.meal_on DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 50
type: SIMPLE_ASSIGN
$whenCondition4 = gen.meal_on and not pre(gen.meal_on)
*/
void System_eqFunction_50(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,50};
  data->localData[0]->booleanVars[3] /* $whenCondition4 DISCRETE */ = (data->localData[0]->booleanVars[6] /* gen.meal_on DISCRETE */ && (!data->simulationInfo->booleanVarsPre[6] /* gen.meal_on DISCRETE */));
  TRACE_POP
}
/*
equation index: 51
type: WHEN

when {$whenCondition4} then
  gen.delta = gen.gamma;
end when;
*/
void System_eqFunction_51(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,51};
  if((data->localData[0]->booleanVars[3] /* $whenCondition4 DISCRETE */ && !data->simulationInfo->booleanVarsPre[3] /* $whenCondition4 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[16] /* gen.delta DISCRETE */ = data->simulationInfo->realParameter[2] /* gen.gamma PARAM */;
  }
  else if((data->localData[0]->booleanVars[2] /* $whenCondition3 DISCRETE */ && !data->simulationInfo->booleanVarsPre[2] /* $whenCondition3 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[16] /* gen.delta DISCRETE */ = 0.0;
  }
  TRACE_POP
}
/*
equation index: 53
type: SIMPLE_ASSIGN
$DER.rag.Qsto1 = rag.K.Dose * gen.delta - rag.K.kmax * rag.Qsto1
*/
void System_eqFunction_53(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,53};
  data->localData[0]->realVars[8] /* der(rag.Qsto1) STATE_DER */ = (data->simulationInfo->realParameter[12] /* rag.K.Dose PARAM */) * (data->localData[0]->realVars[16] /* gen.delta DISCRETE */) - ((data->simulationInfo->realParameter[17] /* rag.K.kmax PARAM */) * (data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */));
  TRACE_POP
}

OMC_DISABLE_OPT
int System_functionDAE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  int equationIndexes[1] = {0};
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_DAE);
#endif

  data->simulationInfo->needToIterate = 0;
  data->simulationInfo->discreteCall = 1;
  System_functionLocalKnownVars(data, threadData);
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

  System_eqFunction_49(data, threadData);

  System_eqFunction_50(data, threadData);

  System_eqFunction_51(data, threadData);

  System_eqFunction_53(data, threadData);
  data->simulationInfo->discreteCall = 0;
  
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_DAE);
#endif
  TRACE_POP
  return 0;
}


int System_functionLocalKnownVars(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH

  
  TRACE_POP
  return 0;
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

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
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
}

int System_functionODE(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_tick(SIM_TIMER_FUNCTION_ODE);
#endif

  
  data->simulationInfo->callStatistics.functionODE++;
  
  System_functionLocalKnownVars(data, threadData);
  functionODE_system0(data, threadData);

#if !defined(OMC_MINIMAL_RUNTIME)
  if (measure_time_flag) rt_accumulate(SIM_TIMER_FUNCTION_ODE);
#endif

  TRACE_POP
  return 0;
}

/* forward the main in the simulation runtime */
extern int _main_SimulationRuntime(int argc, char**argv, DATA *data, threadData_t *threadData);

#include "System_12jac.h"
#include "System_13opt.h"

struct OpenModelicaGeneratedFunctionCallbacks System_callback = {
   (int (*)(DATA *, threadData_t *, void *)) System_performSimulation,    /* performSimulation */
   (int (*)(DATA *, threadData_t *, void *)) System_performQSSSimulation,    /* performQSSSimulation */
   System_updateContinuousSystem,    /* updateContinuousSystem */
   System_callExternalObjectDestructors,    /* callExternalObjectDestructors */
   NULL,    /* initialNonLinearSystem */
   NULL,    /* initialLinearSystem */
   NULL,    /* initialMixedSystem */
   #if !defined(OMC_NO_STATESELECTION)
   System_initializeStateSets,
   #else
   NULL,
   #endif    /* initializeStateSets */
   System_initializeDAEmodeData,
   System_functionODE,
   System_functionAlgebraics,
   System_functionDAE,
   System_functionLocalKnownVars,
   System_input_function,
   System_input_function_init,
   System_input_function_updateStartValues,
   System_data_function,
   System_output_function,
   System_setc_function,
   System_function_storeDelayed,
   System_updateBoundVariableAttributes,
   System_functionInitialEquations,
   1, /* useHomotopy - 0: local homotopy (equidistant lambda), 1: global homotopy (equidistant lambda), 2: new global homotopy approach (adaptive lambda), 3: new local homotopy approach (adaptive lambda)*/
   NULL,
   System_functionRemovedInitialEquations,
   System_updateBoundParameters,
   System_checkForAsserts,
   System_function_ZeroCrossingsEquations,
   System_function_ZeroCrossings,
   System_function_updateRelations,
   System_zeroCrossingDescription,
   System_relationDescription,
   System_function_initSample,
   System_INDEX_JAC_A,
   System_INDEX_JAC_B,
   System_INDEX_JAC_C,
   System_INDEX_JAC_D,
   System_INDEX_JAC_F,
   System_initialAnalyticJacobianA,
   System_initialAnalyticJacobianB,
   System_initialAnalyticJacobianC,
   System_initialAnalyticJacobianD,
   System_initialAnalyticJacobianF,
   System_functionJacA_column,
   System_functionJacB_column,
   System_functionJacC_column,
   System_functionJacD_column,
   System_functionJacF_column,
   System_linear_model_frame,
   System_linear_model_datarecovery_frame,
   System_mayer,
   System_lagrange,
   System_pickUpBoundsForInputsInOptimization,
   System_setInputData,
   System_getTimeGrid,
   System_symbolicInlineSystem,
   System_function_initSynchronous,
   System_function_updateSynchronous,
   System_function_equationsSynchronous,
   System_inputNames,
   System_dataReconciliationInputNames,
   NULL,
   NULL,
   NULL,
   -1

};

#define _OMC_LIT_RESOURCE_0_name_data "InputReal"
#define _OMC_LIT_RESOURCE_0_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,9,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,29,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "KPar"
#define _OMC_LIT_RESOURCE_1_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,4,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,29,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "MealGenerator"
#define _OMC_LIT_RESOURCE_2_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,13,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,29,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "OutputReal"
#define _OMC_LIT_RESOURCE_3_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,10,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,29,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "Patient"
#define _OMC_LIT_RESOURCE_4_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,7,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,29,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "Pump"
#define _OMC_LIT_RESOURCE_5_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,4,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,29,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "Rate_Appearance_Glucose"
#define _OMC_LIT_RESOURCE_6_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,23,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,29,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "System"
#define _OMC_LIT_RESOURCE_7_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,6,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,29,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "k_empt"
#define _OMC_LIT_RESOURCE_8_dir_data "/home/leo/Modelica/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,6,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,29,_OMC_LIT_RESOURCE_8_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,18,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir)}};
void System_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &System_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "System";
  data->modelData->modelFilePrefix = "System";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/home/leo/Modelica/Prj/Models";
  data->modelData->modelGUID = "{3733cebc-1c51-4e22-8608-307d2a1c196a}";
  #if defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME)
  data->modelData->initXMLData = NULL;
  data->modelData->modelDataXml.infoXMLData = NULL;
  #else
  #if defined(_MSC_VER) /* handle joke compilers */
  {
  /* for MSVC we encode a string like char x[] = {'a', 'b', 'c', '\0'} */
  /* because the string constant limit is 65535 bytes */
  static const char contents_init[] =
    #include "System_init.c"
    ;
  static const char contents_info[] =
    #include "System_info.c"
    ;
    data->modelData->initXMLData = contents_init;
    data->modelData->modelDataXml.infoXMLData = contents_info;
  }
  #else /* handle real compilers */
  data->modelData->initXMLData =
  #include "System_init.c"
    ;
  data->modelData->modelDataXml.infoXMLData =
  #include "System_info.c"
    ;
  #endif /* defined(_MSC_VER) */
  #endif /* defined(OPENMODELICA_XML_FROM_FILE_AT_RUNTIME) */
  data->modelData->runTestsuite = 0;
  
  data->modelData->nStates = 5;
  data->modelData->nVariablesReal = 19;
  data->modelData->nDiscreteReal = 3;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 8;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 19;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  
  data->modelData->nAliasReal = 4;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 1;
  data->modelData->nSamples = 3;
  data->modelData->nRelations = 2;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  
  data->modelData->modelDataXml.fileName = "System_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 2;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 54;
  data->modelData->nMixedSystems = 0;
  data->modelData->nLinearSystems = 0;
  data->modelData->nNonLinearSystems = 0;
  data->modelData->nStateSets = 0;
  data->modelData->nJacobians = 5;
  data->modelData->nOptimizeConstraints = 0;
  data->modelData->nOptimizeFinalConstraints = 0;
  
  data->modelData->nDelayExpressions = 0;
  
  data->modelData->nClocks = 0;
  data->modelData->nSubClocks = 0;
  
  data->modelData->nSensitivityVars = 0;
  data->modelData->nSensitivityParamVars = 0;
  data->modelData->nSetcVars = 0;
  data->modelData->ndataReconVars = 0;
  data->modelData->linearizationDumpLanguage =
  OMC_LINEARIZE_DUMP_LANGUAGE_MODELICA;
}

static int rml_execution_failed()
{
  fflush(NULL);
  fprintf(stderr, "Execution failed!\n");
  fflush(NULL);
  return 1;
}

#if defined(threadData)
#undef threadData
#endif
/* call the simulation runtime main from our main! */
int main(int argc, char**argv)
{
  int res;
  DATA data;
  MODEL_DATA modelData;
  SIMULATION_INFO simInfo;
  data.modelData = &modelData;
  data.simulationInfo = &simInfo;
  measure_time_flag = 0;
  compiledInDAEMode = 0;
  compiledWithSymSolver = 0;
  MMC_INIT(0);
  omc_alloc_interface.init();
  {
    MMC_TRY_TOP()
  
    MMC_TRY_STACK()
  
    System_setupDataStruc(&data, threadData);
    res = _main_SimulationRuntime(argc, argv, &data, threadData);
    
    MMC_ELSE()
    rml_execution_failed();
    fprintf(stderr, "Stack overflow detected and was not caught.\nSend us a bug report at https://trac.openmodelica.org/OpenModelica/newticket\n    Include the following trace:\n");
    printStacktraceMessages();
    fflush(NULL);
    return 1;
    MMC_CATCH_STACK()
    
    MMC_CATCH_TOP(return rml_execution_failed());
  }

  fflush(NULL);
  EXIT(res);
  return res;
}

#ifdef __cplusplus
}
#endif


