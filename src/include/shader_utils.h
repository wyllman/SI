/*
 * shader_utils.h
 *
 *  Created on: 09/11/2013
 *      Author: manwe
 */

#ifndef SHADER_UTILS_H_
#define SHADER_UTILS_H_

#include <GL/glew.h>

#if __cplusplus
extern "C" {
#endif

char* file_read(const char* filename);
void print_log(GLuint object);
GLuint create_shader(const char* filename, GLenum type);

#if __cplusplus
}
#endif

#endif /* SHADER_UTILS_H_ */
