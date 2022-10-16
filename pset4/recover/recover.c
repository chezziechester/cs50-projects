#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover [file]\n");
        return 1;
    }
    
    //pointer for input file
    FILE *inptr = fopen(argv[1], "r");

    if (inptr == NULL)
    {
        fprintf(stderr, "File could not be opened.\n");
        return 1;
    }
    
    //pointer for output file
    FILE *outptr = NULL;
    int count = 0;
    unsigned char *buffer = malloc(512);

    //fread works inside the loop, no need to declare within loop
    //fread returns amount of elements
    while (fread(buffer, 512, 1, inptr) == 1)
    {
        //create string buffer to hold the file names
        char *stringBuffer = malloc(sizeof(char) * 8);

        //using bitwise arithmetic to compare 1111 with the first four bits to check if it is 1110 (check if it is jpg)
        //also used to check for end of file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (count == 0)
            {
                sprintf(stringBuffer, "%03i.jpg", 0);
                count++;
                //open and then write from buffer to outptr
                outptr = fopen(stringBuffer, "w");
                fwrite(buffer, 512, 1, outptr);
            }

            else
            {
                //close the file from before
                fclose(outptr);
                //same thing for above
                sprintf(stringBuffer, "%03i.jpg", count);
                count++;
                outptr = fopen(stringBuffer, "w");
                fwrite(buffer, 512, 1, outptr);
            }
        }

        else
        {
            //since images are back to back
            if (count > 0)
            {
                fwrite(buffer, 512, 1, outptr);
            }
        }
    }

    fclose(inptr);
    fclose(outptr);
    free(buffer);
}
