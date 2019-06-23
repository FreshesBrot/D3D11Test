#include "PipelineInterface.h"

PipelineInterface::PipelineInterface() : bindables(){
	
	//push back all required bindables in set order
	bindables.reserve(5);
	bindables.push_back(new VertexShader(L"VertexShader.cso"));
	bindables.push_back(new PixelShader(L"PixelShader.cso"));
	bindables.push_back(new VertexBuffer(std::vector<Vertex>()));
	bindables.push_back(new IndexBuffer(std::vector<int>()));
	bindables.push_back(new MatrixBuffer());

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
	int i = 2;
	bindables[i++]->Update();
	bindables[i]->Update();
}

void PipelineInterface::UpdateTransformBuffer() {
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
