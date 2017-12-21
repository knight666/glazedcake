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

#include "GlazedCake.hpp"

namespace GlazedCake {

	Printer* Printer::s_instance = nullptr;
	bool Printer::s_instanceManaged = false;

	const Module Printer::ModuleAll("all");

	Printer::Printer()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
			s_instanceManaged = true;
		}
	}

	Printer::~Printer()
	{
	}

	Printer& Printer::get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new Printer();
		}

		return *s_instance;
	}

	void Printer::setInstance(Printer* instance)
	{
		if (s_instanceManaged &&
			s_instance != nullptr)
		{
			delete s_instance;
		}

		s_instance = instance;
		s_instanceManaged = false;
	}

	void Printer::addSink(QSharedPointer<Sink> sink, const Module& module /*= ModuleAll*/)
	{
		auto found = m_sinksByModule.find(module);
		if (found != m_sinksByModule.end())
		{
			found.value().push_back(sink);
		}
		else
		{
			QVector<QSharedPointer<Sink>> sinks;
			sinks.push_back(sink);
			m_sinksByModule.insert(module, sinks);
		}
	}

	void Printer::write(const Module& module, Level level, const char* filePath, int line, const char* message)
	{
		QVector<QSharedPointer<Sink>>* module_sinks = nullptr;

		auto found = m_sinksByModule.find(module);
		if (found != m_sinksByModule.end())
		{
			module_sinks = &found.value();
		}
		else
		{
			module_sinks = &m_sinksByModule[ModuleAll];
		}

		auto current_time = time(0);
		auto now = localtime(&current_time);

		char timestamp[32] = { 0 };
		_snprintf(timestamp, sizeof(timestamp), "%02d:%02d:%02d",
			now->tm_hour,
			now->tm_min,
			now->tm_sec);

		for (auto sink : *module_sinks)
		{
			sink->write(level, timestamp, filePath, line, message);
		}
	}

};
