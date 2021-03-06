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
#include "core\string_format.h"

#include <thirdparty/ini/ini.h>

namespace redox {
	namespace detail {
		class value_proxy {
		public:
			value_proxy(ini_t* conf, StringView group, StringView value) {
				_ini_val = ini_get(conf, group.data(), value.data());
				if (_ini_val == nullptr)
					throw Exception("failed to load ini key");
			}

			template<class T>
			auto as() const {
				return redox::parse<T>(_ini_val);
			}

			template<class T>
			operator T() const {
				return as<T>();
			}

		private:
			const char* _ini_val;
		};
	}

	class Configuration {
	public:
		Configuration(const Path& file);
		~Configuration();

		detail::value_proxy get(StringView group, StringView value) const;

	private:
		ini_t* _config;
	};
}