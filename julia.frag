#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout (location = 0) uniform vec2 u_resolution;
layout (location = 1) uniform vec2 u_c;
layout (location = 2) uniform vec2 u_offset;
layout (location = 3) uniform float u_zoom;
layout (location = 4) uniform float u_time; // [ms]
layout (location = 5) uniform int u_iterations;

layout (location = 0) out vec4 fragColor;

const float THRESHOLD = 2.0;

vec2 complex_multiply(vec2 a, vec2 b) {
    float i = a.x * b.x - a.y * b.y;
    float r = a.x * b.y + a.y * b.x;
    return vec2(i, r);
}

void main () {
    vec2 st = gl_FragCoord.xy / min(u_resolution.x, u_resolution.y);
    st = (st * (2.0 * u_zoom) - u_zoom) + u_offset;

    vec3 bgc = vec3(0.235, 0.066, 0.294);
    vec3 inc = vec3(0.043, 0.231, 0.031);
    vec3 color = vec3(0.0);

    vec2 z = st;
    for (int i = 0; i < u_iterations; i++) {
        z = complex_multiply(z, z) + u_c;
        if (length(z) > THRESHOLD)
            break;
    }

    float m = length(z);

    float j = step(0.9, m) - step(1.1, m);
    float f = smoothstep(0.0, 1.02, m) - step(0.98, m);
    float k = (1.0 - m*smoothstep(1.02, u_iterations, m)) * step(1.02, m);

    color += mix(vec3(0.5), bgc,  k);   // |z| > 1
    color = mix(color, inc,       f);   // |z| < 1
    color = mix(color, vec3(1.0), j);   // |z| = 1

    fragColor = vec4(color, 1.0);
}
