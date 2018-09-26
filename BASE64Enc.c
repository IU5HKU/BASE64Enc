/*************************************************
* Simple BASE64 Encoder, for embed icons in html
* September 2018  - M.Campinoti
**************************************************/

#include <stdio.h>
#include <string.h>

union conv
{
    unsigned int l;
    struct bytes
    {
        char b1;
        char b2;
        char b3;
        char b4;
    } b;
};

char convert(char c)
{
    if (c == 63)
        return 47;
    else if (c == 62)
        return 43;
    else if (c >= 52)
        return c - 4;
    else if (c >= 26)
        return c + 71;
    else
        return c + 65;
}

unsigned int toBase64(unsigned char b1, unsigned char b2, unsigned char b3)
{
    conv src, dest;
    src.b.b1 = b3;
    src.b.b2 = b2;
    src.b.b3 = b1;
    src.b.b4 = 0;
    //conv.l == b4 b3 b2 b1
    dest.b.b1 = convert(src.b.b1 & 0x3f);
    src.l = src.l >> 6;
    dest.b.b2 = convert(src.b.b1 & 0x3f);
    src.l = src.l >> 6;
    dest.b.b3 = convert(src.b.b1 & 0x3f);
    src.l = src.l >> 6;
    dest.b.b4 = convert(src.b.b1 & 0x3f);

    return dest.l;
}

int main(int argc, char *argv[])
{
    FILE *output_file;
    FILE *input_file;
    char out_file_name[256];
    unsigned char input_buffer[3];
    int bytes_read;
    conv dest;
        
    if (argc == 2){
        if ((input_file = fopen(argv[1], "rb")) == NULL){
            printf("(!)input file error\n");
            return 1;
        }
    }
    else
    {
        printf("usage: B64ENC [inputfile]\n");
        return 3;
    }
    
    // add .html extension
    strcpy(&out_file_name[0], argv[1]);
    strcat(&out_file_name[0], ".html");

    //and open file for writing a base64 encoded png image
    if ((output_file = fopen(out_file_name, "wt")) == NULL){
        printf("(!)cannot open output file\n");
        return 2;
    }
    
    fprintf(output_file, "<img src='data:image/png;base64,");

    while (!feof(input_file)){
        bytes_read = fread(&input_buffer, sizeof(char), 3, input_file);
        if (bytes_read = 3){
            dest.l = toBase64(input_buffer[0], input_buffer[1], input_buffer[2]);
        }
        else{
            switch (bytes_read){
            case 0:
                input_buffer[0] = input_buffer[1] = input_buffer[2] = 0x00;
                break;
            case 1:
                input_buffer[1] = input_buffer[2] = 0x00;
                break;
            case 2:
                input_buffer[2] = 0x00;
                break;
            }
        }
        //conv.l == b4 b3 b2 b1
        fprintf(output_file, "%c%c%c%c", dest.b.b4, dest.b.b3, dest.b.b2, dest.b.b1);
    }
        
    fprintf(output_file, "'/>");
    
    fclose(output_file);
    fclose(input_file);
	return 0;
}
