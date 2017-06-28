#include "Level.h"

/*
Losa 64x64
http://docs.unity3d.com/Manual/SL-VertexFragmentShaderExamples.html

Create LookAt-2D:
http://www.learnopengles.com/android-lesson-one-getting-started/

Create Ortho-2D:
http://stackoverflow.com/questions/2847574/opengl-es-2-0-equivalent-of-glortho
http://www.opengl.org/discussion_boards/showthread.php/172280-Constructing-an-orthographic-matrix-for-2D-drawing
http://stackoverflow.com/questions/18012226/android-gl-es-2-0-ortho-matrices
http://www.gamedev.net/topic/634155-problems-with-glmortho/

http://duriansoftware.com/joe/An-intro-to-modern-OpenGL.-Chapter-3:-3D-transformation-and-projection.html
http://3dgep.com/understanding-the-view-matrix/
*/

void Level::createMap(){

    this->sizeX = 768;
    this->sizeY = 1024;

    this->idImage = this->global->getImageId("MAP_1");

    DEBUGLOGPONE("Level::createMap() - Id Image [%d] MAP_1",this->idImage);

    if (this->idImage == 0){
        ERRORLOG("Level::createMap() - Id Image no válido");

        this->idImage = 3;
        this->idPlayer = 4;
        this->idText = 5;

        DEBUGLOGPONE("Level::createMap() - Id Image [%d] MAP_1",this->idImage);
    }

    /*
    map ={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };*/


    /*
    this->map_1_x = new float*[this->sizeX];
    for (int i = 0; i< this->sizeX; i++){
        this->map_1_x[i] = new float[this->sizeY];
    }


	this->map_1_y = new float*[this->sizeX];
    for (int i = 0; i< this->sizeX; i++){
        this->map_1_y[i] = new float[this->sizeY];
    }
    */
}

void Level::destroyMap(){


    /*
    for (int i = 0; i < 32; ++i){
        delete [] map[i];
    }

    delete [] map;*/

     /*
     for (int i = 0; i < this->sizeX; ++i){
        delete [] map_1_x[i];
        delete [] map_1_y[i];
     }

     delete [] map_1_x;
     delete [] map_1_y;
     */
    /*
    char spaceStationAlpha[8][8] =
    {
        {0,0,0,0,0,0,0,0},
        {0,2,1,0,0,2,2,0},
        {0,0,1,1,1,2,2,0},
        {0,0,1,0,0,1,1,0},
        {0,0,1,0,0,1,1,0},
        {0,0,1,0,0,1,1,0},
        {0,2,1,1,1,1,1,0},
        {0,0,0,0,0,0,0,0}
    };*/


}

