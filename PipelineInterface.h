#pragma once
#include "Graphics.h"
#include "ShaderStateController.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "PSConstBuffer.h"
#include "VSConstBuffer.h"
#include "Object.h"


//this class represents the interface between the graphics interface and the binable objects
class PipelineInterface {
public:

	//sets up the pipeline
	PipelineInterface();
	~PipelineInterface();

	//these will bind the first components to the graphics pipeline
	void BindComponents();

	//these will update the bindable components 
	//updates the geometry data for vertex and index buffer
	void UpdateGeometry();
	//updates the world view transform buffer
	void UpdateTransformBuffer();
	//intializes default values for the SSC
	void initDefault();
	//updates the SSC
	void UpdateShaderState();
	//updates the component buffers
	void UpdateComponentBuffers(Object* obj);


	//adds file resources to the SSC
	int addVertexShader(const wchar_t* fileName);
	int addPixelShader(const wchar_t* fileName);
	int addTexture(const wchar_t* fileName);


private:
	
	//the vector of essential bindables
	//first four are allways in the same order:
	//0: VertexBuffer - 1: IndexBuffer - 2: MatrixBuffer - 3: SSC
	std::vector<Bindable*> bindables;

	//vector of component buffers
	std::vector<ConstBuffer*> componentBuffers;

	//a buffer that holds light information

};

