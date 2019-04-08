#version 330 core

in layout(location = 0) vec3 vert_position;
uniform mat4 matrix_mvp;
 
void main() {
    gl_Position = matrix_mvp * vec4(vert_position, 1.0);
}
