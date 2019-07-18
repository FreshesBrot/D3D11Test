#include "MeshFile.h"

MeshFile::MeshFile(const wchar_t* fileName) : FileReader::FileReader(fileName) {
	VSfileName = nullptr;
	PSfileName = nullptr;
	TXfileName = nullptr;
	
	ProcessFile();
}

MeshFile::~MeshFile() { }

std::vector<int> MeshFile::getIndices() {
	return indices;
}

std::vector<Vertex> MeshFile::getVertices() {
	return vertices;
}

const wchar_t* MeshFile::getTXfileName() {
	return TXfileName;
}

const wchar_t* MeshFile::getVSfileName() {
	return VSfileName;
}

const wchar_t* MeshFile::getPSfileName() {
	return PSfileName;
}

void MeshFile::ProcessFile() {
	//open the file
	Read();
	
	std::string newLine;
	//keep track which line throws the error
	//capture the returned string and check if it is END_OF_FILE
	while ((newLine = nextLine()).compare(END_OF_FILE) != 0) {
		std::istringstream iss(newLine);
		//skip if the line begins with # (comment)
		char c0 = iss.peek();
		if (c0 == COMMENT || c0 == EMPTY) continue;
		//switch that determines the formatting of the line
		switch (val(newLine)) {
		case VERTEX:
			//iterate through block
			//capture the returned string and check if it is END_OF_BLOCK
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				std::istringstream iss(newLine);
				//check for comment or empty line
				char c = iss.peek();
				if (c == COMMENT || c == EMPTY) continue;
				
				
				float x, y, z, r, g, b, xn, yn, zn, u, v;
				//extract the information
				//if information is incorrect, throw READ_EXC
				if (!(iss >> x >> y >> z >> r >> g >> b >> xn >> yn >> zn >> u >> v)) 
					throw READ_EXC(error("The Formatting of the Vertex Structure is incorrect."));
				
				//construct vertex
				Vertex vrt = { x, y, z, r, g, b, xn, yn, zn, u, v };
				//insert into vertex vector
				vertices.push_back(vrt);
			}
			//if there are not at least 3 vertices after the read, throw exception
			if (vertices.size() < 3)
				throw READ_EXC(error("Cannot construct Mesh with less than 3 Vertices"));
			
			break;
		case FACE:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				std::istringstream iss(newLine);
				char c = iss.peek();
				if (c == COMMENT || c == EMPTY) continue;
				
				//check if at least 5 characters
				if (newLine.length() < 5) 
					throw READ_EXC(error("One or more Faces are incorrectly specified. Minimum Number of Vertices: 3."));
				
				int ind;
				std::vector<int> curInd;
				//returns true while iss can extract
				while (iss >> ind) {
					if (!(ind < vertices.size()))
						throw READ_EXC(error("An Index reffered to a Vertex that is out of Range."));
					curInd.push_back(ind);
				}
				//tesselate in case indices for one face are greater that three
				curInd = tesselate(curInd);
				//add indices to total indices
				indices.insert(indices.end(), curInd.begin(), curInd.end());
			}
			break;
		case VS:
			//check next line for specified name and convert it to wchar
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				char c = iss.peek();
				if (c == COMMENT || c == EMPTY) continue;
				VSfileName = toWString(newLine);
			}
			break;
		case PS:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				char c = iss.peek();
				if (c == COMMENT || c == EMPTY) continue; 
				PSfileName = toWString(newLine);
			}
			break;
		case TX:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				char c = iss.peek();
				if (c == COMMENT || c == EMPTY) continue; 
				TXfileName = toWString(newLine);
			}
			break;
		case MATERIAL:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				char c = iss.peek();
				if (c == COMMENT || c == EMPTY) continue;
			}
			break;
		default: 	
			std::ostringstream oss;
			oss << "Unexpected Block Identifier: " << newLine;
			std::string msg = oss.str();
			throw READ_EXC(error(msg.c_str()));
		}
	}
}

std::vector<int> MeshFile::tesselate(std::vector<int> indices) {
	if (indices.size() == 3) return indices;
	//new index vector
	std::vector<int> newInd;
	int maxIt = indices.size() - 1;
	//simple tesselation (only works for convex shapes)
	for (int i = 1; i < maxIt; i++) {
		newInd.push_back(0);
		newInd.push_back(indices[i]);
		newInd.push_back(indices[i + 1]);
	}
	return newInd;
}

int MeshFile::val(std::string s) {
	std::string::iterator it;
	int sum = 0;
	for (it = s.begin(); it < s.end(); it++) {
		sum += (char) *it;
	}
	return sum;
}

std::string MeshFile::error(const char* msg) {
	std::ostringstream oss;
	oss << msg << "\n[Line]: " << line << "\n[File]: " << file;
	std::string newmsg = oss.str();
	return newmsg;
}

