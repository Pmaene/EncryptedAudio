#include "crypto.h"

// Diffie-Hellman
const unsigned char     Enc_Generator[ENC_PRIVATE_KEY_CHARS] =
    "\x82\xc1\x57\x1c\xf6\x8d\x59\xaa\xc1\x93\x67\xc7\xde\x23\x4b"
    "\xe8\xc3\xb9\x20\xb8\x36\x2d\x21\xf5\x3e\x3c\x6b\xc8\x4e\xaa"
    "\x5c\x54\x8d\x84\x88\x73\x3a\xc3\x27\x8b\xcf\x66\xe6\x35\xbe"
    "\xbd\x20\x73\x4b\x4b\xea\xaa\x48\x46\xf1\xbc\xf4\x8d\xfa\x0d"
    "\x91\xa3\xbb\xd2\x97\x27\x21\x84\x25\x66\x78\x03\x6d\xd5\x66"
    "\x80\xc5\xa1\x63\x6b\x25\x36\xd7\xe2\x3e\xf6\x6a\xac\x1d\x62"
    "\xb7\xdb\x3c\x6f\xbe\x05\x75\x1b\x1b\x64\x2f\x7c\x1a\xba\x7c"
    "\x07\x4f\x48\x8e\x34\x7b\xf4\xd7\xff\x25\x5f\x2d\x13\x4d\x87"
    "\x4b\x06\x54\x19\x84\xe0\x3d\x61\x14\x4e\x7a\xfb\x12\x38\x34"
    "\x62\x5e\xc0\x33\x7d\xea\xe4\x70\xa6\x79\x9c\x05\x87\xbb\xed"
    "\x9a\xcc\xf1\x0d\xf0\x8b";

const unsigned char         Enc_Prime[ENC_PRIVATE_KEY_CHARS] =
    "\xd0\xa8\x73\x80\x04\xa3\x5f\x3d\x10\xf9\x34\x92\x24\xcc\x66"
    "\xb8\xdf\x41\x6e\x9b\x8a\x09\x79\x4d\x69\x35\xf7\x12\xa3\x32"
    "\x46\xc6\x43\x51\xef\x3b\xdb\xad\x21\xcb\xf7\x54\x52\x56\x20"
    "\xcb\x8c\xfa\xcc\x71\x48\xea\xe4\x2b\xfb\x4d\x12\x90\x12\xc6"
    "\xf7\xed\x1f\xee\x95\xa1\x3f\xcc\x95\x78\x74\xcf\x55\x91\xb7"
    "\x9f\x4e\xfc\xe6\x28\x44\x27\x5f\x86\xe1\xde\xf3\x20\xe9\x40"
    "\x07\x90\x24\x00\x7d\x17\xaa\x16\xc1\x9f\xc5\x51\x82\xaa\x5c"
    "\xe0\x42\xac\xe5\x7f\xe9\xaf\xaa\x46\x47\xb6\x76\x80\x3e\x03"
    "\xbc\xe8\xc1\x05\x90\xcc\xd0\x48\x79\xa9\x0e\xab\xcb\x18\x51"
    "\x2a\xa5\xdb\x1c\x6b\xa9\xfc\xd2\xea\x89\xae\xab\xe3\x9c\x3f"
    "\x6b\x03\xc7\x98\xac\x43";

