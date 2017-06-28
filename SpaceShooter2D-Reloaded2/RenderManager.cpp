#include "RenderManager.h"


std::string RenderManager::readShaderFile(const string fileName)
{
  std::ifstream shaderFile( fileName.c_str() );

  shaderFile.seekg(0,std::ios::end);
  std::streampos length = shaderFile.tellg();
  shaderFile.seekg(0,std::ios::beg);

  std::vector<char>       buffer(length);
  shaderFile.read(&buffer[0],length);

  return std::string( buffer.begin(), buffer.end() );
}

GLuint RenderManager::LoadShader ( GLenum type, const string shaderSrc )
{
   GLuint shader;
   GLint compiled;

   shader = glCreateShader ( type );

   if ( shader == 0 )
        return 0;


   const std::string shaderProgram = readShaderFile(shaderSrc);
   const char *shaderData = shaderProgram.c_str();

   glShaderSource ( shader, 1, &shaderData, NULL );
   glCompileShader ( shader );

   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled )
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = new char[infoLen];
         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }
   return shader;
}


GLuint RenderManager::LoadShaderToString( GLenum type, const char *shaderSrc )
{
   GLuint shader;
   GLint compiled;

   shader = glCreateShader ( type );

   if ( shader == 0 )
        return 0;

   glShaderSource ( shader, 1, &shaderSrc, NULL );
   glCompileShader ( shader );

   glGetShaderiv ( shader, GL_COMPILE_STATUS, &compiled );

   if ( !compiled )
   {
      GLint infoLen = 0;

      glGetShaderiv ( shader, GL_INFO_LOG_LENGTH, &infoLen );

      if ( infoLen > 1 )
      {
         char* infoLog = new char[infoLen];
         glGetShaderInfoLog ( shader, infoLen, NULL, infoLog );
         free ( infoLog );
      }

      glDeleteShader ( shader );
      return 0;
   }
   return shader;
}


void RenderManager::startUp(const std::string vertexshader, const std::string fragmentshader){

    vertexShader = LoadShader ( GL_VERTEX_SHADER, vertexshader);
    fragmentShader = LoadShader (GL_FRAGMENT_SHADER, fragmentshader);

    DEBUGLOGPTWO("RenderManager::startUp - load vertex_shader %s fragment_shader %s",vertexshader.c_str(),fragmentshader.c_str());

    if ((vertexShader==0)||(fragmentShader==0)){
        ERRORLOG("RenderManager::startUp - Error al compilar los shaders");
        exit(-1);
    }

    INFOLOG("RENDERMANAGER - INITIALIZED!");
}


void RenderManager::shutDown(){
    INFOLOG("RENDERMANAGER - FINISHED!");
}
