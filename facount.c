#include <zlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_LENGTH (1024*16)

void help()
{
    fprintf(stderr, "\n");
    fprintf(stderr, "Usage:   facount <in.fa>...\n\n");
}

void process(const char * file, int printFile)
{
	gzFile fp;
    char buffer[BUFFER_LENGTH]; // 16kb buffer
    fp = strcmp(file, "-")? gzopen(file, "r") : gzdopen(fileno(stdin), "r");
    int count, l, c;
    count = 0;
    while ((l = gzread(fp, buffer, BUFFER_LENGTH)) > 0) {
        c = 0;
        while(c < l) {
            if(buffer[c] == '>') {
                count += 1;   
            }
            c++;
        }
    }
    if(printFile)
    {
        printf("%s\t%d\n", file, count);
    } else {
        printf("%d\n", count);
    }
    gzclose(fp);
}

int main(int argc, char * argv[])
{
    int print_file = 0;
    int c;
    while ((c = getopt (argc, argv, "hH")) != -1)
    {
        switch(c)
        {
            case 'H': print_file = 1; break;
            case 'h': help(); return 1; break;
        }
    }

    if(optind >= argc) 
    {
        process("-", print_file);
    }
    else 
    {
        int i;
        for(i = optind; i < argc; ++i)
        {
            process(argv[i], print_file);
        }
    }
	return 0;
}
