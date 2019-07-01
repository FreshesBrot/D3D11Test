#pragma once
#include "Graphics.h"
#include "ShaderStateController.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstBuffer.h"


//this class represents the interface between the graphics interface and the binable objects
class PipelineInterface {
public:

	//sets up the pipeline
	PipelineInterface();
	~PipelineInterface();

	//these will bind the components to the graphics pipeline
	void BindComponents();

	//these will update the bindable components 
	//updates the geometry data for vertex and index buffer
	void UpdateGeometry();
	//updates the world view transform buffer
	void UpdateTransformBuffer();
	//updates the SSC
	void UpdateShaderState();



	//updates any buffer 
	void UpdateBuffer(int position);


	//adds file resources to the SSC
	int addVertexShader(const wchar_t* fileName);
	int addPixelShader(const wchar_t* fileName);
	int addTexture(const wchar_t* fileName);

	//adds a bindable object and binds it to the pipeline (mainly buffers only)
	void addBind(Bindable* b);


private:
	
	//the list of all bindables
	//first four are allways in the same order:
	//0: VertexBuffer - 1: IndexBuffer - 2: MatrixBuffer - 3: SSC
	std::vector<Bindable*> bindables;

};

