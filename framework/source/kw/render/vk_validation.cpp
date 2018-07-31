#include <kw/render/vk_validation.h>
#include <kw/debug/runtime_error.h>

namespace kw {
namespace render {

VkValidation::VkValidation(VkInstance* instance) {
    VkDebugReportCallbackCreateInfoEXT create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    create_info.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
    create_info.pfnCallback = debug_callback;

    if (create_debug_callback_EXT(instance, &create_info) != VK_SUCCESS) {
        throw kw::RuntimeError("Failed to set up validation callback!");
    }
};

uint32_t VkValidation::validation_layers_size() {
    return static_cast<uint32_t>(validation_layers.size());
}

const char* const* VkValidation::validation_layers_data() {
    return validation_layers.data();
}

bool VkValidation::check_validation_layer_support() {
    uint32_t layer_count;
    vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

    kw::Vector<VkLayerProperties> available_layers(layer_count);
    vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

    for (const char* layer_name : validation_layers) {
        bool layer_found = false;

        for (const auto& layer_properties : available_layers) {
            if (strcmp(layer_name, layer_properties.layerName) == 0) {
                layer_found = true;
                break;
            }
        }

        if (!layer_found) {
            return false;
        }
    }

    return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL VkValidation::debug_callback(
        VkDebugReportFlagsEXT flags,
        VkDebugReportObjectTypeEXT obj_type,
        uint64_t obj,
        size_t location,
        int32_t code,
        const char* layer_prefix,
        const char* msg,
        void* user_data) {
    fprintf(stderr, "Validation layer: %s\n", msg);
    return VK_FALSE;
}

VkResult
VkValidation::create_debug_callback_EXT(VkInstance* instance, const VkDebugReportCallbackCreateInfoEXT* create_info) {
    auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(*instance, "vkCreateDebugReportCallbackEXT");
    if (func != nullptr) {
        return func(*instance, create_info, nullptr, &validation_callback);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void VkValidation::destroy_debug_report_callback_EXT(VkInstance* instance) {
    auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(*instance, "vkDestroyDebugReportCallbackEXT");
    if (func != nullptr) {
        func(*instance, validation_callback, nullptr);
    }
}

const kw::Vector<const char*> VkValidation::validation_layers = {
        "VK_LAYER_LUNARG_standard_validation"
};

} // namespace render
} // namespace kw
