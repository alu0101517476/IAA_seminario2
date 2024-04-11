#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

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

  printf("\nHEALTH:\n");
  normalizeTable(2, 6, health_table);
  printTable(2, 6, health_table, health_names, state_names);

  printf("\nHEAR NOISE:\n");
  normalizeTable(2, 6, hear_noise_table);
  printTable(2, 6, hear_noise_table, yes_no_names, state_names);

  printf("\nNEAR ENEMIES:\n");
  normalizeTable(2, 6, near_enemies_table);
  printTable(2, 6, near_enemies_table, yes_no_names, state_names);

  printf("\nOPPONENT WEAPON:\n");
  normalizeTable(2, 6, opponent_weapon_table);
  printTable(2, 6, opponent_weapon_table, weapon_names, state_names);

  printf("\nCLOSE HEALTH PACK:\n");
  normalizeTable(2, 6, close_health_table);
  printTable(2, 6, close_health_table, yes_no_names, state_names);

  printf("\nCLOSE WEAPON:\n");
  normalizeTable(2, 6, close_weapon_table);
  printTable(2, 6, close_weapon_table, yes_no_names, state_names);

  printf("\nST:\n");
  normalizeColumn(6, st_table);
  printColumn(6, st_table, state_names);

  printf("\nST+1:\n");
  normalizeTable(6, 6, st_1_table);
  printTable(6, 6, st_1_table, state_names, state_names);

  printf("\nWEAPON:\n");
  normalizeTable(2, 6, weapon_table);
  printTable(2, 6, weapon_table, weapon_names, state_names);
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

void healthCheckLine(float table[2][6], char* line) {
  regex_t regex;
  regmatch_t match;
  regcomp(&regex, "^Alta(,\\w*?){6},Atacar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Alta][Atacar]++;
    return;
  }
  regcomp(&regex, "^Alta(,\\w*?){6},Recoger_Armas", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Alta][Recoger_Armas]++;
    return;
  }
  regcomp(&regex, "^Alta(,\\w*?){6},Recoger_Energia", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Alta][Recoger_Energia]++;
    return;
  }
  regcomp(&regex, "^Alta(,\\w*?){6},Explorar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Alta][Explorar]++;
    return;
  }
  regcomp(&regex, "^Alta(,\\w*?){6},Huir", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Alta][Huir]++;
    return;
  }
  regcomp(&regex, "^Alta(,\\w*?){6},Detectar_Peligro", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Alta][Detectar_Peligro]++;
    return;
  }
  regcomp(&regex, "^Baja(,\\w*?){6},Atacar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Baja][Atacar]++;
    return;
  }
  regcomp(&regex, "^Baja(,\\w*?){6},Recoger_Armas", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Baja][Recoger_Armas]++;
    return;
  }
  regcomp(&regex, "^Baja(,\\w*?){6},Recoger_Energia", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Baja][Recoger_Energia]++;
    return;
  }
  regcomp(&regex, "^Baja(,\\w*?){6},Explorar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Baja][Explorar]++;
    return;
  }
  regcomp(&regex, "^Baja(,\\w*?){6},Huir", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Baja][Huir]++;
    return;
  }
  regcomp(&regex, "^Baja(,\\w*?){6},Detectar_Peligro", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[Baja][Detectar_Peligro]++;
    return;
  }
}

void hearNoiseCheckLine(float table[2][6], char* line) {
  regex_t regex;
  regmatch_t match;
  regcomp(&regex, "^(\\w*?,){1}si(,\\w*?){5},Atacar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Atacar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}si(,\\w*?){5},Recoger_Armas", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Recoger_Armas]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}si(,\\w*?){5},Recoger_Energia", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Recoger_Energia]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}si(,\\w*?){5},Explorar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Explorar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}si(,\\w*?){5},Huir", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Huir]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}si(,\\w*?){5},Detectar_Peligro", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Detectar_Peligro]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}no(,\\w*?){5},Atacar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Atacar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}no(,\\w*?){5},Recoger_Armas", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Recoger_Armas]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}no(,\\w*?){5},Recoger_Energia", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Recoger_Energia]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}no(,\\w*?){5},Explorar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Explorar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}no(,\\w*?){5},Huir", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Huir]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){1}no(,\\w*?){5},Detectar_Peligro", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Detectar_Peligro]++;
    return;
  }
}

void nearEnemiesCheckLine(float table[2][6], char* line) {
  regex_t regex;
  regmatch_t match;
  regcomp(&regex, "^(\\w*?,){2}si(,\\w*?){4},Atacar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Atacar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}si(,\\w*?){4},Recoger_Armas", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Recoger_Armas]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}si(,\\w*?){4},Recoger_Energia", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Recoger_Energia]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}si(,\\w*?){4},Explorar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Explorar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}si(,\\w*?){4},Huir", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Huir]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}si(,\\w*?){4},Detectar_Peligro", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[si][Detectar_Peligro]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}no(,\\w*?){4},Atacar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Atacar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}no(,\\w*?){4},Recoger_Armas", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Recoger_Armas]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}no(,\\w*?){4},Recoger_Energia", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Recoger_Energia]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}no(,\\w*?){4},Explorar", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Explorar]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}no(,\\w*?){4},Huir", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Huir]++;
    return;
  }
  regcomp(&regex, "^(\\w*?,){2}no(,\\w*?){4},Detectar_Peligro", REG_EXTENDED);
  if (!regexec(&regex, line, 1, &match, 0)) {
    table[no][Detectar_Peligro]++;
    return;
  }
}

void opponentWeaponCheckLine(float table[2][6], char* line) {
}
void closeHealthCheckLine(float table[2][6], char* line) {
}
void closeWeaponCheckLine(float table[2][6], char* line) {
}
void stCheckLine(float table[6], char* line) {
}
void st1CheckLine(float table[6][6], char* line) {
}
void weaponCheckLine(float table[2][6], char* line) {
}


