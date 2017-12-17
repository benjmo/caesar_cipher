# Caesar Cipher
Encrypt and decrypt using caesar cipher. Decryption using brute force available.

## Encrypt
`./caesar encrypt|e <filename> <key>`


## Decrypt

### With key ###
`./caesar decrypt|d <filename> <key>`

### Without key ###

`./caesar decrypt|d <filename>`

## Examples

Encrypt `input.txt` with a key (right-shift) of 18

`./caesar e input.txt 18`


Decrypt `input.txt` with a key of 2 (right-shift of 24)

`./caesar d input.txt 2`

Decrypt `input.txt` without knowing key (provides best guess)

`caesar d input.txt`
