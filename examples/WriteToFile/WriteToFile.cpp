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
#include <public/sinks/SinkFile.hpp>

#include <QtCore/QCoreApplication>

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);

	QSharedPointer<GlazedCake::Sink> sinkPizza(new GlazedCake::SinkFile(QCoreApplication::applicationDirPath() + "/pizza.log"));
	QSharedPointer<GlazedCake::Sink> sinkDonut(new GlazedCake::SinkFile(QCoreApplication::applicationDirPath() + "/donut.log"));

	GlazedCake::Printer::get().addSink(sinkPizza, "Pizza");
	GlazedCake::Printer::get().addSink(sinkPizza, "Breakfast");
	GlazedCake::Printer::get().addSink(sinkDonut, "Donut");
	GlazedCake::Printer::get().addSink(sinkDonut, "Breakfast");

	GC_LOG_INFO(Pizza) << "Now with *MORE* cheese!";
	GC_LOG_INFO(Donut) << "Loved by law enforcement everywhere!";
	GC_LOG_INFO(Breakfast) << "Part of a wholesome breakfast!";

	return 0;
}
