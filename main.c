#include <word-search.h>

static const int DIRECTIONS = 8;

typedef enum
{
    N = 0,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW
} direction;

static const int COLORS = 6;

#define ANSI_CODE_RED "\x1b[31m"
#define ANSI_CODE_GREEN "\x1b[32m"
#define ANSI_CODE_YELLOW "\x1b[33m"
#define ANSI_CODE_BLUE "\x1b[34m"
#define ANSI_CODE_MAGENTA "\x1b[35m"
#define ANSI_CODE_CYAN "\x1b[36m"
#define ANSI_CODE_RESET "\x1b[0m"

typedef enum
{
    COLOR_RED = 0,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN
} color;

static bchar **scramble;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: word-search list puzzle\n");
        return 1;
    }

    setlocale(LC_ALL, "");
    FILE *list, *puzzle;

    list = fopen(argv[1], "r");
    if (!list)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }

    if (is_image(list))
    {
        fclose(list);
        list = read_image(argv[1], WORD_LIST_IMAGE);
    }
    else
    {
        fclose(list); // Closes and reopens file to set back to wide char mode
        list = fopen(argv[1], "r");
    }

    if (!load(list))
    {
        fprintf(stderr, "Failed to build trie\n");
        return 3;
    }

    puzzle = fopen(argv[2], "r");
    if (!puzzle)
    {
        fprintf(stderr, "Could not open %s\n", argv[2]);
        return 4;
    }

    if (is_image(puzzle))
    {
        fclose(puzzle);
        puzzle = read_image(argv[2], PUZZLE_LIST_IMAGE);
    }
    else
    {
        fclose(puzzle); // Closes and reopens file to set back to wide char mode
        puzzle = fopen(argv[2], "r");
    }

    scramble = parse(puzzle);
    if (!scramble)
    {
        fprintf(stderr, "Could not parse puzzle\n");
        return 5;
    }

    int n = row_size();
    int m = col_size();
    if (n == 0 || n == -1)
    {
        fprintf(stderr, "Unable to determine size of sides\n");
        return 6;
    }

    pos cor;

    for (int x = 0; x < m; x++)
    {
        for (int y = 0; y < n; y++)
        {
            cor.x = x;
            cor.y = y;
            cor.ch = towlower(scramble[x][y].ch);
            check(cor);
        }
    }

    for (int x = 0; x < m; x++)
    {
        for (int y = 0; y < n; y++)
        {
            switch (scramble[x][y].color % COLORS)
            {
                case COLOR_RED:
                    wprintf(ANSI_CODE_RED L"%lc" ANSI_CODE_RESET, scramble[x][y].ch);
                    break;
                case COLOR_CYAN:
                    wprintf(ANSI_CODE_CYAN L"%lc" ANSI_CODE_RESET, scramble[x][y].ch);
                    break;
                case COLOR_BLUE:
                    wprintf(ANSI_CODE_BLUE L"%lc" ANSI_CODE_RESET, scramble[x][y].ch);
                    break;
                case COLOR_GREEN:
                    wprintf(ANSI_CODE_GREEN L"%lc" ANSI_CODE_RESET, scramble[x][y].ch);
                    break;
                case COLOR_YELLOW:
                    wprintf(ANSI_CODE_YELLOW L"%lc" ANSI_CODE_RESET, scramble[x][y].ch);
                    break;
                case COLOR_MAGENTA:
                    wprintf(ANSI_CODE_MAGENTA L"%lc" ANSI_CODE_RESET, scramble[x][y].ch);
                    break;
                default:
                    wprintf(L"%lc", scramble[x][y].ch);
                    break;
            }
            wprintf(L" ");
        }
        wprintf(L"\n");
    }

    unload_trie();
    unload_array(scramble);
    fclose(list);
    fclose(puzzle);

    return 0;
}

void check(pos cor)
{
    int count = 0;
    pos *buffer = malloc(word_length() * sizeof(pos));
    pos tmp;
    for (int i = 0; i < DIRECTIONS; i++)
    {
        tmp = cor;
        buffer[count] = cor;
        count++;

        while (true)
        {
            trie *node = locate(buffer, count);
            if (!node)
            {
                break;
            }
            if (node->valid)
            {
                highlight(buffer, count);
                break;
            }
            tmp = translate(tmp, i);
            if (tmp.x == INVALID)
            {
                break;
            }
            buffer[count] = tmp;
            count++;
        }
        count = 0;
    }
    free(buffer);
}

pos translate(pos cor, int dir)
{
    switch (dir)
    {
        case N:
            cor.y = cor.y + 1;
            break;
        case NE:
            cor.x = cor.x + 1;
            cor.y = cor.y + 1;
            break;
        case E:
            cor.x = cor.x + 1;
            break;
        case SE:
            cor.x = cor.x + 1;
            cor.y = cor.y - 1;
            break;
        case S:
            cor.y = cor.y - 1;
            break;
        case SW:
            cor.x = cor.x - 1;
            cor.y = cor.y - 1;
            break;
        case W:
            cor.x = cor.x - 1;
            break;
        case NW:
            cor.x = cor.x - 1;
            cor.y = cor.y + 1;
    }
    if ((cor.x >= row_size() || cor.x < 0) || (cor.y >= col_size() || cor.y < 0))
    {
        cor.x = INVALID;
        return cor;
    }
    cor.ch = towlower(scramble[cor.x][cor.y].ch);

    return cor;
}

void highlight(pos *cors, int length)
{
    static int color = 0;

    for (int i = 0; i < length; i++)
    {
        scramble[cors[i].x][cors[i].y].color = color;
    }

    color++;
}

bool is_image(FILE *inptr)
{
    unsigned char header[8];
    fread(header, sizeof(unsigned char), 8, inptr);
    if ((header[0] == 137 && header[1] == 80 &&
                header[2] == 78 && header[3] == 71 &&
                header[4] == 13 && header[5] == 10 &&
                header[6] == 26 && header[7] == 10) ||
                (header[0] == 0xFF && header[1] == 0xD8 &&
                header[2] == 0xFF))
    {
        return true;
    }
    else
    {
        return false;
    }
}
