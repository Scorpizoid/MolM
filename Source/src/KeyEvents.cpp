#include "MolMContainer.h"
#include <e32math.h>

// ----------------------------------------------------
// CMolMContainer::OfferKeyEventL(const 
//               TKeyEvent& aKeyEvent,TEventCode aType)
// ----------------------------------------------------
//
TKeyResponse 
CMolMContainer::OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    TInt code=aKeyEvent.iCode;
    keyCode = aKeyEvent.iCode;
   number=0;
   

    
   // five-way navigation middle button handler
   if ( aKeyEvent.iScanCode == EStdKeyDevice3)
       {
   /*//x = -16;
   mass();
   DrawNow();
			//BasicBrowserControlL(x, y);
			 */
	formula.Delete(0,255);
		molarMass.Delete(0,255);
	character.Delete(0,255);
	firstLine.Delete(0,255);
	firstLineDisplay.Delete(0,255);
	secondLine.Delete(0,255);
	bracketFormulaMultiplier = 1;
		ekfl=0;
		lastWasADot = 0;
		for (TInt i=0;i<200;i++) {
		displayNumber[i].Zero(); displayFormula[i].Zero(); Pos[i]=0;
		displayDot[i].Zero(); dotPos[i]=0; }

        DrawNow();
			return EKeyWasConsumed;
       }
 
   
    switch (code) 
            { 

      	case EKeySpace:
      		{
      		formula.Delete(0,255);
      		molarMass.Delete(0,255);
     		character.Delete(0,255);
    		firstLine.Delete(0,255);
    		firstLineDisplay.Delete(0,255);
    		secondLine.Delete(0,255);
    		bracketFormulaMultiplier = 1;
      		ekfl=0;
      		lastWasADot = 0;
      		for (TInt i=0;i<200;i++) {
      		displayNumber[i].Zero(); displayFormula[i].Zero(); Pos[i]=0;
      		displayDot[i].Zero(); dotPos[i]=0; }
      		break;
      		}
      	case EKeyEnter:
    	case EKeyLineFeed:
            {
            //x = -16;
            mass();
            DrawNow();
            break;
            }
    	case EKeyBackspace:
            {
	        if (iBrCtlInterface != NULL)
	            {
	            iBrCtlInterface = NULL;
	            DrawNow();
		        break;
	            }
            if (formula.Length() == 0) { break; }
            formula.Delete(formula.Length()-1,1);
            ekfl=ekfl-1;
            if (Pos[ekfl] == 0) { 
				if (ekfl-1 < 0) { displayFormula[0].Zero(); ekfl=0; break; }
				displayFormula[ekfl].Zero();
            }
            if (Pos[ekfl] == 1) { 
				if (ekfl-1 < 0) { displayNumber[0].Zero(); Pos[0] = 0; ekfl=0; break; }
				Pos[ekfl] = 0;
				displayNumber[ekfl].Zero();
            }
            if (dotPos[ekfl] == 1) { 
				if (ekfl-1 < 0) { displayDot[0].Zero(); dotPos[0] = 0;ekfl=0; break; }
				dotPos[ekfl] = 0;
				displayDot[ekfl].Zero();
            }
            break;
            }
	default:
		{
		// Jos ensimmäinen merkki on pikkukirjain, piste, sulku kiinni tai numero, niin ei tehdä mitään
		if (code >= 97 && code <= 122 && displayFormula[0].Length()==0) {
		break;
		}
#if defined WINS
		if (code == 40 && displayFormula[0].Length()==0) {
		break;
		}
#endif
#if defined GCCE
		if (code == 41 && displayFormula[0].Length()==0) {
		break;
		}
#endif
		if (code == 46 && displayFormula[0].Length()==0) {
		break;
		}
		if (code >= 48 && code <= 57 && displayFormula[0].Length()==0) {
		break;
		}
		//Jos yritetään syöttää sulku kiinni -merkin jälkeen kymmeniä
		if (code >= 48 && code <= 57 && displayFormula[ekfl-2].Compare(_L(")"))==0) {
		break;
		}/*
		//Jos yritetään syöttää numeroksi nollaa
		//if (code == 48 && displayFormula[ekfl-1].Compare(_L("0"))==0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("1"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("2"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("3"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("4"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("5"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("6"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("7"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("8"))!=0) { break; }
		if (code == 48 && displayNumber[ekfl-1].Compare(_L("9"))!=0) { break; }*/
		//Jos yritetään syöttää alaindeksiin satoja
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("0"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("1"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("2"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("3"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("4"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("5"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("6"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("7"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("8"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
		if (code >= 48 && code <= 57 && displayNumber[ekfl-2].Compare(_L("9"))==0 && displayFormula[ekfl-1].Length()==0 && displayDot[ekfl-1].Length()==0) { break; }
	
		
		if (code == 97) {formula.Append(_L("a")); displayFormula[ekfl].Format(_L("a")); }
		if (code == 98) { formula.Append(_L("b")); displayFormula[ekfl].Format(_L("b")); }
		if (code == 99) { formula.Append(_L("c")); displayFormula[ekfl].Format(_L("c")); }
		if (code == 100) { formula.Append(_L("d")); displayFormula[ekfl].Format(_L("d")); }
		if (code == 101) { formula.Append(_L("e")); displayFormula[ekfl].Format(_L("e")); }
		if (code == 102) { formula.Append(_L("f")); displayFormula[ekfl].Format(_L("f")); }
		if (code == 103) { formula.Append(_L("g")); displayFormula[ekfl].Format(_L("g")); }
		if (code == 104) { formula.Append(_L("h")); displayFormula[ekfl].Format(_L("h")); }
		if (code == 105) { formula.Append(_L("i")); displayFormula[ekfl].Format(_L("i")); }
		if (code == 106) { formula.Append(_L("j")); displayFormula[ekfl].Format(_L("j")); }
		if (code == 107) { formula.Append(_L("k")); displayFormula[ekfl].Format(_L("k")); }
		if (code == 108) { formula.Append(_L("l")); displayFormula[ekfl].Format(_L("l")); }
		if (code == 109) { formula.Append(_L("m")); displayFormula[ekfl].Format(_L("m")); }
		if (code == 110) { formula.Append(_L("n")); displayFormula[ekfl].Format(_L("n")); }
		if (code == 111) { formula.Append(_L("o")); displayFormula[ekfl].Format(_L("o")); }
		if (code == 112) { formula.Append(_L("p")); displayFormula[ekfl].Format(_L("p")); }
		if (code == 113) { formula.Append(_L("q")); displayFormula[ekfl].Format(_L("q")); }
		if (code == 114) { formula.Append(_L("r")); displayFormula[ekfl].Format(_L("r")); }
		if (code == 115) { formula.Append(_L("s")); displayFormula[ekfl].Format(_L("s")); }
		if (code == 116) { formula.Append(_L("t")); displayFormula[ekfl].Format(_L("t")); }
		if (code == 117) { formula.Append(_L("u")); displayFormula[ekfl].Format(_L("u")); }
		if (code == 118) { formula.Append(_L("v")); displayFormula[ekfl].Format(_L("v")); }
		if (code == 119) { formula.Append(_L("w")); displayFormula[ekfl].Format(_L("w")); }
		if (code == 120) { formula.Append(_L("x")); displayFormula[ekfl].Format(_L("x")); }
		if (code == 121) { formula.Append(_L("y")); displayFormula[ekfl].Format(_L("y")); }
		if (code == 122) { formula.Append(_L("z")); displayFormula[ekfl].Format(_L("z")); }
		if (code == 65) { formula.Append(_L("A")); displayFormula[ekfl].Format(_L("A"));  }
		if (code == 66) { formula.Append(_L("B")); displayFormula[ekfl].Format(_L("B"));  }
		if (code == 67) { formula.Append(_L("C")); displayFormula[ekfl].Format(_L("C"));  }
		if (code == 68) { formula.Append(_L("D")); displayFormula[ekfl].Format(_L("D"));  }
		if (code == 69) { formula.Append(_L("E")); displayFormula[ekfl].Format(_L("E"));  }
		if (code == 70) { formula.Append(_L("F")); displayFormula[ekfl].Format(_L("F"));  }
		if (code == 71) { formula.Append(_L("G")); displayFormula[ekfl].Format(_L("G"));  }
		if (code == 72) { formula.Append(_L("H")); displayFormula[ekfl].Format(_L("H")); }
		if (code == 73) { formula.Append(_L("I")); displayFormula[ekfl].Format(_L("I"));  }
		if (code == 74) { formula.Append(_L("J")); displayFormula[ekfl].Format(_L("J"));  }
		if (code == 75) { formula.Append(_L("K")); displayFormula[ekfl].Format(_L("K"));  }
		if (code == 76) { formula.Append(_L("L")); displayFormula[ekfl].Format(_L("L"));  }
		if (code == 77) { formula.Append(_L("M")); displayFormula[ekfl].Format(_L("M"));  }
		if (code == 78) { formula.Append(_L("N")); displayFormula[ekfl].Format(_L("N"));  }
		if (code == 79) { formula.Append(_L("O")); displayFormula[ekfl].Format(_L("O"));  }
		if (code == 80) { formula.Append(_L("P")); displayFormula[ekfl].Format(_L("P"));  }
		if (code == 81) { formula.Append(_L("Q")); displayFormula[ekfl].Format(_L("Q"));  }
		if (code == 82) { formula.Append(_L("R")); displayFormula[ekfl].Format(_L("R"));  }
		if (code == 83) { formula.Append(_L("S")); displayFormula[ekfl].Format(_L("S"));  }
		if (code == 84) { formula.Append(_L("T")); displayFormula[ekfl].Format(_L("T"));  }
		if (code == 85) { formula.Append(_L("U")); displayFormula[ekfl].Format(_L("U"));  }
		if (code == 86) { formula.Append(_L("V")); displayFormula[ekfl].Format(_L("V"));  }
		if (code == 87) { formula.Append(_L("W")); displayFormula[ekfl].Format(_L("W"));  }
		if (code == 88) { formula.Append(_L("X")); displayFormula[ekfl].Format(_L("X"));  }
		if (code == 89) { formula.Append(_L("Y")); displayFormula[ekfl].Format(_L("Y"));  }
		if (code == 90) { formula.Append(_L("Z")); displayFormula[ekfl].Format(_L("Z"));  }
		if (code == 48) { formula.Append(_L("0")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("0")); }
		if (code == 49) { formula.Append(_L("1")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("1")); }
		if (code == 50) { formula.Append(_L("2")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("2")); }
		if (code == 51) { formula.Append(_L("3")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("3")); }
		if (code == 52) { formula.Append(_L("4")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("4")); }
		if (code == 53) { formula.Append(_L("5")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("5")); }
		if (code == 54) { formula.Append(_L("6")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("6")); }
		if (code == 55) { formula.Append(_L("7")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("7")); }
		if (code == 56) { formula.Append(_L("8")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("8")); }
		if (code == 57) { formula.Append(_L("9")); Pos[ekfl]=1; displayNumber[ekfl].Format(_L("9")); }
		if (code == 46) { formula.Append(_L(".")); dotPos[ekfl]=1; displayDot[ekfl].Format(_L("."));  }
#if defined WINS
		if (code == 42) { formula.Append(_L("(")); displayFormula[ekfl].Format(_L("(")); }
		if (code == 40) { formula.Append(_L(")")); displayFormula[ekfl].Format(_L(")")); }
#endif
#if defined GCCE
		if (code == 40) { formula.Append(_L("(")); displayFormula[ekfl].Format(_L("(")); }
		if (code == 41) { formula.Append(_L(")")); displayFormula[ekfl].Format(_L(")")); }
#endif
		//if (code == 91) { formula.Append(_L("[")); }
		//if (code == 93) { formula.Append(_L("]")); }
		
		
		if (code >= 40 && code <=122) { ekfl=ekfl+1; }
		
		if (code == 46) { lastWasADot = 1; }
		if (code >= 48 && code <= 57 && lastWasADot == 1) { numberAfterDot = 1; lastWasADot = 0; }
		if (code > 57 && lastWasADot==1) { lastWasADot = 0; }
		
		
		break;
		}
		}
    
    
	
	if (iBrCtlInterface)
        {
        return iBrCtlInterface->OfferKeyEventL(aKeyEvent, aType);
        } 
    
	DrawNow();

    return EKeyWasConsumed;
    }
