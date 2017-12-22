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

#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

class FatalSink
	: public GlazedCake::Sink
{

public:
	virtual void write(GlazedCake::Level level, const char* timestamp, const char* filePath, int line, const char* message) override
	{
		if (level != GlazedCake::Level::Fatal)
		{
			return;
		}

		QString combined = QString("%1 %2").arg(timestamp).arg(message);
		QMessageBox::critical(nullptr, "A very important message!", combined);
	}

};

class MainWindow
	: public QMainWindow
{

public:
	MainWindow()
	{
		
	}

};

class DemoApp
	: public QCoreApplication
{

public:


};

static void DemoInitialize()
{
	GlazedCake::Printer::get().addSink(QSharedPointer<GlazedCake::Sink>(new FatalSink()));

	GC_LOG_FATAL(CustomSink) << "I love you!";
}

Q_COREAPP_STARTUP_FUNCTION(DemoInitialize)

int main(int argc, char** argv)
{
	QCoreApplication app(argc, argv);

	return app.exec();
}
