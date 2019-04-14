#version 330 core

layout(location = 0) in vec3 vert_position;
layout(location = 1) in vec3 vert_normal;

out vec3 vert_color;

uniform mat4 u_matrix_mvp;
uniform vec3 u_light_dir;
uniform float u_light_intensity;
uniform float u_ambient_light;
 
void main() {
    gl_Position = u_matrix_mvp * vec4(vert_position, 1.0);
    float dir_light = clamp(dot(vert_normal, -u_light_dir), 0.0, 1.0) * clamp(u_light_intensity, 0.0, 1.0);
    float amb_light = clamp(u_ambient_light, 0.0, 1.0);
    vert_color = vec3(1.0f) * clamp(dir_light + amb_light, 0.0, 1.0);
}
