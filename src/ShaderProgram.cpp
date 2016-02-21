#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() :
    shaderSources(), attributeLocations(), validProgram(false), program(0) {
  std::cout << "Shader program construct called\n";
}

ShaderProgram::~ShaderProgram(){}

void ShaderProgram::setShaderSource(const GLenum type, const std::string &source) {
  std::string vertexShaderSource = readGLSLSource(source);
  shaderSources[type] = vertexShaderSource;
  validProgram = false;
}


bool ShaderProgram::update() {
  std::cout << "update shader program!\n";
  if (program) 
    glDeleteProgram(program);
  std::cout << "create program\n";
  program = glCreateProgram();
  if (!program) {
    std::cout << "program not valid\n";
    return false;
  }

  std::cout << "create and attach shaders!\n";
  // Create and attach shaders to the program
  for (auto it = shaderSources.begin(); it != shaderSources.end(); ++it) {
    GLenum type = it->first;
    const std::string &source = it->second;
    uint32_t shader = createShader(type, source.c_str());
    if (!(shader > 0)) 
      return false;
    glAttachShader(program, shader);
    glDeleteShader(shader); 
  }

  // Bind attribute locations
  for (auto it = attributeLocations.begin(); it != attributeLocations.end(); ++it) {
    const std::string &name = it->first;
    GLint location = it->second;
    glBindAttribLocation(program, location, name.c_str());
  }
        
  // Link the program
  if (!linkProgram(program)) {
    return false;
  }
        
  validProgram = true;
  
  return true;
}


// --------------- Help functions --------------
bool ShaderProgram::linkProgram(GLuint program){
  glLinkProgram(program);
        
  // Check linking status
  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked) {
    showProgramInfoLog(program);
    glDeleteProgram(program);
    return false;
  }
        
  return true;
}
    
bool ShaderProgram::validateProgram(GLuint program) {
  glValidateProgram(program);
        
  // Check validation status
  GLint validated;
  glGetProgramiv(program, GL_VALIDATE_STATUS, &validated);
  if (!validated) {
    std::cerr << "Invalid program." << std::endl;
    glDeleteProgram(program);
    return false;
  }
        
  return true;
}

std::string ShaderProgram::readGLSLSource(const std::string &filename) {
  std::ifstream file(filename);
  std::stringstream stream;
  stream << file.rdbuf();
  return stream.str();
}

GLuint ShaderProgram::createShader(GLenum type, const char* shader_source) {
  // Create shader object
  GLuint shader = glCreateShader(type);
  if (!glIsShader(shader)) 
    return 0;
  
  // Load the shader source
  glShaderSource(shader, 1, &shader_source, NULL);
  
  // Compile the shader
  glCompileShader(shader);
	
  // Check compile status
  GLint compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (!compiled) {
    showShaderInfoLog(shader);
    glDeleteShader(shader);
    return 0;
  }
  return shader;
}

void ShaderProgram::showShaderInfoLog(GLuint shader) {
  if (!glIsShader(shader)) {
    std::cerr << "Input argument is not a shader." << std::endl;
    return;
  }
        
  GLint infoLogLength = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 1) {
    char* infoLog = (char*)malloc(infoLogLength * sizeof(char));
    glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);
    std::cerr << "Error compiling shader:\n" << infoLog << std::endl;
    free(infoLog);
  }
}

void ShaderProgram::showProgramInfoLog(GLuint program) {
  if (!glIsProgram(program)) {
    std::cerr << "Input argument is not a program." << std::endl;
    return;
  }
        
  GLint infoLogLength = 0;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 1) {
    char* infoLog = (char*)malloc(infoLogLength * sizeof(char));
    glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);
    std::cerr << "Error linking program:\n" << infoLog << std::endl;
    free(infoLog);
  }
}
