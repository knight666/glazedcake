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

#include "public/Channel.hpp"
#include "public/Levels.hpp"

namespace GlazedCake {

	class Printer;

	class Context
		: public QTextStream
	{

	public:
		Context(Printer* printer, const char* channelName, Level level, const char* filePath, int line);
		Context(Printer* printer, const Channel& channel, Level level, const char* filePath, int line);
		~Context();

	private:
		Printer* m_printer;
		Channel m_channel;
		Level m_level = Level::Information;
		char m_filePath[_MAX_PATH] = { 0 };
		int m_line = -1;
		QString m_message;

	};

};