int Level::writeText(const char*text, float x, float y, float size){


    unsigned int length = strlen(text);

    /*length caracteres * 6 vertices x cada caracter * 6 elementos cada vertice */
    int sizebuffer = length*6;


    GLfloat afText[sizebuffer* 36];

    int inc_data = 0;


    float tile_x = 6.0;
    float tile_y = 6.0;

    /*

    0.015625
    (1,4) (2,4)
    (1,5) (2,5)
    */



    for(int i=0; i<length; i++){

            tile_x = 6.0+(i * 0.5f);

         //1-vertice
            afText[inc_data     ] =  tile_x   * 32.0f;
            afText[inc_data +  1] = (tile_y+1)* 32.0f;
            afText[inc_data +  2] = 0.0;
            afText[inc_data +  3] = 1.0;
            afText[inc_data +  4] = 2.0f * 0.0625f; //1.0f * 0.0625f; //0.2
            afText[inc_data +  5] = 5.0f * 0.0625f;//4.0f * 0.0625f; //0.9

            //2-vertices
            afText[inc_data +  6] = (tile_x+1)* 32.0f;
            afText[inc_data +  7] = (tile_y+1)* 32.0f;
            afText[inc_data +  8] = 0.0;
            afText[inc_data +  9] = 1.0;
            afText[inc_data + 10] = 1.0f * 0.0625f; //2.0f * 0.0625f; //0.3
            afText[inc_data + 11] = 5.0f * 0.0625f; //4.0f * 0.0625f; //0.9

            //3-vertices
            afText[inc_data + 12] = (tile_x) * 32.0f;
            afText[inc_data + 13] = (tile_y) * 32.0f;
            afText[inc_data + 14] = 0.0;
            afText[inc_data + 15] = 1.0;
            afText[inc_data + 16] = 2.0f * 0.0625f; //1.0f * 0.0625f; //0.2
            afText[inc_data + 17] = 4.0f * 0.0625f; //5.0f * 0.0625f; //1.0

            //4-vertices
            afText[inc_data + 18] = (tile_x+1) * 32.0f;
            afText[inc_data + 19] = (tile_y)   * 32.0f;
            afText[inc_data + 20] = 0.0;
            afText[inc_data + 21] = 1.0;
            afText[inc_data + 22] = 1.0f * 0.0625f; //2.0f * 0.0625f; //0.3
            afText[inc_data + 23] = 4.0f * 0.0625f; //5.0f * 0.0625f; //1.0

            //5-vertices
            afText[inc_data + 24] = (tile_x)   * 32.0f;
            afText[inc_data + 25] = (tile_y)   * 32.0f;
            afText[inc_data + 26] = 0.0;
            afText[inc_data + 27] = 1.0;
            afText[inc_data + 28] = 2.0f * 0.0625f; //1.0f * 0.0625f; //0.2
            afText[inc_data + 29] = 4.0f * 0.0625f; //5.0f * 0.0625f; //1.0

            //6-vertices
            afText[inc_data + 30] = (tile_x+1) * 32.0f;
            afText[inc_data + 31] = (tile_y+1) * 32.0f;
            afText[inc_data + 32] = 0.0;
            afText[inc_data + 33] = 1.0;
            afText[inc_data + 34] = 1.0f * 0.0625f; //2.0f * 0.0625f; //0.3
            afText[inc_data + 35] = 5.0f * 0.0625f; //4.0f * 0.0625f; //0.9






        /*
        char character = text[i];
		float uv_x = (character%16)/16.0f;
		float uv_y = (character/16)/16.0f;

        //1-vertice
        afText[inc_data     ] = x+i*size;
        afText[inc_data +  1] = y+size;
        afText[inc_data +  2] = 0.0;
        afText[inc_data +  3] = 1.0;
        afText[inc_data +  4] = uv_x;
        afText[inc_data +  5] = uv_y;

        //2-vertices
        afText[inc_data +  6] = x+i*size;
        afText[inc_data +  7] = y;
        afText[inc_data +  8] = 0.0;
        afText[inc_data +  9] = 1.0;
        afText[inc_data + 10] = uv_x;
        afText[inc_data + 11] = (uv_y + 1.0f/16.0f);

        //3-vertices
        afText[inc_data + 12] = x+i*size+size;
        afText[inc_data + 13] = y+size;
        afText[inc_data + 14] = 0.0;
        afText[inc_data + 15] = 1.0;
        afText[inc_data + 16] = uv_x+1.0f/16.0f;
        afText[inc_data + 17] = uv_y;

        //4-vertices
        afText[inc_data + 18] = x+i*size+size;
        afText[inc_data + 19] = y;
        afText[inc_data + 20] = 0.0;
        afText[inc_data + 21] = 1.0;
        afText[inc_data + 22] = uv_x+1.0f/16.0f;
        afText[inc_data + 23] = (uv_y + 1.0f/16.0f);

        //5-vertices
        afText[inc_data + 24] = x+i*size+size;
        afText[inc_data + 25] = y+size;
        afText[inc_data + 26] = 0.0;
        afText[inc_data + 27] = 1.0;
        afText[inc_data + 28] = uv_x+1.0f/16.0f;
        afText[inc_data + 29] = uv_y;

        //6-vertices
        afText[inc_data + 30] = x+i*size;
        afText[inc_data + 31] = y;
        afText[inc_data + 32] = 0.0;
        afText[inc_data + 33] = 1.0;
        afText[inc_data + 34] = uv_x;
        afText[inc_data + 35] = (uv_y + 1.0f/16.0f);
        */

        inc_data+=36;
    }



    glGenBuffers(1, &m_ui32Vbo_2);
	m_ui32VertexStride = 6 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo_2);
	glBufferData(GL_ARRAY_BUFFER, sizebuffer  * m_ui32VertexStride, afText, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    return sizebuffer;

}


