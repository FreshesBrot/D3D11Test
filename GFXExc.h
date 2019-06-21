#pragma once
#include "CustomException.h"
#include "dxerr.h"
#include <sstream>

#define GFX_FAILED(hrcall) if (FAILED(hr=(hrcall))) throw GraphicsException(__LINE__,__FILE__,hr)
#define GFX_DEVICE_REMOVED(hrcall) if (FAILED(hr=(hrcall))) throw DeviceRemovedException(__LINE__,__FILE__,hr)


	//this class represents a D3D11 graphics exception
	class GraphicsException : public CustomException {

		using CustomException::CustomException;
	public:
		GraphicsException(int line, const char* file, HRESULT hr);

		const char* what() const noexcept override;
		const char* getType() const noexcept override;
		const char* Translate(HRESULT hr) const noexcept override;

	};


	//this class represents the special case of device removed exceptions
	class DeviceRemovedException : public GraphicsException {
	public:
		DeviceRemovedException(int line, const char* file, HRESULT hr);
		const char* getType() const noexcept override;
	};



