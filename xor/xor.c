#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define er_handler(msg) do{perror(msg); exit(EXIT_FAILURE); }while(0);

int main(int argc, char** argv){
	int a, keyLen, offset = 0;
	char* key;
	FILE* fp;

	/* Check arguments */
	if(argc != 3){
		printf("Usage: xor <textfile> <key>\n\n");
		exit(EXIT_FAILURE);
	}

	key = argv[2];
	keyLen = strlen(key);

	/* Open file */
	if((fp = fopen(argv[1], "r+")) < 0)
		er_handler("Couldnt open file");

	/* Loop through file */
	while((a = getc(fp)) != EOF){
		fseek(fp, -1, SEEK_CUR);
		putc(a ^ key[offset%keyLen], fp);
		offset ++;
	}

	fprintf(stdout,"file \"%s\" en-/decrypted successfully with the key \"%s\"\n", argv[1], argv[2]);
	fclose(fp);
	return 0;
}
