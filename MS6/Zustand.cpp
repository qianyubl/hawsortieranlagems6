#include "Zustand.h"
#include "Z1_BandSteht.h"
#include "Z2_KeinWSImEinlauf.h"
#include "Z3_KeinWsImAuslauf.h"
#include "Z4_Hoehenmessung.h"
#include "Z5_WsNichtInWeiche.h"
#include "Z6_RutscheVoll.h"
#include "Z6_RutscheNichtVoll.h"
#include "Z7_MetallMessung.h"
#include "Z8_BandFrei.h"
#include "HardwareLayer.h"




/**
 * Zustand is constructor
 * 
 */
Zustand::Zustand() {}

/**
 * ~Zustand is destructor
 * 
 */
Zustand::~Zustand() {}

/**
 * returnFromErrorState
 * 
 */
void Zustand::returnFromErrorState(){}


/**
 * wsImEinlauf
 * 
 */
void Zustand::wsImEinlauf(int flanke){}

/**
 * wsInHoehenMessung
 * 
 */
void Zustand::wsInHoehenMessung(int flanke){}

/**
 * hoeheBereich1 
 * 
 */
void Zustand::hoeheBereich1(int flanke){}

/**
 * wsInWeiche 
 * 
 */
void Zustand::wsInWeiche(int flanke){}

/**
 * wsMetall 
 * 
 */
void Zustand::wsMetall(int flanke){}

/**
 * weicheOffen 
 * 
 */
void Zustand::weicheOffen(int flanke){}

/**
 * rutscheVoll 
 * 
 */
void Zustand::rutscheVoll(int flanke){}

/**
 * wsImAuslauf 
 * 
 */
void Zustand::wsImAuslauf(int flanke){}

/**
 * tasteStart 
 * 
 */
void Zustand::tasteStart(){}

/**
 * tasteStop 
 * 
 */
void Zustand::tasteStop(){}

/**
 * tasteReset 
 * 
 */
void Zustand::tasteReset(){}

/**
 * tasteEStop 
 * 
 */
void Zustand::tasteEStop(int flanke){}

/**
 * band2Frei 
 * 
 */
void Zustand::band2Frei(){}

/**
 * band2Belegt 
 * 
 */
void Zustand::band2Belegt(){}

/**
 * fehler 
 * 
 */
void Zustand::fehler(){}

/**
 * fehlerWeg 
 * 
 */
void Zustand::fehlerWeg(){}

/**
 * timerAbgelaufen 
 * 
 */
void Zustand::timerAbgelaufen(){}

/**
 * wsKommtVonBand1 
 * 
 */
void Zustand::wsKommtVonBand1(){}

/**
 * wsVomBandRunter  
 * 
 */
void Zustand::wsVomBandRunter (){}

/**
 * WsVerschwunden 
 * 
 */
void Zustand::WsVerschwunden(){}
