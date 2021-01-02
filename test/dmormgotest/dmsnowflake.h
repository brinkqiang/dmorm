
// Copyright (c) 2018 brinkqiang (brink.qiang@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __DMSNOWFLAKE_H_INCLUDE__
#define __DMSNOWFLAKE_H_INCLUDE__

#include <cstdint>
#include <mutex>
#include <memory>

class CDMIDGeneratorImpl;
class CDMIDGenerator
{
public:
	CDMIDGenerator(int region_id = 0, int worker_id = 0);//region_id in (0-15) , worker_id in (0-1023)
	~CDMIDGenerator();

	void Init(int region_id = 0, int worker_id = 0);
	uint64_t GetNextID();

private:
	std::unique_ptr<CDMIDGeneratorImpl> m_oImpl;
};


#endif // __DMSNOWFLAKE_H_INCLUDE__