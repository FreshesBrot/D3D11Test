#include "PipelineInterface.h"

PipelineInterface::PipelineInterface() : bindables(){
	
	//push back all required bindables in set order
	bindables.reserve(4);
	bindables.push_back(new VertexBuffer(std::vector<Vertex>()));
	bindables.push_back(new IndexBuffer(std::vector<int>()));
	bindables.push_back(new MatrixBuffer());
	bindables.push_back(new ShaderStateController());
	bindables.push_back(new TextureController());

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

void PipelineInterface::UpdateShader() {
	bindables[3]->Update();
}

void PipelineInterface::UpdateTexture() {
	bindables[4]->Update();
}

void PipelineInterface::UpdateBuffer(int position) {
	if (position < 5) position = 5;
	bindables[position]->Update();
}

void PipelineInterface::addBind(Bindable* b) {
	bindables.push_back(b);
	b->Bind();
}

int PipelineInterface::addShader(const wchar_t* VSfileName, const wchar_t* PSfileName) {
	return static_cast<ShaderStateController*>(bindables[3])->
		addShaderFile(VSfileName, PSfileName);
}

int PipelineInterface::addTexture(const wchar_t* fileName) {
	return static_cast<TextureController*>(bindables[4])->addTextureFile(fileName);
}
