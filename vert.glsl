attribute vec4 VertPos;
varying vec2 FragPos;

void main() {
    gl_Position = VertPos;
    FragPos = VertPos.xy;
}