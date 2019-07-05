#include "PipelineInterface.h"

PipelineInterface::PipelineInterface() : bindables(){
	
	//push back all required bindables in set order
	bindables.reserve(4);
	bindables.push_back(new VertexBuffer(std::vector<Vertex>()));
	bindables.push_back(new IndexBuffer(std::vector<int>()));
	//bindables.push_back(new MatrixBuffer());
	bindables.push_back(new ShaderStateController());

	//reserve space for component buffers
	vsBuffers.reserve(4);
	vsBuffers.push_back(nullptr);
	vsBuffers.push_back(nullptr);
	psBuffers.reserve(4);
	psBuffers.push_back(nullptr);
	psBuffers.push_back(nullptr);
}

PipelineInterface::~PipelineInterface() {
	for (int i = 0; i < bindables.size(); i++)
		delete bindables[i];
	for (VSConstBuffer* vs : vsBuffers)
		delete vs;
	for (PSConstBuffer* ps : psBuffers)
		delete ps;
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


void PipelineInterface::initDefault() {
	static_cast<ShaderStateController*>(bindables[2])->initializeDefaults();
}

void PipelineInterface::UpdateShaderState() {
	bindables[2]->Update();
}

void PipelineInterface::CreateComponentBuffers(Object* obj) {
	//iterate through all components
	//if there is no buffer at the specified ID, create a new one
	//else return
	for (Component* comp : obj->getComponents()) {
		int ID = comp->RegID();
		switch (comp->shaderBind()) {
		case VS:
			if (vsBuffers[ID] != nullptr) return;
			vsBuffers[ID] = new VSConstBuffer();
			vsBuffers[ID]->CreateFromResource(comp);
			break;
		case PS:
			if (psBuffers[ID] != nullptr) return;
			psBuffers[ID] = new PSConstBuffer();
			psBuffers[ID]->CreateFromResource(comp);
			break;
		}
	}
}

void PipelineInterface::BindComponentBuffers() {
	for (VSConstBuffer* vs : vsBuffers)
		if (vs != nullptr) vs->Bind();
	for (PSConstBuffer* ps : psBuffers)
		if (ps != nullptr) ps->Bind();
}

void PipelineInterface::UpdateComponentBuffers(Object* obj) {
	for (Component* comp : obj->getComponents()) {
		switch (comp->shaderBind()) {
		case VS:
			vsBuffers[comp->RegID()]->UpdateFromResource(comp);
			break;
		case PS:
			psBuffers[comp->RegID()]->UpdateFromResource(comp);
			break;
		}
	}
}

int PipelineInterface::addVertexShader(const wchar_t* fileName) {
	return static_cast<ShaderStateController*>(bindables[2])->addVSFile(fileName);
}

int PipelineInterface::addPixelShader(const wchar_t* fileName) {
	return static_cast<ShaderStateController*>(bindables[2])->addPSFile(fileName);
}

int PipelineInterface::addTexture(const wchar_t* fileName) {
	return static_cast<ShaderStateController*>(bindables[2])->addTextureFile(fileName);
}

