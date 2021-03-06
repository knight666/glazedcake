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

// C/C++

#include <stdint.h>
#include <time.h>

// Qt

#include <QtCore/qsystemdetection.h>

#include <QtCore/QByteArray>
#include <QtCore/QSharedPointer>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QVector>

// Windows

#ifdef Q_OS_WIN
	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS
	#endif

	#ifndef _CRT_SECURE_NO_DEPRECATE
		#define _CRT_SECURE_NO_DEPRECATE
	#endif

	#ifndef UNICODE
		#define UNICODE
	#endif

	#ifndef WIN32_LEAN_AND_MEAN
		#define WIN32_LEAN_AND_MEAN
	#endif

	#ifndef VC_EXTRALEAN
		#define VC_EXTRALEAN
	#endif

	#include <Windows.h>
#endif

// String functions

namespace GlazedCake {

	template <size_t SizeInBytes>
	inline void strcpy_safe(char(&buffer)[SizeInBytes], const char* source)
	{
	#ifdef Q_OS_WIN
		strncpy_s(buffer, source, SizeInBytes);
	#else
		strncpy(buffer, source, SizeInBytes);
	#endif

		buffer[SizeInBytes - 1] = 0;
	}

	template <size_t SizeInBytes>
	inline void sprintf_safe(char(&buffer)[SizeInBytes], const char* format, ...)
	{
		va_list args;
		va_start(args, format);
	#ifdef Q_OS_WIN
		vsnprintf_s(buffer, SizeInBytes, format, args);
	#else
		vsnprintf(buffer, SizeInBytes, format, args);
	#endif
		va_end(args);

		buffer[SizeInBytes - 1] = 0;
	}

};
