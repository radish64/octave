#version 450
#extension GL_ARB_separate_shader_objects : enable

#include "Common.glsl"

layout (set = 0, binding = 0) uniform GlobalUniformBuffer 
{
    GlobalUniforms global;
};

layout (set = 1, binding = 0) uniform sampler2D samplerLitColor;
layout (set = 1, binding = 1) uniform sampler2D pathTraceImage;

layout (location = 0) in vec2 inTexcoord;

layout (location = 0) out vec4 outFinalColor;

void main()
{
    vec4 linearColor = vec4(0,0,0,1);

    if (global.mPathTracingEnabled != 0)
    {
        linearColor = texture(pathTraceImage, inTexcoord);
    }
    else
    {
        linearColor = texture(samplerLitColor, inTexcoord);
    }

    // Gamma correct
    vec4 srgbColor = LinearToSrgb(linearColor);

    outFinalColor = srgbColor;
}