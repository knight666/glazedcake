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

#include <GlazedCake.hpp>
#include <public/sinks/SinkDebugOutput.hpp>

int main(int argc, char** argv)
{
	// GlazedCake does not require Qt to be initialized before you use it, but
	// some of the "sinks" (writers of messages) _do_.

	// this message will fall through the cracks, because no sinks have been
	// added yet

	GC_LOG_INFO("HelloWorld") << "Hello World!";

	// this sink does not have any dependencies and can be used before
	// QApplication is initialized

	QSharedPointer<GlazedCake::Sink> sink(new GlazedCake::SinkDebugOutput());

	// sinks can be added to specific channels, or the "any" channel by default

	GlazedCake::Printer::get().addSink(sink);

	// this message will now appear in the console!

	GC_LOG_INFO("HelloWorld") << "Hello World!";

	return 0;
}
