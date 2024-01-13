#pragma once

#include "Graphics/Vulkan/VulkanConstants.h"

#include <vulkan/vulkan.h>
#include <spirv_cross/spirv_cross.hpp>

enum ShaderStage
{
    Vertex,
    Fragment,
    Compute,

    Count
};

class Shader
{
public:

    Shader(const char* filePath, ShaderStage stage, const char* name = "");
    Shader(const char* data, uint32_t size, ShaderStage stage, const char* name = "");


protected:

    friend class DestroyQueue;
    ~Shader();

    void Create(const char* data, uint32_t size);

public:

    std::string mName;
    ShaderStage mStage;
    VkShaderModule mModule = VK_NULL_HANDLE;
    VkDescriptorSetLayout mDescriptorSetLayouts[MAX_BOUND_DESCRIPTOR_SETS] = {};
};

