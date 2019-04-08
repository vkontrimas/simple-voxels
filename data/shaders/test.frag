#version 330 core

out vec4 out_frag_color;
in vec3 vert_color;

void main() {
    out_frag_color = vec4(vert_color, 1.0f);
}
