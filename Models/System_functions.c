#include "omc_simulation_settings.h"
#include "System_functions.h"
#ifdef __cplusplus
extern "C" {
#endif

#include "System_includes.h"


KPar omc_KPar(threadData_t *threadData, modelica_real omc_Dose, modelica_real omc_b, modelica_real omc_d, modelica_real omc_kmax, modelica_real omc_kmin, modelica_real omc_kabs, modelica_real omc_BW, modelica_real omc_f)
{
  KPar tmp1;
  tmp1._Dose = omc_Dose;
  tmp1._b = omc_b;
  tmp1._d = omc_d;
  tmp1._kmax = omc_kmax;
  tmp1._kmin = omc_kmin;
  tmp1._kabs = omc_kabs;
  tmp1._BW = omc_BW;
  tmp1._f = omc_f;
  return tmp1;
}

modelica_metatype boxptr_KPar(threadData_t *threadData, modelica_metatype _Dose, modelica_metatype _b, modelica_metatype _d, modelica_metatype _kmax, modelica_metatype _kmin, modelica_metatype _kabs, modelica_metatype _BW, modelica_metatype _f)
{
  return mmc_mk_box9(3, &KPar__desc, _Dose, _b, _d, _kmax, _kmin, _kabs, _BW, _f);
}

DLLExport
modelica_real omc_k__empt(threadData_t *threadData, KPar _K, modelica_real _Q)
{
  modelica_real _y;
  modelica_real _alpha;
  modelica_real _beta;
  modelica_real tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  _tailrecursive: OMC_LABEL_UNUSED
  // _y has no default value.
  // _alpha has no default value.
  // _beta has no default value.
  tmp1 = ((2.0) * (_K._Dose)) * (1.0 - _K._b);
  if (tmp1 == 0) {throwStreamPrint(threadData, "Division by zero %s", "5.0 / (2.0 * K.Dose * (1.0 - K.b))");}
  _alpha = (5.0) / tmp1;

  tmp2 = ((2.0) * (_K._Dose)) * (_K._d);
  if (tmp2 == 0) {throwStreamPrint(threadData, "Division by zero %s", "5.0 / (2.0 * K.Dose * K.d)");}
  _beta = (5.0) / tmp2;

  tmp3 = 2.0;
  if (tmp3 == 0) {throwStreamPrint(threadData, "Division by zero %s", "(K.kmax - K.kmin) / 2.0");}
  _y = _K._kmin + ((_K._kmax - _K._kmin) / tmp3) * (tanh((_alpha) * (_Q - ((_beta) * (_K._Dose)))) - tanh((_beta) * (_Q - ((_K._d) * (_K._Dose)))) + 2.0);
  _return: OMC_LABEL_UNUSED
  return _y;
}
modelica_metatype boxptr_k__empt(threadData_t *threadData, modelica_metatype _K, modelica_metatype _Q)
{
  KPar tmp1;
  modelica_real tmp2;
  modelica_real tmp3;
  modelica_real tmp4;
  modelica_real tmp5;
  modelica_real tmp6;
  modelica_real tmp7;
  modelica_real tmp8;
  modelica_real tmp9;
  modelica_real tmp10;
  modelica_real _y;
  modelica_metatype out_y;
  modelica_metatype tmpMeta[8] __attribute__((unused)) = {0};
  tmpMeta[0] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 2)));
  tmp2 = mmc_unbox_real(tmpMeta[0]);
  tmp1._Dose = tmp2;
  tmpMeta[1] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 3)));
  tmp3 = mmc_unbox_real(tmpMeta[1]);
  tmp1._b = tmp3;
  tmpMeta[2] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 4)));
  tmp4 = mmc_unbox_real(tmpMeta[2]);
  tmp1._d = tmp4;
  tmpMeta[3] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 5)));
  tmp5 = mmc_unbox_real(tmpMeta[3]);
  tmp1._kmax = tmp5;
  tmpMeta[4] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 6)));
  tmp6 = mmc_unbox_real(tmpMeta[4]);
  tmp1._kmin = tmp6;
  tmpMeta[5] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 7)));
  tmp7 = mmc_unbox_real(tmpMeta[5]);
  tmp1._kabs = tmp7;
  tmpMeta[6] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 8)));
  tmp8 = mmc_unbox_real(tmpMeta[6]);
  tmp1._BW = tmp8;
  tmpMeta[7] = (MMC_FETCH(MMC_OFFSET(MMC_UNTAGPTR(_K), 9)));
  tmp9 = mmc_unbox_real(tmpMeta[7]);
  tmp1._f = tmp9;tmp10 = mmc_unbox_real(_Q);
  _y = omc_k__empt(threadData, tmp1, tmp10);
  out_y = mmc_mk_rcon(_y);
  return out_y;
}

#ifdef __cplusplus
}
#endif
