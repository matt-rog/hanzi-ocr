#include <stdio.h>
#include <stdlib.h>

int main() {
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

    long sampleSize;
    char tagCode;
    short imageWidth;
    short imageHeight;

    fread(&sampleSize, 4, 1, fptr);
    fread(&tagCode, 2, 1, fptr);
    fread(&imageWidth, 2, 1, fptr);
    fread(&imageHeight, 2, 1, fptr);

    printf("\n%ld", sampleSize);
    printf("\n%c", tagCode);
    printf("\n%d", imageWidth);
    printf("\n%d", imageHeight);

    int charImage[imageWidth * imageHeight];
    fread(&charImage, imageWidth * imageHeight, 1, fptr);


    FILE* imgFptr;
    imgFptr = fopen("image.bin", "w");

    fwrite(charImage, sizeof(int), imageWidth * imageHeight, imgFptr);
    fclose(imgFptr);
    fclose(fptr);
    return 0;

}