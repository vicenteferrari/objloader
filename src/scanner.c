//
// Created by vfs on 3/17/21.
//

typedef struct Scanner {
	const char *start;
	const char *current;
	int line;
} Scanner;

typedef enum TokenType {
	TOKEN_OBJECT,
	TOKEN_VERTEX,
	TOKEN_TEXTURE,
	TOKEN_NORMAL,
	TOKEN_FACE,
	TOKEN_NUMBER,
	TOKEN_SLASH,
	TOKEN_IDENTIFIER,
	TOKEN_SMOOTH,

	TOKEN_ERROR,
	TOKEN_EOF,
} TokenType;

typedef struct Token {
	TokenType type;
	const char *start;
	int length;
	int line;
} Token;

Scanner scanner;

void init_scanner(const char *source) {
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}

bool is_at_end() {
	return *scanner.current == '\0';
}

bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

bool is_alpha(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool is_whitespace(char c) {
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool match(char expected) {
	if (is_at_end()) return false;
	if (*scanner.current != expected) return false;

	scanner.current++;
	return true;
}

char advance() {
	scanner.current++;
	return scanner.current[-1];
}

char peek() {
	return *scanner.current;
}

char peek_next() {
	if (is_at_end()) return '\0';
	return scanner.current[1];
}

void skip_whitespace() {
	while(true) {
		char c = peek();
		switch (c) {
			case ' ':
			case '\r':
			case '\t':
				advance();
				break;

			case '\n':
				scanner.line++;
				advance();
				break;

			case '#':
				while (peek() != '\n' && !is_at_end()) advance();
				break;

			default:
				return;
		}
	}
}

Token error_token(const char *message) {
	Token token;
	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = (int) strlen(message);
	token.line = scanner.line;

	return token;
}

Token make_token(TokenType type) {
	Token token;
	token.type = type;
	token.start = scanner.start;
	token.length = (int) (scanner.current - scanner.start);
	token.line = scanner.line;

	return token;
}

TokenType check_keyword(int start, int length, const char *rest, TokenType type) {
	if (scanner.current - scanner.start == start + length && memcmp(scanner.start + start, rest, length) == 0) return type;

	return TOKEN_IDENTIFIER;
}

TokenType identifier_type() {
	switch (*scanner.start) {
		case 'f': return check_keyword(1, 0, "", TOKEN_FACE);
		case 'o': return check_keyword(1, 0, "", TOKEN_OBJECT);
		case 's': return check_keyword(1, 0, "", TOKEN_SMOOTH);
		case 'v':
			if (scanner.current - scanner.start > 1) {
				switch (scanner.start[1]) {
					case 't': return check_keyword(2, 0, "", TOKEN_TEXTURE);
					case 'n': return check_keyword(2, 0, "", TOKEN_NORMAL);
				}
			} else {
				return check_keyword(1, 0, "", TOKEN_VERTEX);
			}
	}

	return TOKEN_IDENTIFIER;
}

Token number() {
	if (*scanner.current == '-' && (is_alpha(peek()) || is_whitespace(peek()))) return error_token("Unexpected minus sign");

	while (is_digit(peek())) advance();

	if (peek() == '.' && is_digit(peek_next())) {
		advance();

		while (is_digit(peek())) advance();
	}

	return make_token(TOKEN_NUMBER);
}

Token identifier() {
	while (is_alpha(peek()) || is_digit(peek())) advance();

	return make_token(identifier_type());
}

Token scan_token() {
	skip_whitespace();

	scanner.start = scanner.current;

	if (is_at_end()) return make_token(TOKEN_EOF);

	char c = advance();

	if (is_alpha(c)) return identifier();
	if (is_digit(c) || c == '-') return number();

	switch (c) {
		case '/':
			return make_token(TOKEN_SLASH);
	}

	return error_token("Unexpected character");
}
