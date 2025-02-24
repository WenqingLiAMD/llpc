/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
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

#include "llpc.h"
#include "llpcComputeContext.h"
#include "llpcContext.h"
#include "llpcGraphicsContext.h"
#include "llpcUtil.h"
#include "lgc/CommonDefs.h"
#include "lgc/LgcContext.h"
#include "gmock/gmock.h"

using namespace lgc;
using namespace llvm;
using namespace llvm::CodeGenOpt;

namespace Llpc {
namespace {

constexpr GfxIpVersion GfxIp = {9, 0, 0};

// cppcheck-suppress syntaxError
TEST(LlpcContextTests, MatchPipelineOptLevel) {
  MetroHash::Hash cacheHash = {};
  MetroHash::Hash pipelineHash = {};

  LgcContext::initialize();

  Context *context = new Context(GfxIp);

  for (auto optLevel : {Level::None, Level::Less, Level::Default, Level::Aggressive}) {
    GraphicsPipelineBuildInfo pipelineInfo = {};
    pipelineInfo.options.optimizationLevel = optLevel;

    GraphicsContext graphicsContext(GfxIp, &pipelineInfo, &pipelineHash, &cacheHash);

    context->attachPipelineContext(&graphicsContext);

    if (optLevel == Level::None) {
      // None might not be possible, so accept >= Level::None
      EXPECT_GE(context->getLgcContext()->getOptimizationLevel(), optLevel);
    } else {
      EXPECT_EQ(context->getLgcContext()->getOptimizationLevel(), optLevel);
    }
  }

  for (auto optLevel : {Level::None, Level::Less, Level::Default, Level::Aggressive}) {
    ComputePipelineBuildInfo pipelineInfo = {};
    pipelineInfo.options.optimizationLevel = optLevel;

    ComputeContext computeContext(GfxIp, &pipelineInfo, &pipelineHash, &cacheHash);

    context->attachPipelineContext(&computeContext);

    if (optLevel == Level::None) {
      // None might not be possible, so accept >= Level::None
      EXPECT_GE(context->getLgcContext()->getOptimizationLevel(), optLevel);
    } else {
      EXPECT_EQ(context->getLgcContext()->getOptimizationLevel(), optLevel);
    }
  }
}

} // namespace
} // namespace Llpc
