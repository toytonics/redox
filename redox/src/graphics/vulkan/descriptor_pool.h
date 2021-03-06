/*
redox
-----------
MIT License

Copyright (c) 2018 Luis von der Eltz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#pragma once
#include "core\non_copyable.h"
#include "vulkan.h"

namespace redox::graphics {
	class Graphics;
	class CommandBufferView;
	class Texture;
	class Pipeline;
	struct UniformBuffer;

	class DescriptorSetView {
	public:
		DescriptorSetView(VkDescriptorSet handle);

		void bind(const CommandBufferView& commandBuffer, const Pipeline& pipeline);
		void bind_resource(const Texture& texture, uint32_t bindingPoint);
		void bind_resource(const UniformBuffer& ubo, uint32_t bindingPoint);

	private:
		VkDescriptorSet _handle;
	};

	class DescriptorPool : public NonCopyable {
	public:
		DescriptorPool(uint32_t maxSets, uint32_t maxImages, uint32_t maxUBOs);
		~DescriptorPool();

		DescriptorSetView allocate(VkDescriptorSetLayout layout) const;

	private:
		VkDescriptorPool _handle;
	};
}