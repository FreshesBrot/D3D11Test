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
	void UpdateGeometry();
	void UpdateTransformBuffer();
	void UpdateBuffer(int position);

	//this will add a bindable object and bind it to the pipeline (mainly buffers only)
	void addBind(Bindable* b);

private:
	
	//the list of all bindables
	//first five are allways in the same order:
	//0: VertexShader - 1: PixelShader - 2: VertexBuffer 3: IndexBuffer - 4: MatrixBuffer  
	std::vector<Bindable*> bindables;

};

