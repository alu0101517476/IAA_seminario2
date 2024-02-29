#include <cstdio>
#include "./smile/smile.h"
#include "smile_license.h" // your licensing key

int main() {
  DSL_errorH().RedirectToFile(stdout);

  DSL_network net;
  int res = net.ReadFile("VentureBN.xdsl");
  if (DSL_OKAY != res) {
    return res;
  }
  net.GetNode("Forecast")->Val()->SetEvidence("Moderate");
  net.UpdateBeliefs();
  DSL_node* sn = net.GetNode("Success");
  const DSL_Dmatrix& beliefs = *sn->Val()->GetMatrix();
  const DSL_idArray& outcomes = *sn->Def()->GetOutcomeIds();
  for (int i = 0; i < outcomes.GetSize(); i++)
  {
  printf("%s=%g\n", outcomes[i], beliefs[i]);
  }
  return DSL_OKAY;
}