#include <vector>

#include "interface/RTJet.h"
#include "interface/RTLepton.h"
#include "interface/RTEvent.h"

#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ namespace rt;

#pragma link C++ class rt::Jet+;
#pragma link C++ class rt::Lepton+;
#pragma link C++ class std::vector<rt::Jet>;
#pragma link C++ class std::vector<rt::Lepton>;

#pragma link C++ class rt::Event+;

#endif
