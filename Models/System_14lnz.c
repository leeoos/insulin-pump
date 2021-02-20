/* Linearization */
#include "System_model.h"
#if defined(__cplusplus)
extern "C" {
#endif
const char *System_linear_model_frame()
{
  return "model linearized_model \"System\" \n  parameter Integer n = 5 \"number of states\";\n  parameter Integer m = 0 \"number of inputs\";\n  parameter Integer p = 0 \"number of outputs\";\n"
  "  parameter Real x0[n] = %s;\n"
  "  parameter Real u0[m] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "\n"
  "  Real 'x_pa.Gp' = x[1];\n""  Real 'x_pa.Ip' = x[2];\n""  Real 'x_rag.Qgut' = x[3];\n""  Real 'x_rag.Qsto1' = x[4];\n""  Real 'x_rag.Qsto2' = x[5];\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\nend linearized_model;\n";
}
const char *System_linear_model_datarecovery_frame()
{
  return "model linearized_model \"System\" \n parameter Integer n = 5 \"number of states\";\n  parameter Integer m = 0 \"number of inputs\";\n  parameter Integer p = 0 \"number of outputs\";\n  parameter Integer nz = 6 \"data recovery variables\";\n"
  "  parameter Real x0[5] = %s;\n"
  "  parameter Real u0[0] = %s;\n"
  "  parameter Real z0[6] = %s;\n"
  "\n"
  "  parameter Real A[n, n] =\n\t[%s];\n\n"
  "  parameter Real B[n, m] = zeros(n, m);%s\n\n"
  "  parameter Real C[p, n] = zeros(p, n);%s\n\n"
  "  parameter Real D[p, m] = zeros(p, m);%s\n\n"
  "  parameter Real Cz[nz, n] =\n\t[%s];\n\n"
  "  parameter Real Dz[nz, m] = zeros(nz, m);%s\n\n"
  "\n"
  "  Real x[n](start=x0);\n"
  "  input Real u[m];\n"
  "  output Real y[p];\n"
  "  output Real z[nz];\n"
  "\n"
  "  Real 'x_pa.Gp' = x[1];\n""  Real 'x_pa.Ip' = x[2];\n""  Real 'x_rag.Qgut' = x[3];\n""  Real 'x_rag.Qsto1' = x[4];\n""  Real 'x_rag.Qsto2' = x[5];\n"
  "  Real 'z_$cse1' = z[1];\n""  Real 'z_pa.G' = z[2];\n""  Real 'z_pa.I' = z[3];\n""  Real 'z_pu.err' = z[4];\n""  Real 'z_rag.Qsto' = z[5];\n""  Real 'z_rag.Rameal' = z[6];\n"
  "equation\n  der(x) = A * x + B * u;\n  y = C * x + D * u;\n  z = Cz * x + Dz * u;\nend linearized_model;\n";
}
#if defined(__cplusplus)
}
#endif

