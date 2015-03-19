#include "OBJWrapper.h"

OBJWrapper::OBJWrapper(JNIEnv* jenv, jobject jcontext, File& file) : Drawable(NULL)
{
	std::vector<float> vertexPosition;
	std::vector<float> vertexNormal;
	std::vector<int>   vertexDrawOrder;
	std::vector<int>   vertexNormalOrder;

	std::map<std::string, int> materialSerie;

	int faceSerie = 0;

	std::string currentMaterial;
	bool currentMaterialInit = false;

	OBJDatas* currentDatas = NULL;

	while(true)
	{
		char* buffer = file.readLine();
		std::string line;

		if(buffer != NULL)
		{
			line = std::string(buffer);
			unsigned int loc;
			
			while((loc = line.find("  ")) != std::string::npos) //Two spaces here
				line.replace(loc,2," "); //Single space in quotes
			if(std::regex_match(line, std::regex("^ *#$")))
				free(buffer);
			continue;
		}

		if(buffer == NULL || std::regex_match(line, std::regex("^o ")))
		{
			if(currentDatas)
			{
  				currentDatas->vertexPositionLength = COORDS_PER_VERTEX * vertexDrawOrder.size();
			    currentDatas->vertexNormalLength   = COORDS_PER_VERTEX * vertexNormalOrder.size();
				//fill datas
				float* vertexPositionArray = (float*) malloc(sizeof(float) * currentDatas->vertexPositionLength);
				float* vertexNormalArray   = (float*) malloc(sizeof(float) * currentDatas->vertexNormalLength);

				for(unsigned int i=0; i < vertexDrawOrder.size(); i++)
				{
					int offset = vertexDrawOrder[i] * COORDS_PER_VERTEX;
					for(int j=0; j < COORDS_PER_VERTEX; j++)
						vertexPositionArray[COORDS_PER_VERTEX*i + j] = vertexPosition[offset + j];
				}

				for(unsigned int i=0; i < vertexNormalOrder.size(); i++)
				{
					int offset = vertexNormalOrder[i] * COORDS_PER_VERTEX;
					for(int j=0; j < COORDS_PER_VERTEX; j++)
						vertexNormalArray[COORDS_PER_VERTEX*i + j] = vertexNormal[offset + j];
				}

				//create and fill VBO
				glGenBuffers(1, &(currentDatas->vboID));
				glBindBuffer(GL_ARRAY_BUFFER, currentDatas->vboID);
				{
					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (currentDatas->vertexPositionLength + currentDatas->vertexNormalLength), NULL, GL_DYNAMIC_DRAW);
					glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * currentDatas->vertexPositionLength, vertexPositionArray);
					glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * currentDatas->vertexPositionLength, sizeof(float) * currentDatas->vertexNormalLength, vertexNormalArray);
				}
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				//say how many faces per materials
				if(currentMaterialInit)
				{
					materialSerie.insert(std::make_pair(currentMaterial, faceSerie*COORDS_PER_VERTEX)); //because 3 vertex per faces
					currentDatas->materialSerie = materialSerie;
				}
			}

			if(buffer == NULL)
				break;

			//reinit the vertex
			{
				vertexDrawOrder          = std::vector<int>();
				vertexNormalOrder        = std::vector<int>();
				materialSerie            = std::map<std::string, int>();
				faceSerie                = 0;
				currentMaterialInit      = false;

				std::string name         = split(line, ' ')[1];
				OBJDatas* currentDatas   = new OBJDatas();
				currentDatas->mtlWrapper = NULL;
				m_objDatas.add(name, currentDatas);
			}
		}

		//Init the material file
		else if(std::regex_match(line, std::regex("^mtllib ")))
		{
			std::vector<std::string> pathSplited = split(file.getPath(), '/');
			std::string path="";
			for(unsigned int i=0; i < pathSplited.size()-1; i++)
				path                += pathSplited[i];
			std::string mtlName      = split(line, ' ')[1];
			path                    += mtlName;

			File f(jenv, jcontext, path.c_str(), "r");
			currentDatas->mtlWrapper = new MaterialWrapper(f);
			m_mtlWrapper.add(mtlName, currentDatas->mtlWrapper);
		}

		else if(std::regex_match(line, std::regex("^usemtl ")))
		{
			if(currentMaterialInit)
				materialSerie.insert(std::make_pair(currentMaterial, faceSerie*COORDS_PER_VERTEX));
			currentMaterialInit = true;
			currentMaterial     = split(line, ' ')[1];
			faceSerie          = 0;
		}

		else if(std::regex_match(line, std::regex("^v ")))
		{
			std::vector<std::string> pointValues = split(line, ' ');
			for(unsigned int i=1; i < pointValues.size(); i++)
				vertexPosition.push_back(atoi(pointValues[i].c_str()));
		}

		else if(std::regex_match(line, std::regex("^vn ")))
		{
			std::vector<std::string> pointValues = split(line, ' ');
			for(unsigned int i=1; i < pointValues.size(); i++)
				vertexNormal.push_back(atoi(pointValues[i].c_str()));
		}	

		else if(std::regex_match(line, std::regex("^f ")))
		{
			std::vector<std::string> faceValue = split(line, ' ');
			for(unsigned int i=0; i < faceValue.size(); i++)
			{
				std::vector<std::string> orderValue = split(faceValue[i], '/');
				for(unsigned int j=0; j < orderValue.size(); j++)
				{
					if(orderValue[j] == "")
						continue;
					if(j==0)
						vertexDrawOrder.push_back(atoi(orderValue[j].c_str()));
					else if(j==2)
						vertexNormalOrder.push_back(atoi(orderValue[j].c_str()));
				}
			}
		}

		if(buffer != NULL)
			free(buffer);
	}
}

