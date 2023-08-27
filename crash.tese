#version 440
layout(triangles, equal_spacing, cw) in;

layout(constant_id = 0) const int MAX_NUM_DESCRIPTOR_IMAGES = 100;

layout(location = 0) in vec2 inHeightTexCoordinates[];
layout(location = 1) in int inHeightTextureIndex[];

layout(set = 0, binding = 1) uniform sampler textureSampler;
layout(set = 1, binding = 1) uniform texture2D heightTextures[MAX_NUM_DESCRIPTOR_IMAGES];

vec2 mixVec2(const vec2 vectors[gl_MaxPatchVertices]) {
    return gl_TessCoord.x * vectors[0] + gl_TessCoord.y * vectors[1] + gl_TessCoord.z * vectors[2];
}

void main() {
    vec2 heightTexCoordinates = mixVec2(inHeightTexCoordinates);
    int heightTextureIndex = inHeightTextureIndex[0];
    float extraHeight = texture(sampler2D(heightTextures[heightTextureIndex], textureSampler), heightTexCoordinates).r;
}
