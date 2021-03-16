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
equation index: 51
type: SIMPLE_ASSIGN
$whenCondition2 = sample(5, gen.Meal_length, 0.5 * gen.Meal_period)
*/
void System_eqFunction_51(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,51};
  data->localData[0]->booleanVars[1] /* $whenCondition2 DISCRETE */ = data->simulationInfo->samples[4];
  TRACE_POP
}
/*
equation index: 52
type: SIMPLE_ASSIGN
$whenCondition1 = sample(4, 0.0, 0.5 * gen.Meal_period)
*/
void System_eqFunction_52(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,52};
  data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ = data->simulationInfo->samples[3];
  TRACE_POP
}
/*
equation index: 53
type: SIMPLE_ASSIGN
pa.G = pa.Gp / pa.Vg
*/
void System_eqFunction_53(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,53};
  data->localData[0]->realVars[11] /* pa.G variable */ = DIVISION_SIM(data->localData[0]->realVars[0] /* pa.Gp STATE(1) */,data->simulationInfo->realParameter[7] /* pa.Vg PARAM */,"pa.Vg",equationIndexes);
  TRACE_POP
}
/*
equation index: 54
type: ALGORITHM

  mo_av.high_average := pre(mo_av.high_average);
  mo_av.low_average := pre(mo_av.low_average);
  mo_av.sim_step := pre(mo_av.sim_step);
  mo_av.num_values := pre(mo_av.num_values);
  mo_av.average := pre(mo_av.average);
  mo_av.max_g := pre(mo_av.max_g);
  mo_av.min_g := pre(mo_av.min_g);
  $whenCondition5 := pre($whenCondition5);
  $whenCondition5 := sample(3, 100.0, mo_av.T);
  when $whenCondition5 then
    if pa.G < mo_av.min_g then
      mo_av.min_g := pa.G;
    end if;
    if pa.G > mo_av.max_g then
      mo_av.max_g := pa.G;
    end if;
    mo_av.average := (pre(mo_av.average) * mo_av.num_values + pa.G) / (1.0 + mo_av.num_values);
    mo_av.num_values := mo_av.num_values + 1.0;
    mo_av.sim_step := mo_av.sim_step + mo_av.T;
    if mo_av.sim_step == mo_av.stop_simulation then
      if mo_av.average < 80.0 then
        mo_av.low_average := true;
      end if;
      if mo_av.average > 120.0 then
        mo_av.high_average := true;
      end if;
    end if;
  end when;
*/
void System_eqFunction_54(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,54};
  modelica_boolean tmp0;
  modelica_boolean tmp1;
  modelica_boolean tmp3;
  modelica_boolean tmp4;
  data->localData[0]->booleanVars[9] /* mo_av.high_average DISCRETE */ = data->simulationInfo->booleanVarsPre[9] /* mo_av.high_average DISCRETE */;

  data->localData[0]->booleanVars[10] /* mo_av.low_average DISCRETE */ = data->simulationInfo->booleanVarsPre[10] /* mo_av.low_average DISCRETE */;

  data->localData[0]->realVars[21] /* mo_av.sim_step DISCRETE */ = data->simulationInfo->realVarsPre[21] /* mo_av.sim_step DISCRETE */;

  data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */ = data->simulationInfo->realVarsPre[20] /* mo_av.num_values DISCRETE */;

  data->localData[0]->realVars[17] /* mo_av.average DISCRETE */ = data->simulationInfo->realVarsPre[17] /* mo_av.average DISCRETE */;

  data->localData[0]->realVars[18] /* mo_av.max_g DISCRETE */ = data->simulationInfo->realVarsPre[18] /* mo_av.max_g DISCRETE */;

  data->localData[0]->realVars[19] /* mo_av.min_g DISCRETE */ = data->simulationInfo->realVarsPre[19] /* mo_av.min_g DISCRETE */;

  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = data->simulationInfo->booleanVarsPre[4] /* $whenCondition5 DISCRETE */;

  data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ = data->simulationInfo->samples[2];

  if(data->simulationInfo->discreteCall == 1)
  {
    if((data->localData[0]->booleanVars[4] /* $whenCondition5 DISCRETE */ && !data->simulationInfo->booleanVarsPre[4] /* $whenCondition5 DISCRETE */ /* edge */))
    {
      tmp0 = Less(data->localData[0]->realVars[11] /* pa.G variable */,data->localData[0]->realVars[19] /* mo_av.min_g DISCRETE */);
      if(tmp0)
      {
        data->localData[0]->realVars[19] /* mo_av.min_g DISCRETE */ = data->localData[0]->realVars[11] /* pa.G variable */;
      }

      tmp1 = Greater(data->localData[0]->realVars[11] /* pa.G variable */,data->localData[0]->realVars[18] /* mo_av.max_g DISCRETE */);
      if(tmp1)
      {
        data->localData[0]->realVars[18] /* mo_av.max_g DISCRETE */ = data->localData[0]->realVars[11] /* pa.G variable */;
      }

      data->localData[0]->realVars[17] /* mo_av.average DISCRETE */ = DIVISION_SIM((data->simulationInfo->realVarsPre[17] /* mo_av.average DISCRETE */) * (data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */) + data->localData[0]->realVars[11] /* pa.G variable */,1.0 + data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */,"1.0 + mo_av.num_values",equationIndexes);

      data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */ = data->localData[0]->realVars[20] /* mo_av.num_values DISCRETE */ + 1.0;

      data->localData[0]->realVars[21] /* mo_av.sim_step DISCRETE */ = data->localData[0]->realVars[21] /* mo_av.sim_step DISCRETE */ + data->simulationInfo->realParameter[3] /* mo_av.T PARAM */;

      if((data->localData[0]->realVars[21] /* mo_av.sim_step DISCRETE */ == data->simulationInfo->realParameter[4] /* mo_av.stop_simulation PARAM */))
      {
        tmp3 = Less(data->localData[0]->realVars[17] /* mo_av.average DISCRETE */,80.0);
        if(tmp3)
        {
          data->localData[0]->booleanVars[10] /* mo_av.low_average DISCRETE */ = 1;
        }

        tmp4 = Greater(data->localData[0]->realVars[17] /* mo_av.average DISCRETE */,120.0);
        if(tmp4)
        {
          data->localData[0]->booleanVars[9] /* mo_av.high_average DISCRETE */ = 1;
        }
      }
    }
  }
  TRACE_POP
}
/*
equation index: 55
type: ALGORITHM

  pu_co.controller := pre(pu_co.controller);
  $whenCondition6 := pre($whenCondition6);
  $whenCondition6 := sample(2, 100.0, pu_co.T);
  when $whenCondition6 then
    if pa.G >= 150.0 or pa.G <= 40.0 then
      pu_co.controller := true;
    end if;
  end when;
*/
void System_eqFunction_55(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,55};
  modelica_boolean tmp5;
  modelica_boolean tmp6;
  data->localData[0]->booleanVars[11] /* pu_co.controller DISCRETE */ = data->simulationInfo->booleanVarsPre[11] /* pu_co.controller DISCRETE */;

  data->localData[0]->booleanVars[5] /* $whenCondition6 DISCRETE */ = data->simulationInfo->booleanVarsPre[5] /* $whenCondition6 DISCRETE */;

  data->localData[0]->booleanVars[5] /* $whenCondition6 DISCRETE */ = data->simulationInfo->samples[1];

  if(data->simulationInfo->discreteCall == 1)
  {
    if((data->localData[0]->booleanVars[5] /* $whenCondition6 DISCRETE */ && !data->simulationInfo->booleanVarsPre[5] /* $whenCondition6 DISCRETE */ /* edge */))
    {
      tmp5 = GreaterEq(data->localData[0]->realVars[11] /* pa.G variable */,150.0);
      tmp6 = LessEq(data->localData[0]->realVars[11] /* pa.G variable */,40.0);
      if((tmp5 || tmp6))
      {
        data->localData[0]->booleanVars[11] /* pu_co.controller DISCRETE */ = 1;
      }
    }
  }
  TRACE_POP
}
/*
equation index: 56
type: SIMPLE_ASSIGN
pu.err = pa.G - pu.ref
*/
void System_eqFunction_56(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,56};
  data->localData[0]->realVars[13] /* pu.err variable */ = data->localData[0]->realVars[11] /* pa.G variable */ - data->simulationInfo->realParameter[12] /* pu.ref PARAM */;
  TRACE_POP
}
/*
equation index: 57
type: ALGORITHM

  pu.insulin_out := pre(pu.insulin_out);
  pu.z := pre(pu.z);
  $whenCondition7 := pre($whenCondition7);
  $whenCondition7 := sample(1, 0.0, pu.T);
  when $whenCondition7 then
    pu.z := pre(pu.z) + pu.T * pu.err;
    pu.insulin_out := max(0.0, pu.a * pu.err + pu.b * pre(pu.z));
  end when;
*/
void System_eqFunction_57(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,57};
  data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */ = data->simulationInfo->realVarsPre[22] /* pu.insulin_out DISCRETE */;

  data->localData[0]->realVars[23] /* pu.z DISCRETE */ = data->simulationInfo->realVarsPre[23] /* pu.z DISCRETE */;

  data->localData[0]->booleanVars[6] /* $whenCondition7 DISCRETE */ = data->simulationInfo->booleanVarsPre[6] /* $whenCondition7 DISCRETE */;

  data->localData[0]->booleanVars[6] /* $whenCondition7 DISCRETE */ = data->simulationInfo->samples[0];

  if(data->simulationInfo->discreteCall == 1)
  {
    if((data->localData[0]->booleanVars[6] /* $whenCondition7 DISCRETE */ && !data->simulationInfo->booleanVarsPre[6] /* $whenCondition7 DISCRETE */ /* edge */))
    {
      data->localData[0]->realVars[23] /* pu.z DISCRETE */ = data->simulationInfo->realVarsPre[23] /* pu.z DISCRETE */ + (data->simulationInfo->realParameter[9] /* pu.T PARAM */) * (data->localData[0]->realVars[13] /* pu.err variable */);

      data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */ = fmax(0.0,(data->simulationInfo->realParameter[10] /* pu.a PARAM */) * (data->localData[0]->realVars[13] /* pu.err variable */) + (data->simulationInfo->realParameter[11] /* pu.b PARAM */) * (data->simulationInfo->realVarsPre[23] /* pu.z DISCRETE */));
    }
  }
  TRACE_POP
}
/*
equation index: 58
type: SIMPLE_ASSIGN
$DER.pa.Ip = pu.insulin_out + (-0.1) * pa.Ip + 0.3 * pa.Gp
*/
void System_eqFunction_58(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,58};
  data->localData[0]->realVars[6] /* der(pa.Ip) STATE_DER */ = data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */ + (-0.1) * (data->localData[0]->realVars[1] /* pa.Ip STATE(1) */) + (0.3) * (data->localData[0]->realVars[0] /* pa.Gp STATE(1) */);
  TRACE_POP
}
/*
equation index: 59
type: SIMPLE_ASSIGN
pa.I = (pa.Ip + pu.insulin_out) / pa.Vi
*/
void System_eqFunction_59(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,59};
  data->localData[0]->realVars[12] /* pa.I variable */ = DIVISION_SIM(data->localData[0]->realVars[1] /* pa.Ip STATE(1) */ + data->localData[0]->realVars[22] /* pu.insulin_out DISCRETE */,data->simulationInfo->realParameter[8] /* pa.Vi PARAM */,"pa.Vi",equationIndexes);
  TRACE_POP
}
/*
equation index: 60
type: SIMPLE_ASSIGN
rag.Qsto = rag.Qsto1 + rag.Qsto2
*/
void System_eqFunction_60(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,60};
  data->localData[0]->realVars[14] /* rag.Qsto variable */ = data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */ + data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */;
  TRACE_POP
}
/*
equation index: 61
type: SIMPLE_ASSIGN
$cse1 = k_empt(rag.K, rag.Qsto)
*/
void System_eqFunction_61(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,61};
  data->localData[0]->realVars[10] /* $cse1 variable */ = omc_k__empt(threadData, omc_KPar(threadData, data->simulationInfo->realParameter[15] /* rag.K.Dose PARAM */, data->simulationInfo->realParameter[16] /* rag.K.b PARAM */, data->simulationInfo->realParameter[17] /* rag.K.d PARAM */, data->simulationInfo->realParameter[20] /* rag.K.kmax PARAM */, data->simulationInfo->realParameter[21] /* rag.K.kmin PARAM */, data->simulationInfo->realParameter[19] /* rag.K.kabs PARAM */, data->simulationInfo->realParameter[14] /* rag.K.BW PARAM */, data->simulationInfo->realParameter[18] /* rag.K.f PARAM */), data->localData[0]->realVars[14] /* rag.Qsto variable */);
  TRACE_POP
}
/*
equation index: 62
type: SIMPLE_ASSIGN
$DER.rag.Qsto2 = rag.K.kmax * rag.Qsto1 - $cse1 * rag.Qsto2
*/
void System_eqFunction_62(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,62};
  data->localData[0]->realVars[9] /* der(rag.Qsto2) STATE_DER */ = (data->simulationInfo->realParameter[20] /* rag.K.kmax PARAM */) * (data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */) - ((data->localData[0]->realVars[10] /* $cse1 variable */) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */));
  TRACE_POP
}
/*
equation index: 63
type: SIMPLE_ASSIGN
$DER.rag.Qgut = $cse1 * rag.Qsto2 - rag.K.kabs * rag.Qgut
*/
void System_eqFunction_63(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,63};
  data->localData[0]->realVars[7] /* der(rag.Qgut) STATE_DER */ = (data->localData[0]->realVars[10] /* $cse1 variable */) * (data->localData[0]->realVars[4] /* rag.Qsto2 STATE(1) */) - ((data->simulationInfo->realParameter[19] /* rag.K.kabs PARAM */) * (data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */));
  TRACE_POP
}
/*
equation index: 64
type: SIMPLE_ASSIGN
rag.Rameal = rag.K.f * rag.K.kabs * rag.Qgut / rag.K.BW
*/
void System_eqFunction_64(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,64};
  data->localData[0]->realVars[15] /* rag.Rameal variable */ = (data->simulationInfo->realParameter[18] /* rag.K.f PARAM */) * ((data->simulationInfo->realParameter[19] /* rag.K.kabs PARAM */) * (DIVISION_SIM(data->localData[0]->realVars[2] /* rag.Qgut STATE(1) */,data->simulationInfo->realParameter[14] /* rag.K.BW PARAM */,"rag.K.BW",equationIndexes)));
  TRACE_POP
}
/*
equation index: 65
type: SIMPLE_ASSIGN
$DER.pa.Gp = 20.0 * rag.Rameal + (-0.1) * pa.Gp + (-1e-05) * pa.I * pa.Gp
*/
void System_eqFunction_65(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,65};
  data->localData[0]->realVars[5] /* der(pa.Gp) STATE_DER */ = (20.0) * (data->localData[0]->realVars[15] /* rag.Rameal variable */) + (-0.1) * (data->localData[0]->realVars[0] /* pa.Gp STATE(1) */) + (-1e-05) * ((data->localData[0]->realVars[12] /* pa.I variable */) * (data->localData[0]->realVars[0] /* pa.Gp STATE(1) */));
  TRACE_POP
}
/*
equation index: 66
type: WHEN

when {$whenCondition2} then
  gen.meal_off = not pre(gen.meal_off);
end when;
*/
void System_eqFunction_66(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,66};
  if((data->localData[0]->booleanVars[1] /* $whenCondition2 DISCRETE */ && !data->simulationInfo->booleanVarsPre[1] /* $whenCondition2 DISCRETE */ /* edge */))
  {
    data->localData[0]->booleanVars[7] /* gen.meal_off DISCRETE */ = (!data->simulationInfo->booleanVarsPre[7] /* gen.meal_off DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 67
type: SIMPLE_ASSIGN
$whenCondition3 = gen.meal_off and not pre(gen.meal_off)
*/
void System_eqFunction_67(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,67};
  data->localData[0]->booleanVars[2] /* $whenCondition3 DISCRETE */ = (data->localData[0]->booleanVars[7] /* gen.meal_off DISCRETE */ && (!data->simulationInfo->booleanVarsPre[7] /* gen.meal_off DISCRETE */));
  TRACE_POP
}
/*
equation index: 68
type: WHEN

when {$whenCondition1} then
  gen.meal_on = not pre(gen.meal_on);
end when;
*/
void System_eqFunction_68(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,68};
  if((data->localData[0]->booleanVars[0] /* $whenCondition1 DISCRETE */ && !data->simulationInfo->booleanVarsPre[0] /* $whenCondition1 DISCRETE */ /* edge */))
  {
    data->localData[0]->booleanVars[8] /* gen.meal_on DISCRETE */ = (!data->simulationInfo->booleanVarsPre[8] /* gen.meal_on DISCRETE */);
  }
  TRACE_POP
}
/*
equation index: 69
type: SIMPLE_ASSIGN
$whenCondition4 = gen.meal_on and not pre(gen.meal_on)
*/
void System_eqFunction_69(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,69};
  data->localData[0]->booleanVars[3] /* $whenCondition4 DISCRETE */ = (data->localData[0]->booleanVars[8] /* gen.meal_on DISCRETE */ && (!data->simulationInfo->booleanVarsPre[8] /* gen.meal_on DISCRETE */));
  TRACE_POP
}
/*
equation index: 70
type: WHEN

when {$whenCondition4} then
  gen.delta = gen.par_delta;
end when;
*/
void System_eqFunction_70(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,70};
  if((data->localData[0]->booleanVars[3] /* $whenCondition4 DISCRETE */ && !data->simulationInfo->booleanVarsPre[3] /* $whenCondition4 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[16] /* gen.delta DISCRETE */ = data->simulationInfo->realParameter[2] /* gen.par_delta PARAM */;
  }
  else if((data->localData[0]->booleanVars[2] /* $whenCondition3 DISCRETE */ && !data->simulationInfo->booleanVarsPre[2] /* $whenCondition3 DISCRETE */ /* edge */))
  {
    data->localData[0]->realVars[16] /* gen.delta DISCRETE */ = 0.0;
  }
  TRACE_POP
}
/*
equation index: 72
type: SIMPLE_ASSIGN
$DER.rag.Qsto1 = rag.K.Dose * gen.delta - rag.K.kmax * rag.Qsto1
*/
void System_eqFunction_72(DATA *data, threadData_t *threadData)
{
  TRACE_PUSH
  const int equationIndexes[2] = {1,72};
  data->localData[0]->realVars[8] /* der(rag.Qsto1) STATE_DER */ = (data->simulationInfo->realParameter[15] /* rag.K.Dose PARAM */) * (data->localData[0]->realVars[16] /* gen.delta DISCRETE */) - ((data->simulationInfo->realParameter[20] /* rag.K.kmax PARAM */) * (data->localData[0]->realVars[3] /* rag.Qsto1 STATE(1) */));
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
  System_eqFunction_51(data, threadData);

  System_eqFunction_52(data, threadData);

  System_eqFunction_53(data, threadData);

  System_eqFunction_54(data, threadData);

  System_eqFunction_55(data, threadData);

  System_eqFunction_56(data, threadData);

  System_eqFunction_57(data, threadData);

  System_eqFunction_58(data, threadData);

  System_eqFunction_59(data, threadData);

  System_eqFunction_60(data, threadData);

  System_eqFunction_61(data, threadData);

  System_eqFunction_62(data, threadData);

  System_eqFunction_63(data, threadData);

  System_eqFunction_64(data, threadData);

  System_eqFunction_65(data, threadData);

  System_eqFunction_66(data, threadData);

  System_eqFunction_67(data, threadData);

  System_eqFunction_68(data, threadData);

  System_eqFunction_69(data, threadData);

  System_eqFunction_70(data, threadData);

  System_eqFunction_72(data, threadData);
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
extern void System_eqFunction_51(DATA* data, threadData_t *threadData);
extern void System_eqFunction_52(DATA* data, threadData_t *threadData);
extern void System_eqFunction_53(DATA* data, threadData_t *threadData);
extern void System_eqFunction_56(DATA* data, threadData_t *threadData);
extern void System_eqFunction_57(DATA* data, threadData_t *threadData);
extern void System_eqFunction_58(DATA* data, threadData_t *threadData);
extern void System_eqFunction_59(DATA* data, threadData_t *threadData);
extern void System_eqFunction_60(DATA* data, threadData_t *threadData);
extern void System_eqFunction_61(DATA* data, threadData_t *threadData);
extern void System_eqFunction_62(DATA* data, threadData_t *threadData);
extern void System_eqFunction_63(DATA* data, threadData_t *threadData);
extern void System_eqFunction_64(DATA* data, threadData_t *threadData);
extern void System_eqFunction_65(DATA* data, threadData_t *threadData);
extern void System_eqFunction_67(DATA* data, threadData_t *threadData);
extern void System_eqFunction_69(DATA* data, threadData_t *threadData);
extern void System_eqFunction_72(DATA* data, threadData_t *threadData);

static void functionODE_system0(DATA *data, threadData_t *threadData)
{
    System_eqFunction_51(data, threadData);

    System_eqFunction_52(data, threadData);

    System_eqFunction_53(data, threadData);

    System_eqFunction_56(data, threadData);

    System_eqFunction_57(data, threadData);

    System_eqFunction_58(data, threadData);

    System_eqFunction_59(data, threadData);

    System_eqFunction_60(data, threadData);

    System_eqFunction_61(data, threadData);

    System_eqFunction_62(data, threadData);

    System_eqFunction_63(data, threadData);

    System_eqFunction_64(data, threadData);

    System_eqFunction_65(data, threadData);

    System_eqFunction_67(data, threadData);

    System_eqFunction_69(data, threadData);

    System_eqFunction_72(data, threadData);
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
#define _OMC_LIT_RESOURCE_0_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_name,9,_OMC_LIT_RESOURCE_0_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir,54,_OMC_LIT_RESOURCE_0_dir_data);

#define _OMC_LIT_RESOURCE_1_name_data "KPar"
#define _OMC_LIT_RESOURCE_1_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_name,4,_OMC_LIT_RESOURCE_1_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir,54,_OMC_LIT_RESOURCE_1_dir_data);

#define _OMC_LIT_RESOURCE_2_name_data "MealGenerator"
#define _OMC_LIT_RESOURCE_2_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_name,13,_OMC_LIT_RESOURCE_2_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir,54,_OMC_LIT_RESOURCE_2_dir_data);

#define _OMC_LIT_RESOURCE_3_name_data "Monitor_Average"
#define _OMC_LIT_RESOURCE_3_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_name,15,_OMC_LIT_RESOURCE_3_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir,54,_OMC_LIT_RESOURCE_3_dir_data);

#define _OMC_LIT_RESOURCE_4_name_data "Monitor_Pump"
#define _OMC_LIT_RESOURCE_4_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_name,12,_OMC_LIT_RESOURCE_4_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir,54,_OMC_LIT_RESOURCE_4_dir_data);

#define _OMC_LIT_RESOURCE_5_name_data "OutputBool"
#define _OMC_LIT_RESOURCE_5_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_name,10,_OMC_LIT_RESOURCE_5_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir,54,_OMC_LIT_RESOURCE_5_dir_data);

#define _OMC_LIT_RESOURCE_6_name_data "OutputInt"
#define _OMC_LIT_RESOURCE_6_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_name,9,_OMC_LIT_RESOURCE_6_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir,54,_OMC_LIT_RESOURCE_6_dir_data);

#define _OMC_LIT_RESOURCE_7_name_data "OutputReal"
#define _OMC_LIT_RESOURCE_7_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_name,10,_OMC_LIT_RESOURCE_7_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir,54,_OMC_LIT_RESOURCE_7_dir_data);

#define _OMC_LIT_RESOURCE_8_name_data "Patient"
#define _OMC_LIT_RESOURCE_8_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_name,7,_OMC_LIT_RESOURCE_8_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir,54,_OMC_LIT_RESOURCE_8_dir_data);

#define _OMC_LIT_RESOURCE_9_name_data "Pump"
#define _OMC_LIT_RESOURCE_9_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_name,4,_OMC_LIT_RESOURCE_9_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir,54,_OMC_LIT_RESOURCE_9_dir_data);

#define _OMC_LIT_RESOURCE_10_name_data "Rate_Appearance_Glucose"
#define _OMC_LIT_RESOURCE_10_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_name,23,_OMC_LIT_RESOURCE_10_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir,54,_OMC_LIT_RESOURCE_10_dir_data);

#define _OMC_LIT_RESOURCE_11_name_data "System"
#define _OMC_LIT_RESOURCE_11_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_name,6,_OMC_LIT_RESOURCE_11_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir,54,_OMC_LIT_RESOURCE_11_dir_data);

#define _OMC_LIT_RESOURCE_12_name_data "k_empt"
#define _OMC_LIT_RESOURCE_12_dir_data "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models"
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_name,6,_OMC_LIT_RESOURCE_12_name_data);
static const MMC_DEFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir,54,_OMC_LIT_RESOURCE_12_dir_data);

