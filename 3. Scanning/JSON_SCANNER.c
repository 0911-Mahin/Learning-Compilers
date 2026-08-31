#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_STRING,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_NUMBER,
    TOKEN_NULL,
    TOKEN_FALSE,
    TOKEN_TRUE,
    TOKEN_ERROR
} token_t;

token_t scan_token(FILE *);
const char *token_str(token_t);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Please provide a file to scan");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Error: Unable to access file (check if file exists)");
        exit(EXIT_FAILURE);
    }

    while (1) {
        token_t token = scan_token(file);
        if (token == TOKEN_EOF)
            break;
        printf("%s\n", token_str(token));
    }

    fclose(file);
}

token_t scan_token(FILE *fp) {
    int ch = fgetc(fp);
    if (ch == EOF) {
        return TOKEN_EOF;
    } else if (isspace(ch)) {
        do {
            ch = fgetc(fp);
            if (ch == EOF)
                return TOKEN_EOF;
        } while (isspace(ch));
        ungetc(ch, fp);
        return scan_token(fp);
    } else if (ch == '{') {
        return TOKEN_LBRACE;
    } else if (ch == '-' || isdigit(ch)) {
        if (ch == '-') {
            ch = fgetc(fp);
            if (!isdigit(ch))
                return TOKEN_ERROR;
        } else if (ch == '0') {
            ch = fgetc(fp);
            if (isdigit(ch) && ch != '.')
                return TOKEN_ERROR;
            ungetc(ch, fp);
        }
        do {
            ch = fgetc(fp);
            if (ch == EOF)
                return TOKEN_ERROR;
        } while (isdigit(ch));
        if (ch == '.') {
            ch = fgetc(fp);
            if (!isdigit(ch))
                return TOKEN_ERROR;
            do {
                ch = fgetc(fp);
                if (ch == EOF)
                    return TOKEN_ERROR;
            } while (isdigit(ch));
        }
        if (ch == 'e' || ch == 'E') {
            ch = fgetc(fp);
            if (ch == '+' || ch == '-')
                ch = fgetc(fp);
            if (!isdigit(ch))
                return TOKEN_ERROR;
            do {
                ch = fgetc(fp);
                if (ch == EOF)
                    return TOKEN_ERROR;
            } while (isdigit(ch));
        }
        ungetc(ch, fp);
        return TOKEN_NUMBER;
    } else if (ch == '\"') {
        do {
            ch = fgetc(fp);
            if (ch == '\\') {
                ch = fgetc(fp);
                ch = fgetc(fp);
            } else if (ch == EOF)
                return TOKEN_ERROR;
        } while (ch != '\"');
        return TOKEN_STRING;
    } else if (ch == ':') {
        return TOKEN_COLON;
    } else if (ch == ',') {
        return TOKEN_COMMA;
    } else if (ch == '}') {
        return TOKEN_RBRACE;
    } else if (ch == '[') {
        return TOKEN_LBRACKET;
    } else if (ch == ']') {
        return TOKEN_RBRACKET;
    } else if (isalpha(ch)) {
        char str[6];
        int i = 0;
        do {
            str[i] = ch;
            i++;
            ch = fgetc(fp);
            if (ch == EOF)
                return TOKEN_ERROR;
        } while (i < 5 && isalpha(ch));
        str[i] = '\0';
        ungetc(ch, fp);
        if (i < 6) {
            if (strcmp(str, "null") == 0)
                return TOKEN_NULL;
            else if (strcmp(str, "true") == 0)
                return TOKEN_TRUE;
            else if (strcmp(str, "false") == 0)
                return TOKEN_FALSE;
        }
    }
    return TOKEN_ERROR;
}

const char *token_str(token_t token) {
    switch (token) {
    case TOKEN_STRING:
        return "String";
        break;
    case TOKEN_LBRACE:
        return "Left Bracket";
        break;
    case TOKEN_RBRACE:
        return "Right Bracket";
        break;
    case TOKEN_LBRACKET:
        return "Left Square Bracket";
        break;
    case TOKEN_RBRACKET:
        return "Right Square Bracket";
        break;
    case TOKEN_COLON:
        return "Colon";
        break;
    case TOKEN_COMMA:
        return "Comma";
        break;
    case TOKEN_NUMBER:
        return "Number";
        break;
    case TOKEN_NULL:
        return "Null";
        break;
    case TOKEN_FALSE:
        return "False";
        break;
    case TOKEN_TRUE:
        return "True";
        break;
    case TOKEN_ERROR:
        return "Error";
        break;
    }
}
