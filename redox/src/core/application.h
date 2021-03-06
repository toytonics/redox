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
#include <platform/window.h>
#include <graphics/vulkan/render_system.h>
#include <core/config/config.h>
#include <platform/timer.h>
#include <input/input_system.h>
#include <resources/resource_manager.h>

#include <thread> //std::thread::id

namespace redox {
	class Application {
	public:
		Application(Path directory);
		~Application();

		static Application* instance;

		enum class State {
			RUNNING, PAUSED, TERMINATED
		};

		void run();
		void stop();

		std::thread::id main_thread() const;

		const Configuration* config() const;
		const platform::Timer* timer() const;
		const input::InputSystem* input_system() const;
		const graphics::RenderSystem* render_system() const;
		const graphics::Graphics* graphics() const;

		ResourceManager* resource_manager();

	private:
		void _init_window();

		static_instance_wrapper _iw{ this };
		std::thread::id _threadId;
		Path _directory;
		Configuration _config;
		platform::Timer _timer;

		UniquePtr<ResourceManager> _resourceManager;
		UniquePtr<platform::Window> _window;
		UniquePtr<input::InputSystem> _inputSystem;
		UniquePtr<graphics::Graphics> _graphics;
		UniquePtr<graphics::RenderSystem> _renderSystem;

		Application::State _state;
	};
}