#include <iostream>
#include <string>
#include <vector>
#include "./smile/smile.h"
#include "smile_license.h" // your licensing key

// Compilar: g++ -DNDEBUG -O3 main.cpp -I./smile -L./smile -lsmile

void inicializarValoresRed(DSL_network& net) {
  DSL_idArray id_nodos;
  net.GetAllNodeIds(id_nodos);
  std::string input;
  for (const auto& i : id_nodos) {
    const char *const id = i;
    if (i != "ST_1") {
      std::cout << i << " [";
      int size = net.GetNode(i)->Def()->GetOutcomeIds()[0].GetSize();
      for (int j{0}; j < (size - 1); ++j) {
        std::cout << net.GetNode(i)->Def()->GetOutcomeIds()[0][j]  << " / ";
      }
      std::cout << net.GetNode(i)->Def()->GetOutcomeIds()[0][size - 1] << "]: " <<  std::endl;
      std::cin >> input;
      net.GetNode(i)->Val()->SetEvidence(input.c_str());
    }
  }
}

int main() {
  DSL_errorH().RedirectToFile(stdout);

  DSL_network net;
  int res = net.ReadFile("BOT_2.0.xdsl");
  // No hay fallos en la red
  if (DSL_OKAY != res) { 
    return res;
  }
  std::cout << "Introduzca valores para las siguientes variables:" << std::endl;
  inicializarValoresRed(net);
  net.UpdateBeliefs();
  DSL_node* st_1 = net.GetNode("ST_1");
  const DSL_Dmatrix& beliefs = *st_1->Val()->GetMatrix();
  const DSL_idArray& outcomes = *st_1->Def()->GetOutcomeIds();
  for (int i = 0; i < outcomes.GetSize(); i++) {
    printf("%s=%g\n", outcomes[i], beliefs[i]);
  }
  return DSL_OKAY; 
}