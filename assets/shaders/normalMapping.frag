#version 120 
uniform vec3 view_pos;
uniform vec3 light_position;
uniform float specular_power;
uniform vec3 ambient_color;
uniform vec3 light_color;
uniform vec3 specular_color;
uniform vec3 diffuseColor;

varying vec3 N;
varying vec3 L;
varying vec3 Vv;
varying vec3 H;

void main(void) { 
    vec3 normal = vec3(0.0,0.0,0.0);
    normal = normalize(N);
    
    vec3 halvV = normalize(vec3(L + Vv));
    vec3 output_color = vec3(0.0,0.0,0.0);
    
    // Diffuse color
    output_color +=  diffuseColor * light_color * max(dot(normal,L),0.0);
    
    // Specular color
    output_color += specular_color * light_color * pow(max(dot(normal,halvV), 0.0),specular_power);
    
    // Gamma correction
    output_color = pow(output_color, vec3(1 / 2.2));
    gl_FragColor = vec4(output_color,1.0);
} 
