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

#include "public/Printer.hpp"

namespace GlazedCake {

	Printer* Printer::s_instance = nullptr;
	bool Printer::s_instanceManaged = false;

	const Channel Printer::ChannelAny("any");

	Printer& Printer::get()
	{
		if (s_instance == nullptr)
		{
			s_instance = new Printer();
			s_instanceManaged = true;
		}

		return *s_instance;
	}

	void Printer::setInstance(Printer* instance)
	{
		destroy();

		s_instance = instance;
		s_instanceManaged = false;
	}

	void Printer::destroy()
	{
		if (s_instanceManaged &&
			s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

	Printer::Printer()
	{
	}

	Printer::~Printer()
	{
	}

	void Printer::addSink(QSharedPointer<Sink> sink, const Channel& channel /*= ChannelAny*/)
	{
		auto found = m_sinksByChannel.find(channel);
		if (found != m_sinksByChannel.end())
		{
			found.value().push_back(sink);
		}
		else
		{
			QVector<QSharedPointer<Sink>> sinks;
			sinks.push_back(sink);
			m_sinksByChannel.insert(channel, sinks);
		}
	}

	QVector<QSharedPointer<GlazedCake::Sink>> Printer::getSinksByChannel(const Channel& channel) const
	{
		auto found = m_sinksByChannel.find(channel);
		if (found != m_sinksByChannel.end())
		{
			return found.value();
		}

		return QVector<QSharedPointer<GlazedCake::Sink>>();
	}

	void Printer::write(const Channel& channel, Level level, const char* filePath, int line, const char* message)
	{
		QVector<QSharedPointer<Sink>>* channel_sinks = nullptr;

		auto found = m_sinksByChannel.find(channel);
		if (found != m_sinksByChannel.end())
		{
			channel_sinks = &found.value();
		}
		else
		{
			channel_sinks = &m_sinksByChannel[ChannelAny];
		}

		auto current_time = ::time(0);
		auto now = ::localtime(&current_time);

		char timestamp[32] = { 0 };
		sprintf_safe(timestamp, "%02d:%02d:%02d",
			now->tm_hour,
			now->tm_min,
			now->tm_sec);

		for (auto sink : *channel_sinks)
		{
			sink->write(level, timestamp, filePath, line, message);
		}
	}

};
