#version 460 core

in VS_OUT {
    vec2 texCoord;
} fs_in;

out vec4 FragColor;

uniform sampler2D rayTracingTexture;
uniform sampler2D accretionDiskTexture;

void main() {
    vec4 rayTracingColor = texture(rayTracingTexture, fs_in.texCoord);
    vec4 accretionColor = texture(accretionDiskTexture, fs_in.texCoord);
    
    // Composite with alpha blending
    FragColor = mix(rayTracingColor, accretionColor, accretionColor.a);
}
