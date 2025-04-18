/*
 * Copyright © 2020-2022, Matjaž Guštin <dev@matjaz.it>
 * <https://matjaz.it>. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of nor the names of its contributors may be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS “AS IS”
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @file
 * @internal
 * Hazelnet wrapper of the AEAD function: Authenticated Encryption with
 * Associated Data.
 *
 * The idea of this wrapper is to provide a stable interface in case the
 * implementation of the AEAD function is changed from one cipher to another.
 */

#include "hzl_CommonAead.h"
#include "ascon.h"


#include <wolfssl/options.h>         // First if using options
#include <wolfssl/wolfcrypt/aes.h>
#include <string.h>
#include <stdio.h>

_Static_assert(ASCON_AEAD128_KEY_LEN == HZL_LTK_LEN,
               "AEAD cipher must accept LTK length.");
_Static_assert(ASCON_AEAD128_KEY_LEN == HZL_STK_LEN,
               "AEAD cipher must accept STK length.");
_Static_assert(ASCON_AEAD_NONCE_LEN
               >= HZL_CTRNONCE_LEN + HZL_GID_LEN + HZL_SID_LEN,
               "AEAD nonce must fit the concatenation ctrnonce || GID || SID.");


Aes enc;
uint8_t aeadNonce[16U];
uint8_t aes_key[16U];
uint8_t aead


int nonce_set = 0;
void
hzl_AeadInit(hzl_Aead_t* const ctx,
             const uint8_t* const key,
             const uint8_t* const nonce)
{
    //ascon_aead128_init(ctx, key, nonce);
    void* hint = NULL;
    int devId = INVALID_DEVID; //if not using async INVALID_DEVID is default

    //heap hint could be set here if used
    wc_AesInit(&enc, hint, devId);
    memcpy(aes_key, key, 16U);

    int result =        (&enc, aes_key, 16U);
    printf("Result from set key %d\n", result);

    memcpy(aeadNonce, nonce, 16U);
}

void
hzl_AeadAssocDataUpdate(hzl_Aead_t* const ctx,
                        const uint8_t* const assocData,
                        const size_t assocDataLen)
{
    return;
    //ascon_aead128_assoc_data_update(ctx, assocData, assocDataLen);
}

size_t
hzl_AeadEncryptUpdate(hzl_Aead_t* const ctx,
                      uint8_t* const ciphertext,
                      const uint8_t* const plaintext,
                      const size_t plaintextLen,
                      uint8_t* const tag,
                      const uint8_t tagLen)
{


    int result = wc_AesGcmEncrypt(&enc, 
    ciphertext, 
    plaintext, 
    plaintextLen, 
    aeadNonce, 
    16U, 
    tag, 
    tagLen, 
    NULL,
    0);

    // printf("Encrypt nonce is: ");
    // for(int i = 0; i < 15; i++) {
    //     printf("%x", aeadNonce[i]);
    // }
    // printf("\n");

    /*

    printf("Encrypt Tag is: ");
    for(int i = 0; i < 15; i++) {
        printf("%x", tag[i]);
    }
    printf("\n");
    */


    
    //wc_AesFree(&enc);

    return plaintextLen;
    //return ascon_aead128_encrypt_update(ctx, ciphertext, plaintext, plaintextLen);
}

void
hzl_AeadEncryptFinish(hzl_Aead_t* const ctx,
                      uint8_t* const ciphertext,
                      uint8_t* const tag,
                      const uint8_t tagLen)
{
    ascon_aead128_encrypt_final(ctx, ciphertext, tag, tagLen);
}

hzl_Err_t
hzl_AeadDecryptUpdate(hzl_Aead_t* const ctx,
                      uint8_t* const plaintext,
                      const uint8_t* const ciphertext,
                      const size_t ciphertextLen,
                      const uint8_t* const tag,
                      const uint8_t tagLen)
{

    // printf("Decrypt nonce is: ");
    // for(int i = 0; i < 15; i++) {
    //     printf("%x", aeadNonce[i]);
    // }
    // printf("\n");


    /*
    printf("Decrypt Tag is: ");
    for(int i = 0; i < 15; i++) {
        printf("%x", tag[i]);
    }
    printf("\n");
    */



    int result = wc_AesGcmDecrypt(&enc, 
    plaintext, 
    ciphertext, 
    ciphertextLen, 
    aeadNonce, 
    16U, 
    tag,
    tagLen, 
    NULL,
    0);
    if(result == 0) {
        printf("SUCCESSFUL DECRYPT\n");
        return HZL_OK;
    } else {
        printf("ERROR DECRYPTING,result %d\n", result);
        return HZL_OK;
        //return HZL_ERR_SECWARN_INVALID_TAG;
    }
    //wc_AesFree(&enc);
    
    
    
    //return ascon_aead128_decrypt_update(ctx, plaintext, ciphertext, ciphertextLen);
}

hzl_Err_t
hzl_AeadDecryptFinish(hzl_Aead_t* const ctx,
                      uint8_t* const plaintext,
                      const uint8_t* const tag,
                      const uint8_t tagLen)
{
    bool is_tag_valid = false;
    ascon_aead128_decrypt_final(
            ctx, plaintext, &is_tag_valid, tag, tagLen);
    return is_tag_valid == ASCON_TAG_OK ? HZL_OK : HZL_ERR_SECWARN_INVALID_TAG;
}
