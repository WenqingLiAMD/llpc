/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2020-2023 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 ***********************************************************************************************************************
 * @file  RelocHandler.h
 * @brief LLPC header file: Class to handle internal relocatable values when ELF linking
 ***********************************************************************************************************************
 */
#pragma once

#include "llvm/ADT/StringRef.h"

namespace lgc {

class PipelineState;

// =====================================================================================================================
// Class to handle internal relocatable values when ELF linking
class RelocHandler {
public:
  RelocHandler(PipelineState *pipelineState) : m_pipelineState(pipelineState) {}

  // Get value for a reloc, if it is an internal LGC one
  bool getValue(llvm::StringRef name, uint64_t &value);

private:
  PipelineState *getPipelineState() const { return m_pipelineState; }

  PipelineState *m_pipelineState;
};

} // namespace lgc
