#include <word-search.h>
#include <string.h>
#include <allheaders.h>
#include <tesseract/capi.h>

#define CONFIG_SIZE 1

FILE *read_puzzle_image(char *file)
{
    char **configs = malloc(sizeof(char *));
    if (!configs)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return NULL;
    }
    configs[0] = "blacklist";

    TessBaseAPI *handle = TessBaseAPICreate();
    if(TessBaseAPIInit1(handle, NULL, "eng", OEM_TESSERACT_ONLY, configs, CONFIG_SIZE) != 0)
    {
        fprintf(stderr, "Could not initialize tesseract\n");
        return NULL;
    }
    TessBaseAPISetPageSegMode(handle, PSM_SINGLE_BLOCK);

    PIX *img = pixRead(file);
    if (!img)
    {
        fprintf(stderr, "Could not open %s\n", file);
        return NULL;
    }

    TessBaseAPISetImage2(handle, img);
    if(TessBaseAPIRecognize(handle, NULL) != 0)
    {
        fprintf(stderr, "Could not perform recognition\n");
    }

    char *text = TessBaseAPIGetUTF8Text(handle);
    if (!text)
    {
        fprintf(stderr, "Could not get text\n");
        return NULL;
    }

    char *buf = malloc(DEFAULT_SIZE * sizeof(char));
    if (!buf)
    {
        fprintf(stderr, "Failed to allocate memory\n");
    }

    int n = snprintf(buf, sizeof(file), "%s%s", file, ".txt");
    if (n != 0)
    {
        free(buf);
        buf = malloc((DEFAULT_SIZE * sizeof(char)) + (sizeof(char) * n));
        snprintf(buf, (DEFAULT_SIZE * sizeof(char)) + (sizeof(char) * n), "%s%s", file, ".txt");
    }

    FILE *puzzle_img = fopen(buf, "w");
    fputs(text, puzzle_img);
    // Opens and cloes file to reset to wide char mode
    fclose(puzzle_img);
    puzzle_img = fopen(buf, "r");

    free(buf);
  	TessDeleteText(text);
	TessBaseAPIEnd(handle);
	TessBaseAPIDelete(handle);
	pixDestroy(&img);
	free(configs);
	
	return puzzle_img;
}

FILE *read_list_image(char *file)
{
    TessBaseAPI *handle = TessBaseAPICreate();
    if(TessBaseAPIInit2(handle, NULL, "eng", OEM_LSTM_ONLY) != 0)
    {
        fprintf(stderr, "Could not initialize tesseract\n");
        return NULL;
    }
    TessBaseAPISetPageSegMode(handle, PSM_AUTO);

    PIX *img = pixRead(file);
    if (!img)
    {
        fprintf(stderr, "Could not open %s\n", file);
        return NULL;
    }

    TessBaseAPISetImage2(handle, img);
    if(TessBaseAPIRecognize(handle, NULL) != 0)
    {
        fprintf(stderr, "Could not perform recognition\n");
    }

    char *text = TessBaseAPIGetUTF8Text(handle);
    if (!text)
    {
        fprintf(stderr, "Could not get text\n");
        return NULL;
    }

    char *buf = malloc(DEFAULT_SIZE * sizeof(char));
    if (!buf)
    {
        fprintf(stderr, "Failed to allocate memory\n");
    }

    int n = snprintf(buf, sizeof(file), "%s%s", file, ".txt");
    if (n != 0)
    {
        free(buf);
        buf = malloc((DEFAULT_SIZE * sizeof(char)) + (sizeof(char) * n));
        snprintf(buf, (DEFAULT_SIZE * sizeof(char)) + (sizeof(char) * n), "%s%s", file, ".txt");
    }

    FILE *output = fopen(buf, "w");
    fputs(text, output);
    // Opens and cloes file to reset to wide char mode
    fclose(output);
    output = fopen(buf, "r");

    free(buf);
  	TessDeleteText(text);
	TessBaseAPIEnd(handle);
	TessBaseAPIDelete(handle);
	pixDestroy(&img);
	
	return output;
}