void Level::beginEngine(){


    DEBUGLOG("Level::beginEngine() - IN");

    gRenderManager->startUp("./data/shader/tilevertex.txt","./data/shader/tilefragment.txt");
    gRenderManager->setProgramObject(glCreateProgram());

    glAttachShader ( gRenderManager->getProgramObject(), gRenderManager->getVertexShaderId());
    glAttachShader ( gRenderManager->getProgramObject(), gRenderManager->getFragmentShaderId());

    glBindAttribLocation(gRenderManager->getProgramObject(), VERTEX_ARRAY, "myVertex");
    glBindAttribLocation(gRenderManager->getProgramObject(), TEXCOORD_ARRAY, "myUV");


    glLinkProgram ( gRenderManager->getProgramObject() );

    glGetProgramiv ( gRenderManager->getProgramObject(), GL_LINK_STATUS, &linked );

    if (!linked){


        GLint infoLen = 0;
        glGetProgramiv ( gRenderManager->getProgramObject(), GL_INFO_LOG_LENGTH, &infoLen );
        if ( infoLen > 1 )
        {
            char* infoLog = new char[infoLen];
            glGetProgramInfoLog ( gRenderManager->getProgramObject(), infoLen, NULL, infoLog );
            free ( infoLog );
        }

        glDeleteProgram ( gRenderManager->getProgramObject() );
        ERRORLOG("Level::beginEngine() ERROR AL PROCESAR LOS SHADERS");
        exit(1);
    }

    glUseProgram(gRenderManager->getProgramObject());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glViewport ( 0, 0, this->global->getScreenW(), this->global->getScreenH());

    uniformLocation = glGetUniformLocation(gRenderManager->getProgramObject(), "sampler2d");

    GLfloat afVertices[6912];

    int inc_data = 0;

    //TILES

    for(GLfloat tile_x=0.0; tile_x<12.0; tile_x+=1.0){
        for(GLfloat tile_y=0.0; tile_y<16.0; tile_y+=1.0){

            //1-vertice
            afVertices[inc_data     ] =  tile_x * 64.0f;
            afVertices[inc_data +  1] = (tile_y+1)*64.0f;
            afVertices[inc_data +  2] = 0.0;
            afVertices[inc_data +  3] = 1.0;
            afVertices[inc_data +  4] = 0.2;
            afVertices[inc_data +  5] = 0.9;

            //2-vertices
            afVertices[inc_data +  6] = (tile_x+1)* 64.0f;
            afVertices[inc_data +  7] = (tile_y+1)*64.0f;
            afVertices[inc_data +  8] = 0.0;
            afVertices[inc_data +  9] = 1.0;
            afVertices[inc_data + 10] = 0.3;
            afVertices[inc_data + 11] = 0.9;

            //3-vertices
            afVertices[inc_data + 12] = (tile_x)*64.0f;
            afVertices[inc_data + 13] = (tile_y)*64.0f;
            afVertices[inc_data + 14] = 0.0;
            afVertices[inc_data + 15] = 1.0;
            afVertices[inc_data + 16] = 0.2;
            afVertices[inc_data + 17] = 1.0;

            //4-vertices
            afVertices[inc_data + 18] = (tile_x+1)*64.0f;
            afVertices[inc_data + 19] = (tile_y)*64.0f;
            afVertices[inc_data + 20] = 0.0;
            afVertices[inc_data + 21] = 1.0;
            afVertices[inc_data + 22] = 0.3;
            afVertices[inc_data + 23] = 1.0;

            //5-vertices
            afVertices[inc_data + 24] = (tile_x)*64.0f;
            afVertices[inc_data + 25] = (tile_y)*64.0f;
            afVertices[inc_data + 26] = 0.0;
            afVertices[inc_data + 27] = 1.0;
            afVertices[inc_data + 28] = 0.2;
            afVertices[inc_data + 29] = 1.0;

            //6-vertices
            afVertices[inc_data + 30] = (tile_x+1)*64.0f;
            afVertices[inc_data + 31] = (tile_y+1)*64.0f;
            afVertices[inc_data + 32] = 0.0;
            afVertices[inc_data + 33] = 1.0;
            afVertices[inc_data + 34] = 0.3;
            afVertices[inc_data + 35] = 0.9;

            inc_data+=36;

        }

    }

    glGenBuffers(1, &m_ui32Vbo);
	m_ui32VertexStride = 6 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo);
	glBufferData(GL_ARRAY_BUFFER, 1152 * m_ui32VertexStride, afVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


    //JUGADOR

	GLfloat afPlayer[] = {
    //X      Y       Z   PRT    U       V
    //primer tile
    64.0,   128.0,  0.0,  1.0,  0.375,    0.0,
    128.0,  128.0,  0.0,  1.0,  0.5,    0.0,
    64.0,   64.0,  0.0,  1.0,  0.375,    1.0,

    128.0,  64.0,  0.0,  1.0,  0.5,    1.0,
    64.0,   64.0,  0.0,  1.0,  0.375,    1.0,
    128.0,  128.0,  0.0,  1.0,  0.5,    0.0
	};

    glGenBuffers(1, &m_ui32Vbo_1);
	m_ui32VertexStride = 6 * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo_1);
	glBufferData(GL_ARRAY_BUFFER, 6 * m_ui32VertexStride, afPlayer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


    num_vertex_text = writeText("XXXXXXX", 256, 256, 64);

	glEnable(GL_CULL_FACE);

	INFOLOG("Level::beginEngine() - OUT");
}


