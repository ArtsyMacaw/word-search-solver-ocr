#include <word-search.h>

#define DIRECTIONS 8

#define N 0
#define NE 1
#define E 2
#define SE 3
#define S 4
#define SW 5
#define W 6
#define NW 7

#define BOLD "\x1b[31m"
#define RESET "\x1b[0m"

static bchar **scramble;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: word-search list puzzle\n");
        return 1;
    }
    
    setlocale(LC_ALL, "");
    FILE *list, *puzzle;

    list = fopen(argv[1], "r");
    if (!list)
    {
        printf("Could not open %s\n", argv[1]);
        return 2;
    }

    // Check if png or jpeg
    unsigned char header[8];
    fread(header, sizeof(unsigned char), 8, list);
    if ((header[0] == 137 && header[1] == 80 &&
                header[2] == 78 && header[3] == 71 &&
                header[4] == 13 && header[5] == 10 &&
                header[6] == 26 && header[7] == 10) ||
                (header[0] == 0xFF && header[1] == 0xD8 &&
                header[2] == 0xFF))
    {
        fclose(list);
        list = read_list_image(argv[1]);
    }
    else
    {
        fclose(list);
        list = fopen(argv[1], "r");
    }

    if (!load(list))
    {
        printf("Failed to build trie\n");
        return 3;
    }

    puzzle = fopen(argv[2], "r");
    fread(header, sizeof(unsigned char), 8, puzzle);
    if ((header[0] == 137 && header[1] == 80 &&
                header[2] == 78 && header[3] == 71 &&
                header[4] == 13 && header[5] == 10 &&
                header[6] == 26 && header[7] == 10) ||
                (header[0] == 0xFF && header[1] == 0xD8 &&
                header[2] == 0xFF))
    {
        fclose(puzzle);
        puzzle = read_puzzle_image(argv[2]);
    }
    else
    {
        fclose(puzzle);
        puzzle = fopen(argv[2], "r");
    }

    if (!puzzle)
    {
        printf("Could not open %s\n", argv[2]);
        return 4;
    }

    scramble = parse(puzzle);
    if (!scramble)
    {
        printf("Could not parse puzzle");
        return 5;
    }

    int n = row_size();
    int m = col_size();
    if (n == 0 || n == -1)
    {
        printf("Unable to determine size of sides\n");
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
            if (scramble[x][y].highlight)
            {
                wprintf(BOLD L"%lc" RESET, scramble[x][y].ch);
            }
            else
            {
                wprintf(L"%lc", scramble[x][y].ch);
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
    pos *buffer = malloc(max_size() * sizeof(pos));
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
            if (tmp.x == -1)
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
        cor.x = -1;
        return cor;
    }
    cor.ch = towlower(scramble[cor.x][cor.y].ch);

    return cor;
}

void highlight(pos *cors, int length)
{
    for (int i = 0; i < length; i++)
    {
        scramble[cors[i].x][cors[i].y].highlight = true;
    }
}
