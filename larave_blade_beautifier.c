// Requirements: Pass blade file to be beautified as argument
// All the tags for which indents have to applied should open and close in a new line

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2)
       return 0;
    FILE *readfile, *outfile;
    int spaces = 0, i;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char spa[128];
    strcpy(spa, "");
    int lineno = 0;
    int divcount=0, ifcount=0, ulcount=0, fieldsetcount=0,tablecount=0, tdcount=0, trcount=0, selectcount=0, spancount= 0, formcount=0, forcount=0;

    readfile = fopen(argv[1], "r");
    outfile = fopen("output.txt", "w");

    while ((read = getline(&line, &len, readfile)) != -1) {
        lineno++;
        if (!strncmp(line, "</div", 5) || !strncmp(line, "@end", 4) || !strncmp(line, "@else", 5) || !strncmp(line, "</ul", 4) || !strncmp(line, "</fieldset", 10) || !strncmp(line, "</table", 7) || !strncmp(line, "</tr", 4) || !strncmp(line, "</td ", 4) || !strncmp(line, "</table", 7) || !strncmp(line, "</select", 7) || !strncmp(line, "</span", 6) || !strncmp(line, "</form", 6))
        {
            spaces -= 4;
            strcpy(spa, "");
            for (i=0; i<spaces; i++)
                sprintf(spa, "%s ", spa);
        }

        if (!strncmp(line, "</div", 5))
          divcount--;
        if (!strncmp(line, "@endif", 6))
          ifcount--;
        if ( !strncmp(line, "@endfor", 7))
          forcount--;
        if ( !strncmp(line, "</ul", 4))
          ulcount--;
        if (!strncmp(line, "</fieldset", 10))
          fieldsetcount--;
        if (!strncmp(line, "</table", 7))
          tablecount--;
        if (!strncmp(line, "</tr", 4))
          trcount--;
        if ( !strncmp(line, "</td ", 4))
          tdcount--;
        if (!strncmp(line, "</select", 7))
          selectcount--;
        if (!strncmp(line, "</span", 6))
          spancount--;
        if (!strncmp(line, "</form", 6))
          formcount--;

        if (spaces < 0)
        {
           printf("CRITICAL: Negative spacing at line %d", lineno);
           return 0;
        }

        fprintf(outfile, "%s%s", spa, line);


        if (!strncmp(line, "<div", 4) || !strncmp(line, "@if", 3) || !strncmp(line, "@else", 5) || !strncmp(line, "@for", 4) || !strncmp(line, "<ul", 3) || !strncmp(line, "<fieldset", 9) || !strncmp(line, "<table", 6) || !strncmp(line, "<tr", 3) || !strncmp(line, "<td", 3) || !strncmp(line, "<select", 7) ||  !strncmp(line, "<span", 5) ||  !strncmp(line, "<form", 5))
        {
            spaces += 4;
            strcpy(spa, "");
            for (i=0; i<spaces; i++)
                sprintf(spa, "%s ", spa);
        }

        if (!strncmp(line, "<div", 4))
           divcount++;
        if (!strncmp(line, "@if", 3))
           ifcount++;
        if ( !strncmp(line, "@for", 4))
           forcount++;
        if (!strncmp(line, "<ul", 3))
           ulcount++;
        if (!strncmp(line, "<fieldset", 9))
           fieldsetcount++;
        if ( !strncmp(line, "<table", 6))
           tablecount++;
        if (!strncmp(line, "<tr", 3) )
           trcount++;
        if ( !strncmp(line, "<td", 3) )
           tdcount++;
        if ( !strncmp(line, "<select", 7))
          selectcount++;
        if ( !strncmp(line, "<span", 5))
          spancount++;
        if (  !strncmp(line, "<form", 5))
          formcount++;

        if (spaces < 0)
        {
           printf("CRITICAL: Negative spacing at line %d", lineno);
           return 0;
        }
        free(line);
        line = NULL;
    }

    printf("EXTRA TAG STATS:\n divcount=%d\n ifcount=%d\n ulcount=%d\n fieldsetcount=%d\n tablecount=%d\n tdcount=%d\n trcount=%d\n selectcount=%d\n spancount= %d\n formcount=%d\n forcount=%d\n", divcount, ifcount, ulcount, fieldsetcount, tablecount, tdcount, trcount, selectcount, spancount, formcount, forcount);

    fclose(readfile);
    fclose(outfile);
}