// RSA
const unsigned char   Enc_SenderModulus[ENC_SIGNATURE_CHARS] =
    "\x00\xa2\x79\xf4\x8f\xe4\x08\x9d\x96\x13\x09\x66\x31\x6f\x56"
    "\x48\x78\x2c\xaa\xba\x8d\x01\x05\x6f\x41\xb2\xba\x63\x6a\x7a"
    "\x8c\x1f\x54\x33\x31\xc3\x0f\xa0\xe7\x30\x35\x36\x09\x51\x6f"
    "\x6d\xdd\xaf\xe5\x35\xc9\xb9\x6e\x16\x73\xa6\x30\x15\xff\xad"
    "\x86\xaf\xc3\xf4\x6c\x8d\x4a\x76\xe5\xb6\x4e\xe4\x8f\x60\x12"
    "\x46\xc0\xcd\x42\x65\x04\x58\x08\xf1\x3a\xa3\xe2\xc9\x1a\xc3"
    "\x3c\x71\x81\xe9\x20\xff\x7a\xc0\xff\x8e\x24\x44\x34\x6e\x5a"
    "\x8f\xfc\x13\x94\xf6\x09\x19\x57\x94\x0a\xec\xcf\xe7\x19\x11"
    "\x96\x1d\x00\xff\x44\x63\xb7\x40\x3c\xa9\xe4\xd2\x51\x42\x0a"
    "\xd4\xc7\x09\xc5\xea\x72\xdb\x6a\xf8\x3b\x0c\x06\x5f\x4f\x67"
    "\xeb\x2b\x53\x07\xa4\x86\xf7";

const unsigned char Enc_ReceiverModulus[ENC_SIGNATURE_CHARS] =
    "\x00\xb2\x20\x91\x91\x03\xe9\x2f\x99\x59\xa3\x65\x80\x2c\xb5"
    "\x25\x03\x03\xaf\xe9\x3c\x42\x13\x07\xc2\x5e\x15\x1b\x21\x09"
    "\x9e\x31\xcb\xef\xaf\x19\xa7\xda\x52\xfc\x8c\x01\x2b\x53\x4e"
    "\xee\x53\x2d\x31\xa6\xe5\x3c\x26\xbc\x61\x9e\x38\x86\x74\xc1"
    "\x44\xf9\xb1\x9c\x87\x18\x9f\x58\x3d\x0c\x00\x58\x83\xaa\x5c"
    "\x77\xe1\xd2\x5d\x04\x8c\x00\xb6\x24\x91\x66\x15\x6a\xd9\xc1"
    "\xaa\x3e\x02\x99\xb5\x11\xad\xf6\xb4\x73\x77\x91\xda\x4a\xb2"
    "\xb6\xa5\x3c\xda\xcd\x2f\xaa\xc9\x47\x51\x20\xf2\x87\xe3\xbe"
    "\x3b\xf5\x8f\x15\x63\xb4\xc1\xb0\xb0\x22\x51\xf0\x4b\xd4\x1c"
    "\x50\x91\xa8\x5b\x8f\x09\x55\x5d\x46\x65\x41\xa7\x4e\xab\x5f"
    "\x4c\xf1\x86\x05\x55\xdf\x83";

const unsigned char      Enc_PublicExp[ENC_PUBLIC_KEY_CHARS] =
    "\x01\x00\x01";

// Keys
void _calculateSymmetricKey(digit_t *key, digit_t *modExpResult, digit_t *secret) {
    digit_t prime[ENC_PRIVATE_KEY_DIGITS];

    mpConvFromOctets(prime, ENC_PRIVATE_KEY_DIGITS, Enc_Prime, ENC_PRIVATE_KEY_CHARS);
    mpModExp(key, modExpResult, secret, prime, ENC_PRIVATE_KEY_DIGITS);
}

void _deriveKeys(uint8_t *aesKey, uint8_t *hashKey, uint8_t *CTRNonce, digit_t *symmetricKey) {
    unsigned char i = 0;

    uint8_t hashMessage[ENC_PRIVATE_KEY_CHARS];
    uint8_t hashResult[ENC_HASH_CHARS];

    mpConvToOctets(symmetricKey, ENC_PRIVATE_KEY_DIGITS, hashMessage, ENC_PRIVATE_KEY_CHARS);
    _hash(hashResult, hashMessage, ENC_HASH_CHARS, ENC_PRIVATE_KEY_CHARS);
	for(i = 0; i<ENC_PRIVATE_KEY_CHARS; i++) {
		hashMessage[i] = hashResult[i];
	}
	for(i = 0; i < ENC_HASH_CHARS/2; i++)
		aesKey[i] = hashResult[i];
	for(i = 0; i < ENC_HASH_CHARS/2; i++)
		hashKey[i] = hashResult[i+ENC_HASH_CHARS/2];
	_hash(hashResult, hashMessage, ENC_HASH_CHARS, ENC_PRIVATE_KEY_CHARS);
	for(i = 0; i < ENC_CTR_NONCE_CHARS; i++) {
		CTRNonce[i] = hashResult[i];
	}

}

