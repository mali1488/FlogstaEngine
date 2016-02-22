#version 120 
//attribute vec4 inPosition;
attribute vec3 normal;
attribute vec4 inPosition; 


uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat4 ModelView;
uniform vec3 light_position;

varying vec3 N;
varying vec3 L;
varying vec3 Vv;
varying vec3 H;

void main(void) { 
    gl_Position = P * V * M  * (inPosition);
    N = normalize(mat3(ModelView) * normal);
    L = (vec3(light_position - (mat3(ModelView)*inPosition.xyz)));
    Vv = normalize(-(mat3(ModelView)*inPosition.xyz));
    H = normalize(L + Vv);
}
