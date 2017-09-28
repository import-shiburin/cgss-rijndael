#include <stdio.h>
#include <stdlib.h>
#include <mcrypt.h>
#include "rijndael.h"

bytes * bytes_init(char * data, int length)
{
    bytes * byte = (bytes*)malloc(sizeof(bytes));
    byte->data = data;
    byte->length = length;
    return byte;
}

void bytes_free(bytes * addr)
{
    free(addr->data);
    free(addr);
    return;
}

bytes * rijndael256_cbc_encrypt(char * key, char * initVector, char * plaintext, int textlength)
{
    MCRYPT cipher=mcrypt_module_open("rijndael-256", NULL, "cbc", NULL);
    if(cipher==MCRYPT_FAILED)
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        return NULL;
    }
    if(mcrypt_generic_init(cipher, key, 32, initVector)<0)
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        return NULL;
    }
    int cipherlength=(textlength+(32-textlength%32));
    char * ciphertext=(char*)malloc(cipherlength);
    memset(ciphertext, 0, cipherlength);
    memcpy(ciphertext, plaintext, textlength);
    if(mcrypt_generic(cipher, (void*)ciphertext, cipherlength)!=0)
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        free(ciphertext);
        return NULL;
    }
    else
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        return bytes_init(ciphertext, cipherlength);
    }
}

bytes * rijndael256_cbc_decrypt(char * key, char * initVector, char * ciphertext, int textlength)
{
    MCRYPT cipher=mcrypt_module_open("rijndael-256", NULL, "cbc", NULL);
    if(cipher==MCRYPT_FAILED)
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        return NULL;
    }
    if(mcrypt_generic_init(cipher, key, 32, initVector)<0)
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        return NULL;
    }
    char * plaintext=(char*)malloc(textlength);
    memset(plaintext, 0, textlength);
    memcpy(plaintext, ciphertext, textlength);
    if(mdecrypt_generic(cipher, (void*)plaintext, textlength)!=0)
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        free(plaintext);
        return NULL;
    }
    else
    {
        mcrypt_generic_deinit(cipher);
        mcrypt_module_close(cipher);
        return bytes_init(plaintext, textlength);
    }
}