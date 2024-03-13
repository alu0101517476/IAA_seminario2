#include <iostream>
#include <string>
#include <vector>
#include "./smile/smile.h"
#include "smile_license.h" // your licensing key

/**
 * Translates an initial to its full name
 * @param initials The initial to translate
 * @returns The full name
*/
std::string InitialsToFullName(std::string initials) {
  if (initials == "AT" || initials == "Attack") {
    return "Attack";
  } else if (initials == "SW" || initials == "Search_Weapon") {
    return "Search_Weapon";
  } else if (initials == "SH" || initials == "Search_Health") {
    return "Search_Health";
  } else if (initials == "EX" || initials == "Explore") {
    return "Explore";
  } else if (initials == "FL" || initials == "Flee") {
    return "Flee";
  } else if (initials == "DD" || initials == "Detect_Danger") {
    return "Detect_Danger";
  } else if (initials == "LO" || initials == "Low") {
    return "Low";
  } else if (initials == "HI" || initials == "High") {
    return "High";
  } else if (initials == "HA" || initials == "Have") {
    return "Have";
  } else if (initials == "H" || initials == "Has") {
    return "Has";
  } else if (initials == "Y" || initials == "Yes") {
    return "Yes";
  } else if (initials == "N" || initials == "No") {
    return "No";
  } else if (initials == "DNTH" || initials == "Dont_have") {
    return "Dont_have";
  } else if (initials == "DSTH" || initials == "Doesnt_have") {
    return "Doesnt_have";
  } else if (initials == "NE" || initials == "No_Evidence") {
    return "No_Evidence";
  } else {
    std::cout << "ERROR: Invalid option" << std::endl;
    exit(EXIT_FAILURE);
  }
}

/**
 * Sets evidences for each value of the network
 * @param net The net of which values to set evidences
*/
void initializeNetValues(DSL_network& net) {
  DSL_idArray id_nodos;
  net.GetAllNodeIds(id_nodos);
  std::string input;
  for (const auto& i : id_nodos) {
    const char *const id = i;
    if (strcmp(i, "ST_1") != 0) {
      std::cout << i << " [";
      int size = net.GetNode(i)->Def()->GetOutcomeIds()[0].GetSize();
      for (int j{0}; j < (size - 1); ++j) {
        std::cout << net.GetNode(i)->Def()->GetOutcomeIds()[0][j]  << " / ";
      }
      std::cout << net.GetNode(i)->Def()->GetOutcomeIds()[0][size - 1] << "]: " <<  std::endl;
      std::cin >> input;
      std::string new_input = InitialsToFullName(input);
      std::cout << "Chosen: " << new_input << '\n';
      if (new_input != "No_Evidence")
      net.GetNode(i)->Val()->SetEvidence(new_input.c_str());
    }
  }
}

/**
 * Calculates the state when time tends to infinite and prints it
 * @param net The net
*/
void STInfinite(DSL_network& net) {
  std::string resulting_state = "";
  double resulting_probability = 0;
  while (true) {
    net.GetNode("ST")->Val()->SetEvidence(resulting_state.c_str());
    net.UpdateBeliefs();
    DSL_node* st_1 = net.GetNode("ST_1");
    const DSL_Dmatrix& beliefs = *st_1->Val()->GetMatrix();
    const DSL_idArray& outcomes = *st_1->Def()->GetOutcomeIds();
    double max_probability = 0;
    std::string max_probability_state = "";
    for (int i = 0; i < outcomes.GetSize(); i++) {
      if (beliefs[i] > max_probability) {
        max_probability = beliefs[i];
        resulting_probability = beliefs[i];
        max_probability_state = outcomes[i];
      }
    }
    if (resulting_state == max_probability_state) {
      break;
    }
    resulting_state = max_probability_state;
  }
  std::cout << "Tending to infinite state: " << resulting_state << " with a probability of: " << resulting_probability << std::endl;
}

/**
 * Calculates the probability of each state
 * @param net The net
*/
void NextST(DSL_network& net) {
  net.UpdateBeliefs();
  DSL_node* st_1 = net.GetNode("ST_1");
  const DSL_Dmatrix& beliefs = *st_1->Val()->GetMatrix();
  const DSL_idArray& outcomes = *st_1->Def()->GetOutcomeIds();
  double max_probability = 0;
  std::string max_probability_state = "";
  for (int i = 0; i < outcomes.GetSize(); i++) {
    printf("%s=%g\n", outcomes[i], beliefs[i]);
  }
}

/**
 * Main
*/
int main() {
  DSL_errorH().RedirectToFile(stdout);
  
  DSL_network net;
  int res = net.ReadFile("BOT_2.0.xdsl");
  // No hay fallos en la red
  if (DSL_OKAY != res) { 
    return res;
  }
  std::cout << "Enter values ​​for the following variables:" << std::endl;
  initializeNetValues(net);
  std::cout << "\nProbability of the next State:\n";
  NextST(net);
  std::cout << "\nProbability of the next State when time tends to infinite:\n";
  STInfinite(net);
  return DSL_OKAY; 
}