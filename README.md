# D3D11Test
A DirectX 3D 11 Exercie Project that implements an extensible graphics pipeline and objects with an object component system. This is my first C++ project.

**Working period: 06/19-08/19**

### Features
 - Graphics engine that can render multiple objects with different properties (e.g. material, shader, texture, etc)
 - Extensible graphics pipeline that can deliver numerous objects, shaders and textures to the graphics card
 - High abstraction through self-designed API framework
 - extensible object component system that lets an object manage several attributes (i.e. a transform or a texture) 
 - A self designed (but inefficient) object file format (.sof) - with file readers and writers - to read custom meshes from and load them into the pipeline, along with a defined texture and shader and material properties

### Ideas for improvement
 - The TerrainGenerator that works, but saving the data and reading it again does not quite work
 - Generally improving the .sof file format, moving from a string based file to a binary based file to store vertices and indices as well as other things that can be saved with an object
 - Idea to create a scene tree graph that propagates transforms from the parent nodes down to the child nodes
 
 **!This project has not been maintained in over a year, so I'm not sure if this would still compile and/or work!**
