#include "GFXExc.h"


GraphicsException::GraphicsException(int line, const char* file, HRESULT hr) {
	iLine = line; iFile = file; errorCode = hr;
}

const char* GraphicsException::what() const noexcept {
	std::ostringstream oss;
	oss << "[CODE]: " << (int)errorCode << "\n" <<
		"[LINE]: " << iLine << "\n" <<
		"[FILE]: " << iFile << "\n" <<
		Translate(errorCode);
	msgBuffer = oss.str();
	return msgBuffer.c_str();
}

const char* GraphicsException::getType() const noexcept {
	return "GRAPHICS EXCEPTION";
}

DeviceRemovedException::DeviceRemovedException(int line, const char* file, HRESULT hr) {
	iLine = line; iFile = file; errorCode = hr;
}

const char* DeviceRemovedException::getType() const noexcept {
	return "DEVICE REMOVED EXCEPTION";
}

const char* GraphicsException::Translate(HRESULT hr) const noexcept {
	char buffer[512];
	DXGetErrorDescription(hr, buffer, sizeof(buffer));
	std::ostringstream oss;
	oss << "[ERROR] " << DXGetErrorString(hr) << "\n[DESCRIPTION] " << buffer;
	codeBuffer = oss.str();
	return codeBuffer.c_str();
}
