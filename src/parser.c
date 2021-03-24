//
// Created by vfs on 3/17/21.
//

typedef struct Parser {
	Token current;
	Token previous;
	bool had_error;
} Parser;

Parser parser;

Vec3List pos_list;
Vec3List norm_list;
Vec2List tex_list;

IntList pos_index;
IntList norm_index;
IntList tex_index;

void error_at(Token *token, const char *message) {
	fprintf(stderr, "[line %d] Error", token->line);

	if (token->type == TOKEN_EOF) {
		fprintf(stderr, " at end");
	} else if (token->type == TOKEN_ERROR) {
		// nop
	} else {
		fprintf(stderr, " at '%.*s'", token->length, token->start);
	}

	fprintf(stderr, ": %s\n", message);
	parser.had_error = true;
}

void error(const char *message) {
	error_at(&parser.previous, message);
}

void error_at_current(const char *message) {
	error_at(&parser.current, message);
}

void parser_advance() {
	parser.previous = parser.current;

	while (true) {
		parser.current = scan_token();
		if (parser.current.type != TOKEN_ERROR) break;

		error_at_current(parser.current.start);
	}
}

void consume(TokenType type, const char *message) {
	if (parser.current.type == type) {
		parser_advance();
		return;
	}

	error_at_current(message);
}

bool check(TokenType type) {
	bool res = parser.current.type == type;
	return res;
}

bool parser_match(TokenType type) {
	if (!check(type)) return false;
	parser_advance();
	return true;
}

void parser_identifier() {
	parser_advance();
	printf("%.*s\n", parser.previous.length, parser.previous.start);
}

float parser_float() {
	parser_advance();
	return strtof(parser.previous.start, NULL);
}

int parser_int() {
    parser_advance();
    return strtol(parser.previous.start, NULL, 10);
}

void vertex_statement() {
	float v0 = parser_float();
	float v1 = parser_float();
	float v2 = parser_float();

	vec3list_add(&pos_list, (vec3) {v0, v1, v2});

	printf("vertex: %f, %f, %f\n", v0, v1, v2);
}

void normal_statement() {
	float v0 = parser_float();
	float v1 = parser_float();
	float v2 = parser_float();

    vec3list_add(&norm_list, (vec3) {v0, v1, v2});

	printf("normal: %f, %f, %f\n", v0, v1, v2);
}

void texture_statement() {
	float v0 = parser_float();
	float v1 = parser_float();

    vec2list_add(&tex_list, (vec2) {v0, v1});

	printf("texture: %f, %f\n", v0, v1);
}

void object_statement() {
	parser_identifier();
}

void smooth_statement() {
    parser_identifier();
}

void face_statement() {
    int i0 = parser_int();
    consume(TOKEN_SLASH, "Expected slash\n");
    int i1 = parser_int();
    consume(TOKEN_SLASH, "Expected slash\n");
    int i2 = parser_int();

    int i3 = parser_int();
    consume(TOKEN_SLASH, "Expected slash\n");
    int i4 = parser_int();
    consume(TOKEN_SLASH, "Expected slash\n");
    int i5 = parser_int();

    int i6 = parser_int();
    consume(TOKEN_SLASH, "Expected slash\n");
    int i7 = parser_int();
    consume(TOKEN_SLASH, "Expected slash\n");
    int i8 = parser_int();

    intlist_add(&pos_index, i0);
    intlist_add(&tex_index, i1);
    intlist_add(&norm_index, i2);
    intlist_add(&pos_index, i3);
    intlist_add(&tex_index, i4);
    intlist_add(&norm_index, i5);
    intlist_add(&pos_index, i6);
    intlist_add(&tex_index, i7);
    intlist_add(&norm_index, i8);

    printf("face: %d/%d/%d %d/%d/%d %d/%d/%d\n", i0, i1, i2, i3, i4, i5, i6, i7, i8);
}

void statement() {
	if (parser_match(TOKEN_OBJECT)) {
		object_statement();
	} else if (parser_match(TOKEN_VERTEX)) {
		vertex_statement();
	} else if (parser_match(TOKEN_NORMAL)) {
		normal_statement();
	} else if (parser_match(TOKEN_TEXTURE)) {
		texture_statement();
	} else if (parser_match(TOKEN_SMOOTH)) {
	    smooth_statement();
	} else if (parser_match(TOKEN_FACE)) {
	    face_statement();
	} else {
	    error_at_current("Expected statement!\n");
	}
}

bool parse(const char *source, float **vertices, int *vertex_count) {
	init_scanner(source);

	vec3list_init(&pos_list);
    vec3list_init(&norm_list);
    vec2list_init(&tex_list);

    intlist_init(&pos_index);
    intlist_init(&norm_index);
    intlist_init(&tex_index);

	parser_advance();

	while(!parser_match(TOKEN_EOF)) {
		statement();
	}

	consume(TOKEN_EOF, "Expected end of file.");

    for (int i = 0; i < pos_index.count; ++i) {
        vertexlist_add(&list, (Vertex) {pos_list.memory[pos_index.memory[i]], norm_list.memory[norm_index.memory[i]], tex_list.memory[tex_index.memory[i]]});
    }

	return !parser.had_error;
}
