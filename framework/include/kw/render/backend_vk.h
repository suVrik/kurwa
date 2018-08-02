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

#include "renderering_backend.h"
#include "vk_validation.h"
#include <vulkan/vulkan.h>

namespace kw {
namespace render {

/**
 * BackendVk is a class that implements a Vulkan rendering backend.
 */
class BackendVk : public RenderingBackend {
public:
    explicit BackendVk(kw::IGame* game) noexcept;
    BackendVk(const BackendVk& original) = delete;
    BackendVk& operator=(const BackendVk& original) = delete;
    ~BackendVk() override;

    /**
     * Execute the commands in a command buffer and present the resulting image.
     */
    void process_command_buffer(CommandBuffer&& command_buffer) override;
private:
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        kw::Vector<VkSurfaceFormatKHR> formats;
        kw::Vector<VkPresentModeKHR> present_modes;
    };

    void on_init_listener(kw::IGame* game) override;
    void create_instance();
    void create_surface();
    void pick_physical_device();
    int32_t get_suitable_queue_family_id(const VkPhysicalDevice& device);
    void create_logical_device();
    void cleanup();
    kw::Vector<const char*> get_instance_extensions();
    bool check_device_extension_support(VkPhysicalDevice device);
    bool is_device_suitable(VkPhysicalDevice device);
    SwapChainSupportDetails query_swapchain_support(VkPhysicalDevice device);
    VkSurfaceFormatKHR choose_swap_surface_format(const kw::Vector<VkSurfaceFormatKHR>& available_formats);
    VkExtent2D choose_swap_extent(const VkSurfaceCapabilitiesKHR& capabilities);
    void create_swapchain();
    void create_image_views();
    void create_render_pass();
    void create_framebuffers();
    void create_command_pool();
    void callocate_command_buffers();
    uint32_t acquire_next_frame() const;
    void draw_frame(uint32_t image_index);
    void create_sync_objects();

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
#ifdef KW_DEBUG
    const bool enable_validation_layers = true;
#else
    const bool enable_validation_layers = false;
#endif
    const unsigned long MAX_FRAMES_IN_FLIGHT = 1;
    size_t currentFrame = 0;
    VkInstance instance;
    VkSurfaceKHR surface;
    VkDevice device;
    VkPhysicalDevice physical_device;
    VkValidation* validation;
    VkQueue graphics_queue;
    VkQueue present_queue;
    VkSwapchainKHR swapchain;
    kw::Vector<VkImage> swapchain_images;
    VkFormat swapchain_image_format;
    VkExtent2D swapchain_extent;
    kw::Vector<VkImageView> swapchain_image_views;
    kw::Vector<VkFramebuffer> swapchain_framebuffers;
    VkRenderPass renderpass;
    VkCommandPool command_pool;
    kw::Vector<VkCommandBuffer> command_buffers;
    kw::Vector<VkSemaphore> image_available_semaphores;
    kw::Vector<VkSemaphore> render_finished_semaphores;
    kw::Vector<VkFence> in_flight_fences;
    static const kw::Vector<const char*> device_extensions;
};

} // namespace render
} // namespace kw
