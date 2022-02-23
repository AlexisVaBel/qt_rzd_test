#pragma once

#include "gmock/gmock.h"
#include <client/ui/controller/IController.h>

namespace ui::test {
using namespace ui::controller;

class MockController : public IController {
public:
	MOCK_METHOD0(startProcess, void());
	MOCK_METHOD0(finishProcess, void());
};
} // namespace ui::test
