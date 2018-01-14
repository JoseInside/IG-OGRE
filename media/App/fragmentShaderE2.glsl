fragment_program fragmentShaderE2 glsl
{
source fragmentShaderE2glsl.txt // archivo
default_params // valores para las variable uniform
{
param_named_auto tiempoA time  // ??
param_named_auto tiempoE time_0_1 1 // [0, 1] ciclo 1
param_named_auto tiempoD sintime_0_1 50  // ciclo 50

param_named textura1 int 0 // unidad de textura
param_named textura2 int 1
param_named_auto FB time_0_1 10
param_named intLuz float 1.0;
}
}