static const MMC_DEFSTRUCTLIT(_OMC_LIT_RESOURCES,26,MMC_ARRAY_TAG) {MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_0_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_1_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_2_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_3_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_4_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_5_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_6_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_7_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_8_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_9_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_10_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_11_dir), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_name), MMC_REFSTRINGLIT(_OMC_LIT_RESOURCE_12_dir)}};
void System_setupDataStruc(DATA *data, threadData_t *threadData)
{
  assertStreamPrint(threadData,0!=data, "Error while initialize Data");
  threadData->localRoots[LOCAL_ROOT_SIMULATION_DATA] = data;
  data->callback = &System_callback;
  OpenModelica_updateUriMapping(threadData, MMC_REFSTRUCTLIT(_OMC_LIT_RESOURCES));
  data->modelData->modelName = "System";
  data->modelData->modelFilePrefix = "System";
  data->modelData->resultFileName = NULL;
  data->modelData->modelDir = "/home/leeoos/Projects/Modelica/Insulin-Pump/Prj/Models";
  data->modelData->modelGUID = "{8bfc621c-a0f4-42a8-92cd-7b249f946605}";
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
  data->modelData->nVariablesReal = 24;
  data->modelData->nDiscreteReal = 8;
  data->modelData->nVariablesInteger = 0;
  data->modelData->nVariablesBoolean = 12;
  data->modelData->nVariablesString = 0;
  data->modelData->nParametersReal = 22;
  data->modelData->nParametersInteger = 0;
  data->modelData->nParametersBoolean = 0;
  data->modelData->nParametersString = 0;
  data->modelData->nInputVars = 0;
  data->modelData->nOutputVars = 0;
  
  data->modelData->nAliasReal = 6;
  data->modelData->nAliasInteger = 0;
  data->modelData->nAliasBoolean = 0;
  data->modelData->nAliasString = 0;
  
  data->modelData->nZeroCrossings = 0;
  data->modelData->nSamples = 5;
  data->modelData->nRelations = 0;
  data->modelData->nMathEvents = 0;
  data->modelData->nExtObjs = 0;
  
  data->modelData->modelDataXml.fileName = "System_info.json";
  data->modelData->modelDataXml.modelInfoXmlLength = 0;
  data->modelData->modelDataXml.nFunctions = 2;
  data->modelData->modelDataXml.nProfileBlocks = 0;
  data->modelData->modelDataXml.nEquations = 73;
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


