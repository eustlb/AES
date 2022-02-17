#ifndef AES_H

#define AES_H
#define DATA_SIZE 16 
#define STATE_ROW_SIZE 4 
#define STATE_COL_SIZE 4 
#define ROUND_COUNT 10 
#include <stdint.h>
#include <stdio.h>

// the round that will trigger
extern uint8_t targeted_round;

static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

static const uint8_t Rcon[4][10] = {
  0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static const uint8_t master_key [STATE_ROW_SIZE][STATE_COL_SIZE] = {
  0x2b, 0x28, 0xab, 0x09,
  0x7e, 0xae, 0xf7, 0xcf, 
  0x15, 0xd2, 0x15, 0x4f, 
  0x16, 0xa6, 0x88, 0x3c };

void AESEncrypt(uint8_t ciphertext[DATA_SIZE], uint8_t plaintext[DATA_SIZE] , uint8_t key[
DATA_SIZE]){

	};

void copyArray2D(uint8_t arr [STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t copy [STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t size) {
   for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) { 
         copy[i][j] = arr[i][j];
      }
   }
}

void AddRoundKey( uint8_t state [STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t roundkey [
STATE_ROW_SIZE][STATE_COL_SIZE]);

void SubBytes(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]){
   uint8_t i, j; 
   for (i = 0; i < STATE_ROW_SIZE; ++i){
      for (j = 0; j < STATE_COL_SIZE; ++j){
         // we store the value to be changed in the variable val
         uint8_t val = state[i][j]; 
         // Sbox value are sorted from 0 to 255 (right to left, top to down). 
         // Therefore, when we have to change a value to its corresponding Sbox value, we need to convert the line and column numbers given by the value
         // (e.g. the value 0x7b corresponds to line 7 column b Sbox value) to the number between 0 and 255 corresponding according to how the Sbox values
         // are sorted.
         // To do so, lets firt get the line (variable l) and column (variable c) numbers corresponding to the state value
         uint8_t l, c;
         c = val%16;
         l = (val-c)/16;
         // Then, we convert it to a number between 0 and 255 (Sbox value are sorted from 0 to 255).
         uint8_t num = l*16+c;
         // Now, we can change the value to its Sbox corresponding value
         state[i][j] = sbox[num];
      }
   }
};

void ShiftRows(uint8_t state[STATE_ROW_SIZE][STATE_COL_SIZE]);

void MixColumns(uint8_t state [STATE_ROW_SIZE][STATE_COL_SIZE]);

void KeyGen(uint8_t roundkeys [10][STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t master_key [STATE_ROW_SIZE][STATE_COL_SIZE]){
   uint8_t previous_key [STATE_ROW_SIZE][STATE_COL_SIZE] ;
   copyArray2D(master_key, previous_key, 4) ;
   for (int k=0; k<10; k++) {
      uint8_t new_key [STATE_ROW_SIZE][STATE_COL_SIZE];
      // RotWord
      int i = 0 ;
      do {
         new_key[i][0] = previous_key[i+1][STATE_COL_SIZE-1] ; 
         i=i+1;
      } while ( i <  STATE_ROW_SIZE) ;
      new_key[STATE_ROW_SIZE-1][0] = previous_key[0][STATE_COL_SIZE-1] ;
      // SubByte
      SubBytes(new_key) ; 
      // (first column of previous key) XOR (first column of new key) XOR (k column of Rcon)
      for (int i=0; i<STATE_ROW_SIZE; i++) {
         new_key[i][0] = new_key[i][0] ^ previous_key[i][0] ^ Rcon[i][k];
      }
      // We now have built completely the first colunm of the new key. Let's build the three others.
      // XOR between the other columns of the previous key and the previous column of the new key that we just built
      for (int j=1; j < STATE_COL_SIZE; ++j){
         for (int i=0; i < STATE_ROW_SIZE; ++i){
            new_key[i][j] = new_key[i][j-1] ^ previous_key[i][j];
         }
      }   
      // The new key is now completely built. Let's store it in roundkeys
      for (int i=0; i<STATE_ROW_SIZE; i++){
         for (int j=0; j<STATE_COL_SIZE; j++){
            roundkeys[k][i][j]=new_key[i][j] ;
         }
      } 
      copyArray2D(new_key, previous_key, 4);
   }     
} ;

//fill the first column of a given round key
void ColumnFill(uint8_t roundkeys[][STATE_ROW_SIZE][STATE_COL_SIZE] , int round);

//fill the other 3 columns of a given round key
void OtherColumnsFill(uint8_t roundkeys [][STATE_ROW_SIZE][STATE_COL_SIZE], int round); void GetRoundKey(uint8_t roundkey [STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t roundkeys [][
STATE_ROW_SIZE][STATE_COL_SIZE], int round);

void MessageToState(uint8_t state [STATE_ROW_SIZE][STATE_COL_SIZE], uint8_t message [
DATA_SIZE]);

void StateToMessage(uint8_t message [DATA_SIZE],uint8_t state [STATE_ROW_SIZE][
STATE_COL_SIZE]);

void MCMatrixColumnProduct(uint8_t colonne [STATE_COL_SIZE]); uint8_t gmul(uint8_t a, uint8_t b);

extern extern extern 
#endif

const uint8_t rcon [10]; const uint8_t sboxtab [256]; const uint8_t invsbox [256];