void Level::endEngine(){
    DEBUGLOG("Level::endEngine() - IN");
    DEBUGLOG("Level::endEngine() - OUT");
}


void Level::updateProcess(){
}


void Level::runProcess(){

    DEBUGLOG("Level::runProcess() - IN");

    glClear(GL_COLOR_BUFFER_BIT);

	//defino la matriz Ortho para ser aplicada a la pantalla (en un futuro, si funciona
    //esto se puede transportar al vertex shader)
    //vision ortho
    /**********************************************************************************/

    glm::mat4 Projection = glm::ortho<float>(
		0.0f,
		static_cast<float>(640),
		static_cast<float>(480),
		0.0f,
		1.0f,
		-1.0f
	);

	glm::mat4 view = glm::translate(glm::mat4(1.0f),glm::vec3( 0.0f, 0.0f, 0.0f));
	glm::mat4 Model = glm::mat4(1.0f);
	glm::mat4 MVP = Projection * view * Model;
	/**********************************************************************************/

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int i32Location = glGetUniformLocation(gRenderManager->getProgramObject(), "myPMVMatrix");
	glUniformMatrix4fv(i32Location, 1, GL_FALSE, glm::value_ptr(MVP));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,this->idImage);
    glUniform1i(uniformLocation, 0);

    //fondo
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 4, GL_FLOAT, GL_FALSE, m_ui32VertexStride, 0);

	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, m_ui32VertexStride, (void*) (4 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLES, 0, 1152);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,this->idPlayer);
    glUniform1i(uniformLocation, 1);

	//player
	glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo_1);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 4, GL_FLOAT, GL_FALSE, m_ui32VertexStride, 0);

	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, m_ui32VertexStride, (void*) (4 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,this->idText);
    glUniform1i(uniformLocation, 2);

    //text
    glBindBuffer(GL_ARRAY_BUFFER, m_ui32Vbo_2);

	glEnableVertexAttribArray(VERTEX_ARRAY);
	glVertexAttribPointer(VERTEX_ARRAY, 4, GL_FLOAT, GL_FALSE, m_ui32VertexStride, 0);

	glEnableVertexAttribArray(TEXCOORD_ARRAY);
	glVertexAttribPointer(TEXCOORD_ARRAY, 2, GL_FLOAT, GL_FALSE, m_ui32VertexStride, (void*) (4 * sizeof(GLfloat)));

    glDrawArrays(GL_TRIANGLES, 0, num_vertex_text);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    DEBUGLOG("Level::runProcess() - OUT");
}

