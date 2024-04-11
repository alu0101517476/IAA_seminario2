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

void healthCheckLine(float table[2][6], char* line);
void hearNoiseCheckLine(float table[2][6], char* line);
void nearEnemiesCheckLine(float table[2][6], char* line);
void opponentWeaponCheckLine(float table[2][6], char* line);
void closeHealthCheckLine(float table[2][6], char* line);
void closeWeaponCheckLine(float table[2][6], char* line);
void stCheckLine(float table[6], char* line);
void st1CheckLine(float table[6][6], char* line);
void weaponCheckLine(float table[2][6], char* line);

void normalizeTable(int n, int m, float table[n][m]);
void printTable(int n, int m, float table[n][m]);

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

  printf("HEALTH:\n");
  normalizeTable(2, 6, health_table);
  printTable(2, 6, health_table);

  printf("HEAR NOISE:\n");
  normalizeTable(2, 6, hear_noise_table);
  printTable(2, 6, hear_noise_table);

  printf("NEAR ENEMIES:\n");
  normalizeTable(2, 6, near_enemies_table);
  printTable(2, 6, near_enemies_table);

  printf("OPPONENT WEAPON:\n");
  normalizeTable(2, 6, opponent_weapon_table);
  printTable(2, 6, opponent_weapon_table);

  printf("CLOSE HEALTH PACK:\n");
  normalizeTable(2, 6, close_health_table);
  printTable(2, 6, close_health_table);

  printf("CLOSE WEAPON:\n");
  normalizeTable(2, 6, close_weapon_table);
  printTable(2, 6, close_weapon_table);
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

void printTable(int n, int m, float table[n][m]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%2.3f\t", table[i][j]);
    }
    puts("\n");
  }
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

void nearEnemiesCheckLine(float table[2][6], char* line){}
void opponentWeaponCheckLine(float table[2][6], char* line){}
void closeHealthCheckLine(float table[2][6], char* line){}
void closeWeaponCheckLine(float table[2][6], char* line){}
void stCheckLine(float table[6], char* line){}
void st1CheckLine(float table[6][6], char* line){}
void weaponCheckLine(float table[2][6], char* line){}


