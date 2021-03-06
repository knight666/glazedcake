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

namespace GlazedCake {

	class Channel
	{

	public:
		static const uint MaxNameLength = 32;

	public:
		Channel(const char* name)
		{
			build(name, static_cast<uint>(strlen(name)));
		}

		Channel(const char* name, uint nameLength)
		{
			build(name, nameLength);
		}

		const char* getName() const
		{
			return m_name;
		}

		quint16 getChecksum() const
		{
			return m_checksum;
		}

		operator quint16() const
		{
			return m_checksum;
		}

		bool operator < (const Channel& other) const
		{
			return m_checksum < other.m_checksum;
		}

		bool operator == (const Channel& other) const
		{
			return m_checksum == other.m_checksum;
		}

	private:
		inline void build(const char* name, uint nameLength)
		{
			if (nameLength < 1)
			{
				return;
			}

			// very straight-forward case folding, pretend UTF-8 doesn't exist!

			char* dst = m_name;
			const char* src = name;
			uint length = std::min<uint>(nameLength, MaxNameLength) - 1;

			for (uint i = 0; i < length; ++i)
			{
				bool is_upper = (*src >= 'A') && (*src <= 'Z');
				*dst++ = is_upper ? (*src | 0x20) : (*src);
				src++;
			}

			m_checksum = qChecksum(m_name, length);
		}

	private:
		char m_name[32] = { 0 };
		quint16 m_checksum = 0xFFFF;

	};

};