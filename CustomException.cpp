#include "CustomException.h"
#include <sstream>

CustomException::CustomException(int line, const char* file, HRESULT hr) {
	iLine = line;
	iFile = file;
	errorCode = hr;
}

CustomException::CustomException() : iLine(),iFile(),errorCode() {}

const char* CustomException::what() const noexcept {
	std::ostringstream oss;
	oss << "[CODE]: " << errorCode << "\n" <<
		"[LINE]: " << iLine << "\n" <<
		"[FILE]: " << iFile << "\n" <<
		"[ERROR]: " << Translate(errorCode);
	msgBuffer = oss.str();
	return msgBuffer.c_str();
}

const char* CustomException::getType() const noexcept
{
	return "CUSTOM EXCEPTION OCCURED";
}

const char* CustomException::Translate(HRESULT hr) const noexcept{
	char* pMsgBuffer = nullptr;
	hr = 5;
	DWORD msgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, LANG_ENGLISH, reinterpret_cast<LPSTR>(&pMsgBuffer), 0, nullptr);
	if (msgLen == 0)
		return "Unknown Errorcode";
	codeBuffer = pMsgBuffer;
	//LocalFree(pMsgBuffer);
	return codeBuffer.c_str();
}


