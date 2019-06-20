#pragma once
#include "CustomException.h"
#include "dxerr.h"
#include <sstream>

	//graphics exception
	class GraphicsException : public CustomException {

		using CustomException::CustomException;
	public:
		GraphicsException(int line, const char* file, HRESULT hr);

		const char* what() const noexcept override;
		const char* getType() const noexcept override;
		const char* Translate(HRESULT hr) const noexcept override;

	};

	//special case exception
	class DeviceRemovedException : public GraphicsException {
	public:
		DeviceRemovedException(int line, const char* file, HRESULT hr);
		const char* getType() const noexcept override;
	};



