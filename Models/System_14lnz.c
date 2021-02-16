/* Linearization */
#include "System_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *System_linear_model_frame()
{
  return "model linearized_model \"System\" \n  parameter Integer n = 0 \"number of states\";\n  parameter Integer m = 0 \"number of inputs\";\n  parameter Integer p = 0 \"number of outputs\";\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "\n"
  "  parameter Real A[n, n] = zeros(n, n);%s\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "\n"
  "  Real x[n];\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linearized_model;\n";
}
const char *System_linear_model_datarecovery_frame()
{
  return "model linearized_model \"System\" \n parameter Integer n = 0 \"number of states\";\n  parameter Integer m = 0 \"number of inputs\";\n  parameter Integer p = 0 \"number of outputs\";\n  parameter Integer nz = 6 \"data recovery variables\";\n"
  "  parameter Real x0[0] = %s;\n"
  "  parameter Real u0[0] = %s;\n"
  "  parameter Real z0[6] = %s;\n"
  "\n"
  "  parameter Real A[n, n] = zeros(n, n);%s\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "  parameter Real Cz[nz, n] = zeros(nz, n);%s\n\n"
  "  parameter Real Dz[nz, m] = zeros(nz, m);%s\n\n"
  "\n"
  "  Real x[n];\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'z_$TMP_patient.glucose_4' = z[1];\n""  Real 'z_$TMP_pump.insulin_out_10' = z[2];\n""  Real 'z_generator.delta' = z[3];\n""  Real 'z_patient.glucose' = z[4];\n""  Real 'z_pump.insulin_out' = z[5];\n""  Real 'z_rag.ra_meal' = z[6];\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

