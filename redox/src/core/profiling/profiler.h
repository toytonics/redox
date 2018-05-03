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
#include "core\core.h"
#include "core\string.h"
#include "platform\timer.h"

#include "core\logging\log.h"

#define _RDX_HELPER_CONCAT_IMPL(x,y) x##y
#define _RDX_HELPER_CONCAT(x,y) _RDX_HELPER_CONCAT_IMPL(x,y)

#define _RDX_PROFILE redox::Profiler _RDX_HELPER_CONCAT(_profiler_, __COUNTER__)(__FUNCTION__);

namespace redox {
	struct Profiler {
		_RDX_INLINE Profiler(const redox::String& name) {
			RDX_LOG("PROFILER: {0}", name);
			_timer.start();
		}

		_RDX_INLINE ~Profiler() {
			auto ms = _timer.elapsed();
			RDX_LOG("PROFILER: {0}ms", ms);
		}

		Timer _timer;
		HANDLE _perf;
	};
}