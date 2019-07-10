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
	int line = 0;
	//capture the returned string and check if it is END_OF_FILE
	while ((newLine = nextLine()).compare(END_OF_FILE) != 0) {
		line++;
		std::istringstream iss(newLine);
		//skip if the line begins with # (comment)
		if (iss.peek() == COMMENT) continue;
		//switch that determines the formatting of the line
		switch (val(newLine)) {
		case VERTEX:
			//iterate through block
			//capture the returned string and check if it is END_OF_BLOCK
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				line++;
				float x, y, z, r, g, b, xn, yn, zn, u, v;
				//extract the information
				//if information is incorrect, throw READ_EXC
				if (!(iss >> x >> y >> z >> r >> g >> b >> xn >> yn >> zn >> u >> v)) {
					std::ostringstream oss;
					oss << "The Formatting of the Vertex Structure is incorrect.\nLine: " << line << "\nFile: "<< file;
					std::string msg = oss.str();
					throw READ_EXC(msg);
				}
				//construct vertex
				Vertex vrt = { x, y, z, r, g, b, xn, yn, zn, u, v };
				//insert into vertex vector
				vertices.push_back(vrt);
			}
			break;
		case FACE:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				line++;
				//check if at least 5 characters
				if (newLine.length() < 5) {
					std::ostringstream oss;
					oss << "One or more Faces are incorrectly specified. Minimum Number of Vertices: 3 .\nLine: " << line << "\nFile: " << file.c_str();
					std::string msg = oss.str();
					throw READ_EXC(msg);
				}
				int ind;
				std::vector<int> curInd;
				//returns true while iss can extract
				while (iss >> ind) {
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
				line++;
				std::wstringstream wss;
				wss << newLine.c_str();
				std::wstring ws = wss.str();
				VSfileName = ws.c_str();
			}
			break;
		case PS:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				line++;
				std::wstringstream wss;
				wss << newLine.c_str();
				std::wstring ws = wss.str();
				PSfileName = ws.c_str();
			}
			break;
		case TX:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				line++;
				std::wstringstream wss;
				wss << newLine.c_str();
				std::wstring ws = wss.str();
				TXfileName = ws.c_str();
			}
			break;
		case MATERIAL:
			while ((newLine = nextLine()).compare(END_OF_BLOCK) != 0) {
				line++;
			}
			break;
		default: 	
			std::ostringstream oss;
			oss << "Unexpected Block Identifier: " << newLine << ".\nLine: " << line << "\nFile: " << file.c_str();
			std::string msg = oss.str();
			throw READ_EXC(msg);
		}
	}
}

std::vector<int> MeshFile::tesselate(std::vector<int> indices) {
	if (indices.size() <= 3) return indices;
	//new index vector
	std::vector<int> newInd;
	int maxIt = indices.size() - 1;
	//simple tesselation (only works for convex shapes)
	for (int i = 1; i < maxIt; i++) {
		newInd.push_back(0);
		newInd.push_back(i);
		newInd.push_back(i + 1);
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
