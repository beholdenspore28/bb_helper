#include <stdio.h>
#include <blib/blib.h>

static inline bool is_white_space(int c) {
	return	c == ' ' ||
			c == '\t' ||
			c == '\n';
}

typedef union {
	char* string;
	double number;
	void* object;
	void* array;
	bool bool_value;
	bool is_null;
} json_value_t;

bool is_number(char c) {
	return c >= '0' && c <= '9';
}

void json_parse(FILE* file) {
	static int c;
	while ((c = fgetc(file)) != EOF) {
		if (is_white_space(c))
			continue;
		switch(c) {
			case '{':
				json_parse(file);
				break;
			case '}':
				return;
			case '[':
				json_parse(file);
				break;
			case ']':
				return;
			case '"':
				while ((c = fgetc(file)) != EOF) {
					if (c == '"') {
						break;
					}
					putchar(c);
				}
				break;
			case ',':
				// add value to list then reset it for later use
				break;
			case 'n':
				if ((c = fgetc(file) != 'u' && c != EOF))
					break;
				if ((c = fgetc(file) != 'l' && c != EOF))
					break;
				if ((c = fgetc(file) != 'l' && c != EOF))
					break;

				printf("NULL\n");
				
				break;
			case 'f':
				if ((c = fgetc(file) != 'a' && c != EOF))
					break;
				if ((c = fgetc(file) != 'l' && c != EOF))
					break;
				if ((c = fgetc(file) != 's' && c != EOF))
					break;
				if ((c = fgetc(file) != 'e' && c != EOF))
					break;
				break;
			case 't':
				if ((c = fgetc(file) != 'r' && c != EOF))
					break;
				if ((c = fgetc(file) != 'u' && c != EOF))
					break;
				if ((c = fgetc(file) != 'e' && c != EOF))
					break;
				break;
			default: 
				{
					if (is_number(c)) {
						ungetc(c, file);
						double n;
						fscanf(file, "%lf", &n);
						printf("%.14g", n);
					} else {
						printf("ERROR unhandled character '%c'\n", c);
					}
					break;
				}
		}

		putchar('\n');
	}
}

