#pragma once

namespace ui::controller {
class IController {
public:
	virtual ~IController(){

	};

	virtual void startProcess() = 0;
	virtual void finishProcess() = 0;
};
} // namespace ui::controller
