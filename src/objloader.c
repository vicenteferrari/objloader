#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct vec2 {
	union {
		float x;
		float u;
	};

	union {
		float y;
		float v;
	};
} vec2;

typedef struct vec3 {
	union {
		float x;
		float u;
	};

	union {
		float y;
		float v;
	};

	union {
		float z;
		float w;
	};
} vec3;

typedef struct Vertex {
	vec3 pos;
	vec3 norm;
	vec2 tex;
} Vertex;

#include "lists.c"
#include "scanner.c"
#include "parser.c"

char *read_whole_file(const char *path) {
	FILE *file = fopen(path, "rb");
	if (file == NULL) {
		fprintf(stderr, "Could not open file \"%s\".\n", path);
		exit(1);
	}

	fseek(file, 0L, SEEK_END);
	size_t file_size = ftell(file);
	rewind(file);

	char *buffer = (char *) malloc(file_size + 1);
	if (buffer == NULL) {
		fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
		exit(1);
	}
	size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
	if (bytes_read < file_size) {
		fprintf(stderr, "Could not read file \"%s\".\n", path);
		exit(1);
	}
	buffer[bytes_read] = '\0';

	fclose(file);
	return buffer;
}

//int main(int argc, char *argv[]) {
//    setbuf(stdout, NULL);
//    setbuf(stderr, NULL);
//
//	const char *filename = "data/cube.obj";
//
//	const char *source = read_whole_file(filename);
//
//	VertexList list = {};
//	vertexlist_init(&list);
//
//	parse(source, list);
//
//	return 0;
//}
