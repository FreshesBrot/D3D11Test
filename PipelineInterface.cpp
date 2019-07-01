#include "PipelineInterface.h"

PipelineInterface::PipelineInterface() : bindables(){
	
	//push back all required bindables in set order
	bindables.reserve(4);
	bindables.push_back(new VertexBuffer(std::vector<Vertex>()));
	bindables.push_back(new IndexBuffer(std::vector<int>()));
	bindables.push_back(new MatrixBuffer());
	bindables.push_back(new ShaderStateController());


}

PipelineInterface::~PipelineInterface() {
	for (int i = 0; i < bindables.size(); i++)
		delete bindables[i];
}

void PipelineInterface::BindComponents() {
	for (Bindable* bind : bindables)
		bind->Bind();
}

void
PipelineInterface::UpdateGeometry() {
	int i = 0;
	bindables[i++]->Update();
	bindables[i]->Update();
}

void PipelineInterface::UpdateTransformBuffer() {
	bindables[2]->Update();
}

void PipelineInterface::UpdateShaderState() {
	bindables[3]->Update();
}

void PipelineInterface::UpdateBuffer(int position) {
	if (position < 5) position = 5;
	bindables[position]->Update();
}

int PipelineInterface::addVertexShader(const wchar_t* fileName) {
	return static_cast<ShaderStateController*>(bindables[3])->addVSFile(fileName);
}

int PipelineInterface::addPixelShader(const wchar_t* fileName) {
	return static_cast<ShaderStateController*>(bindables[3])->addPSFile(fileName);
}

int PipelineInterface::addTexture(const wchar_t* fileName) {
	return static_cast<ShaderStateController*>(bindables[3])->addTextureFile(fileName);
}

void PipelineInterface::addBind(Bindable* b) {
	bindables.push_back(b);
	b->Bind();
}