// Hashes
void _hash(uint8_t *hash, uint8_t *data, unsigned hashLength, unsigned dataLength) {
    struct sha3_256_ctx ctx;

    sha3_256_init(&ctx);
    sha3_256_update(&ctx, dataLength, data);
    sha3_256_digest(&ctx, hashLength, hash);
}

void _hmac(uint8_t *hmac, uint8_t *data, uint8_t *key, unsigned hashLength, unsigned dataLength, unsigned keyLength) {
    unsigned i;

    uint8_t innerPad[SHA3_256_DATA_SIZE];
    uint8_t outerPad[SHA3_256_DATA_SIZE];
    uint8_t zeroPaddedKey[SHA3_256_DATA_SIZE];
    uint8_t paddedKey[SHA3_256_DATA_SIZE];
    uint8_t innerHashMessage[SHA3_256_DATA_SIZE+dataLength];
    uint8_t outerHashMessage[SHA3_256_DATA_SIZE+ENC_HASH_CHARS];
    uint8_t hashResult[ENC_HASH_CHARS];

    // Padding Strings
    for (i = 0; i < SHA3_256_DATA_SIZE; i++)
        innerPad[i] = 0x36;
    for (i = 0; i < SHA3_256_DATA_SIZE; i++)
        outerPad[i] = 0x5c;

    // Inner Padding
    for (i = 0; i < keyLength; i++)
        zeroPaddedKey[i] = key[i];
    for (i = 0; i < SHA3_256_DATA_SIZE; i++)
        paddedKey[i] = zeroPaddedKey[i] ^ innerPad[i];

    // Append Data
    for (i = 0; i < SHA3_256_DATA_SIZE; i++)
        innerHashMessage[i] = paddedKey[i];
    for (i = 0; i < dataLength; i++)
        innerHashMessage[SHA3_256_DATA_SIZE+i] = data[i];

    _hash(hashResult, innerHashMessage, ENC_HASH_CHARS, SHA3_256_DATA_SIZE+dataLength);

    // Outer Padding
    for (i = 0; i < SHA3_256_DATA_SIZE; i++)
        paddedKey[i] = zeroPaddedKey[i] ^ outerPad[i];

    // Append Hash
    for (i = 0; i < SHA3_256_DATA_SIZE; i++)
        outerHashMessage[i] = paddedKey[i];
    for (i = 0; i < ENC_HASH_CHARS; i++)
        outerHashMessage[SHA3_256_DATA_SIZE+i] = hashResult[i];

    _hash(hmac, outerHashMessage, ENC_HASH_CHARS, SHA3_256_DATA_SIZE+ENC_HASH_CHARS);
}

// Signatures
void _sign(digit_t *signature, digit_t *message, digit_t *privateExponent, digit_t *modulus) {
    mpModExp(signature, message, privateExponent, modulus, ENC_SIGNATURE_DIGITS);
}

int _verify(digit_t *signature, digit_t *message, digit_t *publicExponent, digit_t *modulus) {
    digit_t modExpResult[ENC_SIGNATURE_DIGITS];

    mpModExp(modExpResult, signature, publicExponent, modulus, ENC_SIGNATURE_DIGITS);
    if (mpEqual(modExpResult, message, ENC_SIGNATURE_DIGITS)) {
        printf("----> Verification Successful\n");
        return ENC_SIGNATURE_ACCEPTED;
    }

    printf("----> Verification Failed\n");
    return ENC_SIGNATURE_REJECTED;
}