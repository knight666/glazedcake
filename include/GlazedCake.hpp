/*
    Copyright (C) 2017 Quinten Lansu

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include "public/Base.hpp"

#include "public/Context.hpp"
#include "public/Levels.hpp"
#include "public/Module.hpp"
#include "public/Sink.hpp"

#define GC_LOG_INFO(_module) \
	::GlazedCake::Context(&::GlazedCake::Printer::get(), ::GlazedCake::Level::Information, ::GlazedCake::Module(#_module), __FILE__, __LINE__)

#define GC_LOG_TRACE(_module)  \
	::GlazedCake::Context(&::GlazedCake::Printer::get(), ::GlazedCake::Level::Trace, ::GlazedCake::Module(#_module), __FILE__, __LINE__)

#define GC_LOG_WARN(_module) \
	::GlazedCake::Context(&::GlazedCake::Printer::get(), ::GlazedCake::Level::Warning, ::GlazedCake::Module(#_module), __FILE__, __LINE__)

#define GC_LOG_ERROR(_module) \
	::GlazedCake::Context(&::GlazedCake::Printer::get(), ::GlazedCake::Level::Error, ::GlazedCake::Module(#_module), __FILE__, __LINE__)

#define GC_LOG_FATAL(_module) \
	::GlazedCake::Context(&::GlazedCake::Printer::get(), ::GlazedCake::Level::Fatal, ::GlazedCake::Module(#_module), __FILE__, __LINE__)

namespace GlazedCake {

	class Printer
	{

	public:
		static const Module ModuleAll;

	public:
		Printer();
		~Printer();

		static Printer& get();
		static void setInstance(Printer* instance);

		inline void addSink(QSharedPointer<Sink> sink, const char* moduleName)
		{
			return addSink(sink, Module(moduleName));
		}
		void addSink(QSharedPointer<Sink> sink, const Module& module = ModuleAll);

		void write(const Module& module, Level level, const char* filePath, int line, const char* message);

	private:
		static Printer* s_instance;
		static bool s_instanceManaged;

	private:
		QHash<Module, QVector<QSharedPointer<Sink>>> m_sinksByModule;

	};

};
