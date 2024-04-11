#include <stdio.h>

/**
  * cada funcion checkea un regexp con el q matchea
  * contra la linea q le pasas
  * y añade valores a sus tablas respectivamente
  *
  * luego de eso normalizar las tablas e imprimirlas ez pz
  */
void healthCheckLine(float** table, char* line);
void hearNoiseCheckLine(float** table, char* line);
void nearEnemiesCheckLine(float** table, char* line);
void opponentWeaponCheckLine(float** table, char* line);
void closeHealthCheckLine(float** table, char* line);
void closeWeaponCheckLine(float** table, char* line);
void stCheckLine(float* table, char* line);
void st1CheckLine(float* table, char* line);
void weaponCheckLine(float** table, char* line);

int main(int argc, char** argv) {
  float health_table[2][6];
  float hear_noise_table[2][6];
  float near_enemies_table[2][6];
  float opponent_weapon_table[2][6];
  float close_health_table[2][6];
  float close_weapon_table[2][6];
  float st_table[6];
  float st_1_table[6][6];
  float weapon_table[2][6];

  FILE* input;
  input = fopen(argv[1], "r");

  char* header;
  unsigned long header_size = 60;
  getline(&header, &header_size, input);

  fclose(input);
}

void healthCheckLine(float** table, char* line) {

}