void OBJWrapper::onDraw(Renderer* renderer, glm::mat4& mvp)
{
	glm::mat4 inverseMVP = glm::inverse(mvp);
	for(std::map<std::string, OBJDatas*>::iterator itOBJ = m_objDatas.begin(); itOBJ != m_objDatas.end(); ++itOBJ)
	{
		OBJDatas* currentDatas = itOBJ->second;
		glBindBuffer(GL_ARRAY_BUFFER, currentDatas->vboID);
		{
			for(std::map<std::string, int>::iterator itSeries = currentDatas->materialSerie.begin(); itSeries != currentDatas->materialSerie.end(); itSeries++)
			{
				//Draw triangle for each materials series.
				int offset = 0;
				//Get the material and the shader, then init them.
				Material* currentMaterial = currentDatas->mtlWrapper->getMaterial(itSeries->first);
				const Shader* shader;
				if(!m_material)
				{
					currentMaterial->enableShader();
					currentMaterial->init(renderer);
					shader = currentMaterial->getShader();
				}
				else
				{
					m_material->init(renderer);
					shader = m_material->getShader();
				}

				//Send the vector attribute
				int stride = 12;
				glVertexAttribPointer(glGetAttribLocation(shader->getProgramID(), "vPosition"), 3, GL_FLOAT, false, stride, BUFFER_OFFSET(0));
				glVertexAttribPointer(glGetAttribLocation(shader->getProgramID(), "vNormal"), 3, GL_FLOAT, false, stride, BUFFER_OFFSET(currentDatas->vertexPositionLength*4));

				//Send the uniform attribute
				GLint mvpMatrixHandle = glGetUniformLocation(shader->getProgramID(), "uMVP");
				glUniformMatrix4fv(mvpMatrixHandle, 1, false, glm::value_ptr(mvp));

				GLint inverseMVPMatrixHandle = glGetUniformLocation(shader->getProgramID(), "uInverseMVP");
				if(inverseMVPMatrixHandle != -1)
					glUniformMatrix4fv(inverseMVPMatrixHandle, 1, false, glm::value_ptr(inverseMVP));

				//Draw the triangles.
				glDrawArrays(GL_TRIANGLES, offset, itSeries->second);
				offset += itSeries->second;
			}
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

OBJWrapper::~OBJWrapper()
{

}
