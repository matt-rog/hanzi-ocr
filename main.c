#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

struct Character {
    char label;
    short imageWidth;
    short imageHeight;
    int charImage[];
};

#define MAX_CHARACTER_SAMPLES 100000

int main() {

    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    FILE *fptr;

    fptr = fopen("train1.0/001-f.gnt", "r");

    if (fptr == NULL)
    {
        printf("GNT failed to open");
        return 1;
    }

    // Get file size
    fseek(fptr, 0L, SEEK_END);
    long int fileSize = ftell(fptr);
    fseek(fptr, 0L, SEEK_SET);

    int i = 0;
    while (ftell(fptr) < fileSize)
    {
        printf("\n%ld", ftell(fptr));
        
        long sampleSize;
        wchar_t charLabel[3];
        short imageWidth;
        short imageHeight;
        
        fread(&sampleSize, 4, 1, fptr);
        fread(charLabel, 2, 1, fptr);
        fread(&imageWidth, 2, 1, fptr);
        fread(&imageHeight, 2, 1, fptr);
        
        printf("\n%ld", sampleSize);
        printf("\n%ls", charLabel);
        printf("\n%d", imageWidth);
        printf("\n%d", imageHeight);
        
        int charImage[imageWidth * imageHeight];
        fread(&charImage, imageWidth * imageHeight, 1, fptr);
        
        
        FILE* imgFptr;
        imgFptr = fopen("image.bin", "w");
        
        fwrite(charImage, sizeof(int), imageWidth * imageHeight, imgFptr);
        fclose(imgFptr);
    }

    fclose(fptr);
    return 0;

}