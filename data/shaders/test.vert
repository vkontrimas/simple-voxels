#version 330 core

in layout(location = 0) vec3 vert_position;
 
void main() {
    gl_Position = vec4(vert_position, 1.0);
}
