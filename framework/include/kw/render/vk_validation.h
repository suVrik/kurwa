/**
 *  Copyright (c) 2018, 21DOGZ.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 *  except in compliance with the License. You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software distributed under the License is
 *  distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and limitations under the License.
 */

#pragma once

#include <vulkan/vulkan.h>
#include <kw/base/vector.h>

namespace kw {
namespace render {

class VkValidation {
public:
    explicit VkValidation(VkInstance* instance);

    void destroy_debug_report_callback_EXT(VkInstance* instance);

    static bool check_validation_layer_support();

    static uint32_t validation_layers_size();

    static const char* const* validation_layers_data();

private:
    static VKAPI_ATTR VkBool32 VKAPI_CALL debug_callback(
            VkDebugReportFlagsEXT flags,
            VkDebugReportObjectTypeEXT obj_type,
            uint64_t obj,
            size_t location,
            int32_t code,
            const char* layer_prefix,
            const char* msg,
            void* user_data);

    VkDebugReportCallbackEXT validation_callback;

    VkResult create_debug_callback_EXT(VkInstance* instance, const VkDebugReportCallbackCreateInfoEXT* create_info);

    static const kw::Vector<const char*> validation_layers;
};

} // namespace render
} // namespace kw
