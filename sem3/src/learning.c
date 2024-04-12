#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum STATE{
  Atacar,
  Recoger_Armas,
  Recoger_Energia,
  Explorar,
  Huir,
  Detectar_Peligro
};

enum HEALTH {
  Baja,
  Alta
};

enum YESNO {
  si,
  no
};

enum WEAPON {
  armado,
  desarmado
};

// Get info for tables from line of input
void healthCheckLine(float table[2][6], char* line);
void hearNoiseCheckLine(float table[2][6], char* line);
void nearEnemiesCheckLine(float table[2][6], char* line);
void opponentWeaponCheckLine(float table[2][6], char* line);
void closeHealthCheckLine(float table[2][6], char* line);
void closeWeaponCheckLine(float table[2][6], char* line);
void stCheckLine(float table[6], char* line);
void st1CheckLine(float table[6][6], char* line);
void weaponCheckLine(float table[2][6], char* line);

// Operations on tables
void normalizeTable(int n, int m, float table[n][m]);
void normalizeColumn(int n, float table[n]);
void printTable(int n, int m, float table[n][m], char* row_names[n], char* column_names[m]);
void printColumn(int n, float table[n], char* row_names[n]);

int main(int argc, char** argv) {
  long time_took = clock();

  float health_table[2][6] = {{0}};
  float hear_noise_table[2][6] = {{0}};
  float near_enemies_table[2][6] = {{0}};
  float opponent_weapon_table[2][6] = {{0}};
  float close_health_table[2][6] = {{0}};
  float close_weapon_table[2][6] = {{0}};
  float st_table[6] = {0};
  float st_1_table[6][6] = {{0}};
  float weapon_table[2][6] = {{0}};

  FILE* input;
  input = fopen("data.txt", "r");
  char* line = malloc(70);
  unsigned long line_size = 70;
  getline(&line, &line_size, input);
  getline(&line, &line_size, input);

  while (!feof(input)) {
    healthCheckLine(health_table, line);
    hearNoiseCheckLine(hear_noise_table, line);
    nearEnemiesCheckLine(near_enemies_table, line);
    opponentWeaponCheckLine(opponent_weapon_table, line);
    closeHealthCheckLine(close_health_table, line);
    closeWeaponCheckLine(close_weapon_table, line);
    stCheckLine(st_table, line);
    st1CheckLine(st_1_table, line);
    weaponCheckLine(weapon_table, line);
    getline(&line, &line_size, input);
  }
  fclose(input);

  char* state_names[6] = {"Atac", "RecArm", "RecEng", "Exp", "Huir", "DetPel"};
  char* health_names[2] = {"Alta", "Baja"};
  char* yes_no_names[2] = {"yes", "no"};
  char* weapon_names[2] = {"armado", "desarm"};

  normalizeTable(2, 6, health_table);
  normalizeTable(2, 6, hear_noise_table);
  normalizeTable(2, 6, near_enemies_table);
  normalizeTable(2, 6, opponent_weapon_table);
  normalizeTable(2, 6, close_health_table);
  normalizeTable(2, 6, close_weapon_table);
  normalizeColumn(6, st_table);
  normalizeTable(6, 6, st_1_table);
  normalizeTable(2, 6, weapon_table);

  printf("\nHEALTH:\n");
  printTable(2, 6, health_table, health_names, state_names);
  printf("\nHEAR NOISE:\n");
  printTable(2, 6, hear_noise_table, yes_no_names, state_names);
  printf("\nNEAR ENEMIES:\n");
  printTable(2, 6, near_enemies_table, yes_no_names, state_names);
  printf("\nOPPONENT WEAPON:\n");
  printTable(2, 6, opponent_weapon_table, weapon_names, state_names);
  printf("\nCLOSE HEALTH PACK:\n");
  printTable(2, 6, close_health_table, yes_no_names, state_names);
  printf("\nCLOSE WEAPON:\n");
  printTable(2, 6, close_weapon_table, yes_no_names, state_names);
  printf("\nST:\n");
  printColumn(6, st_table, state_names);
  printf("\nST+1:\n");
  printTable(6, 6, st_1_table, state_names, state_names);
  printf("\nWEAPON:\n");
  printTable(2, 6, weapon_table, weapon_names, state_names);

  time_took = (clock() - time_took);
  printf("\n\nTook: %f seconds\n", (double)time_took / CLOCKS_PER_SEC);
}

