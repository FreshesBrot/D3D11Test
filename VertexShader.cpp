#include "VertexShader.h"


VertexShader::~VertexShader() {
	pVshader = nullptr;
	pVshaderBlob = nullptr;
}

void VertexShader::Bind() {
	if (PSset) return;
	
}

void VertexShader::Update() {

}
