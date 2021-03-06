#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../Modes/KeccakHash.h"

#define KeccakP200_excluded
#define KeccakP400_excluded
#define KeccakP800_excluded

void keccak_hash(Keccak_HashInstance* hashInstance, BitSequence* hashval, int rate, int capacity, unsigned int hashbitlen, unsigned char delimitedSuffix, BitSequence* data, BitLength databitlen) {
    Keccak_HashInitialize(hashInstance, rate, capacity, hashbitlen, delimitedSuffix);
    Keccak_HashUpdate(hashInstance, data, databitlen);
    Keccak_HashFinal(hashInstance, hashval);
}

int main(int argc, char* argv[]) {

    int hashbitlen = 256;

    Keccak_HashInstance hashInstance;
    BitSequence hashval[hashbitlen / 8];

    int rate = 480;
    unsigned char delimitedSuffix = '\1';
    
    BitLength databitlen = 80;
    char datastring[] = "0123456789";
    BitSequence* data = (unsigned char*) datastring;

    int c;
    while ((c = getopt(argc, argv, "r:h:d:s:")) != -1) {
        switch (c) {
            case 'r':
                rate = atoi(optarg);
                break;
            case 'h':
                hashbitlen = atoi(optarg);
                break;
            case 'd':
                delimitedSuffix = atoi(optarg);
                break;
            case 's':
                data = (unsigned char*) optarg;
                databitlen = 8 * strlen(optarg);
                break;
        }
    }

    keccak_hash(&hashInstance, hashval, rate, 1600-rate, hashbitlen, delimitedSuffix, data, databitlen);
    printf("Hash calculated for rate = %d, capacity = %d, hash length = %d, delimited suffix = %02x and string = %s\n", rate, 1600-rate, hashbitlen, delimitedSuffix, data);
    printf("The hash is ");
    for (int i=0; i<hashbitlen/8; i++) {
        printf("%02x", hashval[i]);
    }
    printf("\n");

    return 0;

}