void normalizeTable(int n, int m, float table[n][m]) {
  for (int j = 0; j < m; j++) {
    int count = 0;
    for (int i = 0; i < n; i++) {
      count += (int)table[i][j];
    }
    for (int i = 0; i < n; i++) {
      table[i][j] = table[i][j] / (float)count;
    }
  }
}

void normalizeColumn(int n, float table[n]) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    count += (int)table[i];
  }
  for (int i = 0; i < n; i++) {
    table[i] = table[i] / (float)count;
  }
}

void printTable(int n, int m, float table[n][m], char* row_names[n], char* column_names[m]) {
  printf("\t");
  for (int j = 0; j < m; j++) {
    printf("%-6s\t", column_names[j]);
  }
  puts("\n");
  for (int i = 0; i < n; i++) {
    printf("%-6s\t", row_names[i]);
    for (int j = 0; j < m; j++) {
      printf("%.3f\t", table[i][j]);
    }
    puts("\n");
  }
}

void printColumn(int n, float table[n], char* names[n]) {
  for (int i = 0; i < n; i++) {
    printf("%-6s\t%.3f\n", names[i], table[i]);
  }
  puts("");
}

void checkLine(int n, int m, float table[n][m], char* rownames[n], char* colnames[m], int offset1, int offset2, char* line) {
  regex_t regex;
  regmatch_t match;
  char regex_str[50];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      sprintf(regex_str, "^(\\w*?,){%d}%s(,\\w*?){%d},%s", offset1, rownames[i], offset2, colnames[j]);
      regcomp(&regex, regex_str, REG_EXTENDED);
      if (!regexec(&regex, line, 1, &match, 0)) {
        table[i][j]++;
        return;
      }
    }
  }
}

void healthCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"Baja", "Alta"};
  checkLine(2, 6, table, row_names, state_names, 0, 6, line);
}

void hearNoiseCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"si", "no"};
  checkLine(2, 6, table, row_names, state_names, 1, 5, line);
}

void nearEnemiesCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"si", "no"};
  checkLine(2, 6, table, row_names, state_names, 2, 4, line);
}

void opponentWeaponCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"armado", "desarmado"};
  checkLine(2, 6, table, row_names, state_names, 3, 3, line);
}
void closeHealthCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"si", "no"};
  checkLine(2, 6, table, row_names, state_names, 4, 2, line);
}
void closeWeaponCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"si", "no"};
  checkLine(2, 6, table, row_names, state_names, 5, 1, line);
}
void stCheckLine(float table[6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  regex_t regex;
  regmatch_t match;
  char regex_str[50];
  for (int i = 0; i < 6; i++) {
    sprintf(regex_str, "^(\\w*?,){%d}%s", 6, state_names[i]);
    regcomp(&regex, regex_str, REG_EXTENDED);
    if (!regexec(&regex, line, 1, &match, 0)) {
      table[i]++;
      return;
    }
  }
}
void st1CheckLine(float table[6][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  regex_t regex;
  regmatch_t match;
  char regex_str[50];
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
      sprintf(regex_str, "%s,%s", state_names[j], state_names[i]);
      regcomp(&regex, regex_str, REG_EXTENDED);
      if (!regexec(&regex, line, 1, &match, 0)) {
        table[i][j]++;
        return;
      }
    }
  }
}
void weaponCheckLine(float table[2][6], char* line) {
  char* state_names[6] = {"Atacar", "Recoger_Armas", "Recoger_Energia", "Explorar", "Huir", "Detectar_Peligro"};
  char* row_names[2] = {"armado", "desarmado"};
  regex_t regex;
  regmatch_t match;
  char regex_str[50];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 6; j++) {
      sprintf(regex_str, "%s,%s", state_names[j], row_names[i]);
      regcomp(&regex, regex_str, REG_EXTENDED);
      if (!regexec(&regex, line, 1, &match, 0)) {
        table[i][j]++;
        return;
      }
    }
  }
}


