#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <dirent.h>
#include <string.h>

struct Character {
    wchar_t label[3];
    short imageWidth;
    short imageHeight;
    int charImage[];
};

#define MAX_CHARACTER_SAMPLES 10000

int main() {

    struct Character characters[MAX_CHARACTER_SAMPLES];

    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    char dataset_path[500] = "train1.0/";

    DIR *dir = opendir(dataset_path);
    if (!dir) {
        printf("Dataset directory failed to open");
        return 1;
    }

    int i = 0;
    int maxW = -1;
    int maxH = -1;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {  
        if (entry->d_type != DT_REG) 
            continue;

        FILE *fptr;
        
        char file_path[500];
        memcpy(file_path, dataset_path, strlen(dataset_path));
        sprintf(file_path + strlen(entry->d_name), "%s", entry->d_name);
        fptr = fopen(file_path, "r");
    
        if (fptr == NULL) {
            printf("GNT failed to open");
            return 1;
        }
    
        // Get file size
        fseek(fptr, 0L, SEEK_END);
        long int fileSize = ftell(fptr);
        fseek(fptr, 0L, SEEK_SET);
    
        while (ftell(fptr) < fileSize)
        {
            struct Character c;
    
            long sampleSize;
            wchar_t charLabel[3];
            short imageWidth;
            short imageHeight;
            
            fread(&sampleSize, 4, 1, fptr);
            fread(c.label, 2, 1, fptr);
            fread(&c.imageWidth, 2, 1, fptr);
            fread(&c.imageHeight, 2, 1, fptr);
            
            int charImage[c.imageWidth * c.imageHeight];
            fread(&charImage, c.imageWidth * c.imageHeight, 1, fptr);
            
            if (c.imageWidth > maxW)
                maxW = c.imageWidth;

            if (c.imageHeight > maxH)
                maxH = c.imageHeight;
            
            i++;
        }
        fclose(fptr);
    }

    printf("\n%d samples", i);
    printf("\n%d maxW", maxW);
    printf("\n%d maxH", maxH);

    return 0;

}