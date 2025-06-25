// INCLUDE FILES
#include "MolMContainer.h"
#include <eiklabel.h>  // for example label control
#include <avkon.hrh>
#include <MolM.rsg>
#include "MolM.hrh"
#include <BrCtlInterface.h>
#include <CHARCONV.H>
#include <gdi.h>
#include <bitdev.h>
#include <coefont.h>
#include <eikenv.h>
#include <COEFONTPROVIDER.H>
#include <coetextdrawer.h>




// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CMolMContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CMolMContainer::ConstructL(const TRect& aRect)
    {
	
	bracketOpen = 0;

    x = 12;
	y = 4;
	firstrun = 1;
	lastWasADot = 0;
	numberAfterDot = 0;
		for (TInt i=0;i<200;i++) {
		displayNumber[i].Zero(); displayFormula[i].Zero(); Pos[i]=0;
		displayDot[i].Zero(); dotPos[i]=0;
		}
		
	bitmap = new (ELeave) CFbsBitmap(); 

	
	_LIT(KMBMbg,"C:\\private\\2002AA25\\bg.mbm");
	CleanupStack::PushL(bitmap); 
	User::LeaveIfError(bitmap->Load(KMBMbg, 0));
	CleanupStack::Pop(1);

//	iExampleText = HBufC::NewL(40);
//	_LIT(KHydrogen,""); 
//	*iExampleText = KHydrogen;

	//SetMass();
	
	
	CreateWindowL();
    SetRect(aRect);
    ActivateL();
    
   // mass();

    iCommandBase = TBrCtlDefs::ECommandIdBase;
    }

// Destructor
CMolMContainer::~CMolMContainer() 
    {
    if (iBrCtlInterface)
        {
			delete iBrCtlInterface;
        }

	delete bitmap;
/*	delete bitmapCursor;
	delete maskBitmap;
*///    delete iExampleText;
    User::Exit(0);
    }

// ---------------------------------------------------------
// CMolMContainer::SizeChanged()
// Called by framework when the view size is changed
// ---------------------------------------------------------
//
void CMolMContainer::SizeChanged()
    {
    if (iBrCtlInterface)
        {
        iBrCtlInterface->SetRect(Rect());
        }
    }

// ---------------------------------------------------------
// CMolMContainer::CountComponentControls() const
// ---------------------------------------------------------
//
TInt CMolMContainer::CountComponentControls() const
    {
    if (iBrCtlInterface)
        return 1;
    return 0;
    }

// ---------------------------------------------------------
// CMolMContainer::ComponentControl(TInt aIndex) const
// ---------------------------------------------------------
//
CCoeControl* CMolMContainer::ComponentControl(TInt aIndex) const
    {
    switch ( aIndex )
        {
        case 0:
            return iBrCtlInterface; // Could be NULL
        default:
            return NULL;
        }
    }

// ---------------------------------------------------------
// CMolMContainer::Draw(const TRect& aRect) const
// ---------------------------------------------------------
//
void CMolMContainer::Draw(const TRect& aRect) const
    {
    
    CWindowGc& gc = SystemGc();
    // Start with a clear screen
	gc.Clear();
	
			// draw the background
	TPoint pos(0,0);//6,15); 
	gc.BitBlt(pos, bitmap);
	
	
	
	
	
	
	const CFont*     titleFont;
	titleFont = iEikonEnv->TitleFont();
	const CFont*     annotationFont;
	annotationFont = iEikonEnv->AnnotationFont();

	TChar aChar(keyCode);
	TInt width = 20;
	TBuf<1> formulaCharacter;
	//TInt Pos;
	//width = titleFont->TextWidthInPixels(displayFormula);

	TInt i = 0;
	TInt j = 0;
	
	
	
     
     
    // *iExampleText.Format(KFormat1,8);
	
	TRect textRect(0,10,800,284);
	
	gc.SetPenColor(KRgbBlack);  
			   // Draw the text in the middle of the rectangle.
	TInt   titleBaselineOffset=25;//drawRect.Height() - fontUsed->HeightInPixels())/2; 
	
	do
		{
	gc.UseFont(titleFont);
		gc.DrawText(displayFormula[i],textRect,titleBaselineOffset,CGraphicsContext::ELeft, width);
		width = width+titleFont->TextWidthInPixels(displayFormula[i]);

		// Piirrä pisteen eteen numero tavallisessa koossa, jos . 
		if (dotPos[i-2] == 1 && Pos[i] == 1 && displayFormula[i-1].Compare(_L("H"))!=0)
		{
			gc.UseFont(titleFont);
			gc.DrawText(displayNumber[i],textRect,titleBaselineOffset,CGraphicsContext::ELeft, width);
			width = width+titleFont->TextWidthInPixels(displayNumber[i]);
		}
		// .H2O
		if (dotPos[i-2] == 1 && Pos[i] == 1 && displayFormula[i-1].Compare(_L("H"))==0)
		{
		gc.UseFont(annotationFont);
		gc.DrawText(displayNumber[i],textRect,titleBaselineOffset+5,CGraphicsContext::ELeft, width);
		width = width+annotationFont->TextWidthInPixels(displayNumber[i]);
		}
		if (dotPos[i-1] == 1 && Pos[i]==1)
		{
			gc.UseFont(titleFont);
			gc.DrawText(displayNumber[i],textRect,titleBaselineOffset,CGraphicsContext::ELeft, width);
			width = width+titleFont->TextWidthInPixels(displayNumber[i]);
			
		}
		if (dotPos[i-1] != 1 && dotPos[i-2] != 1 && Pos[i] == 1)
		{
			gc.UseFont(annotationFont);
			gc.DrawText(displayNumber[i],textRect,titleBaselineOffset+5,CGraphicsContext::ELeft, width);
			width = width+annotationFont->TextWidthInPixels(displayNumber[i]);
		}
		if (dotPos[i] == 1)
			{
			gc.UseFont(annotationFont);
			gc.DrawText(displayDot[i],textRect,titleBaselineOffset-7,CGraphicsContext::ELeft, width);
			width = width+annotationFont->TextWidthInPixels(_L("."));
		
			}
		i++;
		} while (i<200);

	
	
	gc.UseFont(titleFont);
	gc.DrawText(firstLineDisplay,textRect,108,CGraphicsContext::ELeft, 40);
	gc.UseFont(annotationFont);
	gc.DrawText(secondLine,textRect,169,CGraphicsContext::ELeft, 40);
	gc.UseFont(titleFont);
	gc.DrawText(molarMass,textRect,256,CGraphicsContext::ELeft, 60);
/*	TInt   titleBaselineOffset2=45;//drawRect.Height() - fontUsed->HeightInPixels())/2; 
	gc.DrawText(molarMass,textRect,titleBaselineOffset2,CGraphicsContext::ECenter, 0);*/
			   // Finished using the font
	gc.DiscardFont();
	gc.DiscardFont();

/*
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( KRgbRed );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.DrawRect( textRect );

 */
	
	
	
    }

// ---------------------------------------------------------
// CMolMContainer::HandleControlEventL(
//     CCoeControl* aControl,TCoeEvent aEventType)
// ---------------------------------------------------------
//
void CMolMContainer::HandleControlEventL(
    CCoeControl* /*aControl*/,TCoeEvent /*aEventType*/)
    {
    // TODO: Add your control event handler code here
    }

// ----------------------------------------------------
// CMolMContainer::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ----------------------------------------------------
//
TKeyResponse CMolMContainer::HandleKeyEventL(
    const TKeyEvent& /*aKeyEvent*/,TEventCode /*aType*/)
    {
    return EKeyWasNotConsumed;
    }

// ----------------------------------------------------
// CMolMContainer::CancelLoad()
// ----------------------------------------------------
//
void CMolMContainer::CancelLoad()
    {
    iCancelInitDataLoad = ETrue;
    }

// ----------------------------------------------------
// CMolMContainer::HandleCommandL(TInt aCommand)
// ----------------------------------------------------
//
void CMolMContainer::HandleCommandL(TInt aCommand)
{
    switch ( aCommand )
    {
    	case EAknSoftkeyBack:
        {
            if (iBrCtlInterface != NULL)
            {
            iBrCtlInterface = NULL;
                 DrawNow();
            }
            break;
        }
        case EMolMCmdAppOpen:
        {
            if (iBrCtlInterface == NULL)
            {
				BasicBrowserControlL(x, y);
            }
			break;
        }
        case EMolMCmdAppAbout:
        {
            if (iBrCtlInterface != NULL)
            {
				iBrCtlInterface = NULL;
				DrawNow();
            }
			OpenAboutBoxL();
 			break;
       }
   }
}

// ----------------------------------------------------
// CMolMContainer::DynInitMenuPaneL(
//           TInt aResourceId, CEikMenuPane* aMenuPane)
// ----------------------------------------------------
//
void 
CMolMContainer::DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane)
    {
    if (iBrCtlInterface && aResourceId == R_MOLM_MENU )
        {
        iBrCtlInterface->AddOptionMenuItemsL(*aMenuPane, aResourceId);
        RPointerArray<TBrCtlWmlServiceOption>* options;
        options = iBrCtlInterface->WMLOptionMenuItemsL();
        TInt i;
        TInt count = options->Count();
        for (i = 0; i < count; i++)
            {
            TBrCtlWmlServiceOption* option = (*options)[i];
            if (option != NULL)
                {
                CEikMenuPaneItem::SData item;
                item.iText.Copy(option->Text());
                item.iCommandId = option->ElemID();
                item.iFlags = 0;
                item.iCascadeId = 0;
                aMenuPane->InsertMenuItemL(item, 0);
                }
            }
        }
    }


// ----------------------------------------------------
// CMolMContainer::ReadFileLC(const TDesC& aFileName)
// ----------------------------------------------------
//
HBufC8* 
CMolMContainer::ReadFileLC(const TDesC& aFileName)
    {
    RFs rfs;
    RFile file;
    User::LeaveIfError(rfs.Connect());
    CleanupClosePushL(rfs);
    User::LeaveIfError(file.Open(rfs, aFileName, EFileRead));
    CleanupClosePushL(file);
    TInt size;
    User::LeaveIfError(file.Size(size));
    HBufC8* buf = HBufC8::NewLC(size);
    TPtr8 bufPtr(buf->Des());
    User::LeaveIfError(file.Read(bufPtr));
    CleanupStack::Pop(); // buf
    CleanupStack::PopAndDestroy(2); // file, rfs
    CleanupStack::PushL(buf);
    return buf;
    }

// ----------------------------------------------------
// CMolMContainer::BasicBrowserControlL()
// ----------------------------------------------------
//
void 
CMolMContainer::BasicBrowserControlL(TInt x, TInt y)
    {
   }


void 
CMolMContainer::OpenAboutBoxL()
    {
    if (iBrCtlInterface == NULL) {
    
    
				TRect rect(120,10, 640,264);//Position(), Size());
				iBrCtlInterface = CreateBrowserControlL( this, 
				rect, 
				TBrCtlDefs::ECapabilityDisplayScrollBar,
				iCommandBase, 
				NULL, 
				NULL,
				NULL, 
				NULL,
				NULL);
				
				_LIT(KUrl, "file:///C:\\private\\2002AA25\\about.html");
				iBrCtlInterface->LoadUrlL(KUrl);
	
		}
   }

TInt CMolMContainer::mass()
	{
	
	TInt a;
	TInt stringPos;
	TBuf<2> stringHandler;
	TBuf<2> smallLetterStringHandler;
	
	setm();
	
	t.Format(formula);
	//t.Append(_L("   "));
	a=0;
	molarMassValue = 0;
	position = 0;
	bracketFormulaMultiplier = 1;
	masBrackets = 0;
	mas=0;
	dot = 0;
	dotMass = 0;
	dotMultiplier = 1;
	if (t.Length() == 0) { molarMass.Format(_L("Ei alkuaineita!")); return 0; }
	//stringPos=stringPos+1;
	
	if (t.Find(_L(".")) != KErrNotFound) { dot = 1; }
	
	// Kidevedet
	if (dot == 1)
		{
		stringPos = t.Find(_L("."));
		stringPos = stringPos + 1;
		if (t.Mid(stringPos,1) == _L("1")) { dotMultiplier = 1; }
		if (t.Mid(stringPos,1) == _L("2")) { dotMultiplier = 2; }
		if (t.Mid(stringPos,1) == _L("3")) { dotMultiplier = 3; }
		if (t.Mid(stringPos,1) == _L("4")) { dotMultiplier = 4; }
		if (t.Mid(stringPos,1) == _L("5")) { dotMultiplier = 5; }
		if (t.Mid(stringPos,1) == _L("6")) { dotMultiplier = 6; }
		if (t.Mid(stringPos,1) == _L("7")) { dotMultiplier = 7; }
		if (t.Mid(stringPos,1) == _L("8")) { dotMultiplier = 8; }
		if (t.Mid(stringPos,1) == _L("9")) { dotMultiplier = 9; }
		if (t.Mid(stringPos+1,1) == _L("0")) { dotMultiplier = dotMultiplier*10; }
		if (t.Mid(stringPos+1,1) == _L("1")) { dotMultiplier = dotMultiplier*10 + 1; }
		if (t.Mid(stringPos+1,1) == _L("2")) { dotMultiplier = dotMultiplier*10 + 2; }
		if (t.Mid(stringPos+1,1) == _L("3")) { dotMultiplier = dotMultiplier*10 + 3; }
		if (t.Mid(stringPos+1,1) == _L("4")) { dotMultiplier = dotMultiplier*10 + 4; }
		if (t.Mid(stringPos+1,1) == _L("5")) { dotMultiplier = dotMultiplier*10 + 5; }
		if (t.Mid(stringPos+1,1) == _L("6")) { dotMultiplier = dotMultiplier*10 + 6; }
		if (t.Mid(stringPos+1,1) == _L("7")) { dotMultiplier = dotMultiplier*10 + 7; }
		if (t.Mid(stringPos+1,1) == _L("8")) { dotMultiplier = dotMultiplier*10 + 8; }
		if (t.Mid(stringPos+1,1) == _L("9")) { dotMultiplier = dotMultiplier*10 + 9; }
		if (t.Length() == stringPos+5) { if (t.Mid(stringPos+2,3) == _L("H2O")) { dotMass = atomicMass[1]*2+atomicMass[8]; } }
		if (t.Length() == stringPos+4) { if (t.Mid(stringPos+1,3) == _L("H2O")) { dotMass = atomicMass[1]*2+atomicMass[8]; } }
		if (t.Length() == stringPos+3) { if (t.Mid(stringPos,3) == _L("H2O")) { dotMass = atomicMass[1]*2+atomicMass[8]; dotMultiplier=1; } }
		
		dotMass = dotMass * dotMultiplier;
		TInt dotFactor = dotMultiplier;
		TBuf<255> water;
		water.Format(_L("M(%dH) + M(%dO) + "),dotMultiplier*2,dotMultiplier);
		firstLineDisplay.Append(water);
		
		
		water.Format(_L("%d x "),dotMultiplier*2);
		secondLine.Append(water);
		water.Format(_L("%f"),atomicMass[1]);
		secondLine.Append(water);
		secondLine.Delete(secondLine.Find(_L("."))+4,secondLine.Length()-secondLine.Find(_L("."))+4);
		secondLine.Replace(secondLine.Find(_L(".")),1,_L(","));
		secondLine.Append(_L(" g/mol + "));
		
		water.Format(_L("%d x "),dotMultiplier);
		secondLine.Append(water);
		water.Format(_L("%f"),atomicMass[8]);
		secondLine.Append(water);
		secondLine.Delete(secondLine.Find(_L("."))+4,secondLine.Length()-secondLine.Find(_L("."))+4);
		secondLine.Replace(secondLine.Find(_L(".")),1,_L(","));
		secondLine.Append(_L(" g/mol + "));
		/*do
			{
		//firstLine.Append(_L("HHO"));
		firstLineDisplay.Append(_L("HHO"));
		dotFactor--;
			}while (dotFactor>=1);*/
		
		// .66H2O
		if (t.Length() == stringPos+5) { t.Delete(stringPos-1,6); }
		if (t.Length() == stringPos+4) { t.Delete(stringPos-1,5); }
		if (t.Length() == stringPos+3) { t.Delete(stringPos-1,4); }
		

		
	dot = 0;
	}
	
	if (dot == 0)
		{
	stringPos=t.Length();
	do
		{
		stringPos=stringPos-1;
		
		if (t.Mid(stringPos,1) == _L("a")) { charCode = 97; }
		if (t.Mid(stringPos,1) == _L("b")) { charCode = 98; }
		if (t.Mid(stringPos,1) == _L("c")) { charCode = 99; }
		if (t.Mid(stringPos,1) == _L("d")) { charCode = 100; }
		if (t.Mid(stringPos,1) == _L("e")) { charCode = 101; }
		if (t.Mid(stringPos,1) == _L("f")) { charCode = 102; }
		if (t.Mid(stringPos,1) == _L("g")) { charCode = 103; }
		if (t.Mid(stringPos,1) == _L("h")) { charCode = 104; }
		if (t.Mid(stringPos,1) == _L("i")) { charCode = 105; }
		if (t.Mid(stringPos,1) == _L("j")) { charCode = 106; }
		if (t.Mid(stringPos,1) == _L("k")) { charCode = 107; }
		if (t.Mid(stringPos,1) == _L("l")) { charCode = 108; }
		if (t.Mid(stringPos,1) == _L("m")) { charCode = 109; }
		if (t.Mid(stringPos,1) == _L("n")) { charCode = 110; }
		if (t.Mid(stringPos,1) == _L("o")) { charCode = 111; }
		if (t.Mid(stringPos,1) == _L("p")) { charCode = 112; }
		if (t.Mid(stringPos,1) == _L("q")) { charCode = 113; }
		if (t.Mid(stringPos,1) == _L("r")) { charCode = 114; }
		if (t.Mid(stringPos,1) == _L("s")) { charCode = 115; }
		if (t.Mid(stringPos,1) == _L("t")) { charCode = 116; }
		if (t.Mid(stringPos,1) == _L("u")) { charCode = 117; }
		if (t.Mid(stringPos,1) == _L("v")) { charCode = 118; }
		if (t.Mid(stringPos,1) == _L("w")) { charCode = 119; }
		if (t.Mid(stringPos,1) == _L("x")) { charCode = 120; }
		if (t.Mid(stringPos,1) == _L("y")) { charCode = 121; }
		if (t.Mid(stringPos,1) == _L("z")) { charCode = 122; }
		if (t.Mid(stringPos,1) ==  _L("A")) { charCode = 65 ; }
		if (t.Mid(stringPos,1) ==  _L("B")) { charCode = 66 ; }
		if (t.Mid(stringPos,1) ==  _L("C")) { charCode = 67 ; }
		if (t.Mid(stringPos,1) ==  _L("D")) { charCode = 68 ; }
		if (t.Mid(stringPos,1) ==  _L("E")) { charCode = 69 ; }
		if (t.Mid(stringPos,1) ==  _L("F")) { charCode = 70 ; }
		if (t.Mid(stringPos,1) ==  _L("G")) { charCode = 71 ; }
		if (t.Mid(stringPos,1) ==  _L("H")) { charCode = 72 ; }
		if (t.Mid(stringPos,1) ==  _L("I")) { charCode = 73 ; }
		if (t.Mid(stringPos,1) ==  _L("J")) { charCode = 74 ; }
		if (t.Mid(stringPos,1) ==  _L("K")) { charCode = 75 ; }
		if (t.Mid(stringPos,1) ==  _L("L")) { charCode = 76 ; }
		if (t.Mid(stringPos,1) ==  _L("M")) { charCode = 77 ; }
		if (t.Mid(stringPos,1) ==  _L("N")) { charCode = 78 ; }
		if (t.Mid(stringPos,1) ==  _L("O")) { charCode = 79 ; }
		if (t.Mid(stringPos,1) ==  _L("P")) { charCode = 80 ; }
		if (t.Mid(stringPos,1) ==  _L("Q")) { charCode = 81 ; }
		if (t.Mid(stringPos,1) ==  _L("R")) { charCode = 82 ; }
		if (t.Mid(stringPos,1) ==  _L("S")) { charCode = 83 ; }
		if (t.Mid(stringPos,1) ==  _L("T")) { charCode = 84 ; }
		if (t.Mid(stringPos,1) ==  _L("U")) { charCode = 85 ; }
		if (t.Mid(stringPos,1) ==  _L("V")) { charCode = 86 ; }
		if (t.Mid(stringPos,1) ==  _L("W")) { charCode = 87 ; }
		if (t.Mid(stringPos,1) ==  _L("X")) { charCode = 88 ; }
		if (t.Mid(stringPos,1) ==  _L("Y")) { charCode = 89 ; }
		if (t.Mid(stringPos,1) ==  _L("Z")) { charCode = 90 ; }
		if (t.Mid(stringPos,1) == _L("0")) { charCode = 48; }
		if (t.Mid(stringPos,1) == _L("1")) { charCode = 49; }
		if (t.Mid(stringPos,1) == _L("2")) { charCode = 50; }
		if (t.Mid(stringPos,1) == _L("3")) { charCode = 51; }
		if (t.Mid(stringPos,1) == _L("4")) { charCode = 52; }
		if (t.Mid(stringPos,1) == _L("5")) { charCode = 53; }
		if (t.Mid(stringPos,1) == _L("6")) { charCode = 54; }
		if (t.Mid(stringPos,1) == _L("7")) { charCode = 55; }
		if (t.Mid(stringPos,1) == _L("8")) { charCode = 56; }
		if (t.Mid(stringPos,1) == _L("9")) { charCode = 57; }
#if defined WINS
		if (t.Mid(stringPos,1) == _L("(")) { charCode = 42; }
		if (t.Mid(stringPos,1) == _L(")")) { charCode = 40; }
#endif
#if defined GCCE
if (t.Mid(stringPos,1) == _L("(")) { charCode = 41; }
if (t.Mid(stringPos,1) == _L(")")) { charCode = 42; }
#endif
		//if (t.Mid(stringPos,1) == _L("[")) { charCode = 91; }
		//if (t.Mid(stringPos,1) == _L("]")) { charCode = 93; }

		TInt found = 0;
		TInt tens = 0;
		TBuf<2> times;
		TInt factor = 1;
		TBuf<15> atomicName;
		TBuf<255> temp;
		TBuf<255> temp2;
		TInt kerroin = 0;
		
		// )
#if defined WINS
		if (charCode == 40)
#endif
#if defined GCCE
		if (charCode == 42)
#endif
			{
			bracketOpen = 1;
			if (t.Length()!=stringPos+1)
				{
			if (t.Mid(stringPos+1,1) == _L("0")) { bracketFormulaMultiplier = 0; }
			if (t.Mid(stringPos+1,1) == _L("1")) { bracketFormulaMultiplier = 1; }
			if (t.Mid(stringPos+1,1) == _L("2")) { bracketFormulaMultiplier = 2; }
			if (t.Mid(stringPos+1,1) == _L("3")) { bracketFormulaMultiplier = 3; }
			if (t.Mid(stringPos+1,1) == _L("4")) { bracketFormulaMultiplier = 4; }
			if (t.Mid(stringPos+1,1) == _L("5")) { bracketFormulaMultiplier = 5; }
			if (t.Mid(stringPos+1,1) == _L("6")) { bracketFormulaMultiplier = 6; }
			if (t.Mid(stringPos+1,1) == _L("7")) { bracketFormulaMultiplier = 7; }
			if (t.Mid(stringPos+1,1) == _L("8")) { bracketFormulaMultiplier = 8; }
			if (t.Mid(stringPos+1,1) == _L("9")) { bracketFormulaMultiplier = 9; }
				}
			}
		
		// (
#if defined WINS
		if (charCode == 42)
#endif
#if defined GCCE
		if (charCode == 41)
#endif
			{
			bracketOpen = 0;
			masBrackets = masBrackets*bracketFormulaMultiplier;
			bracketFormulaMultiplier = 1;
			}
		
		
		
		
		// 0 - 9
		if (charCode>=48 && charCode<=57)
			{
			if (stringPos-2 >= 0)
			{
			// Aluksi haravoidaan kaksi merkkiä taaksepäin
			// Esim. He2 ->  >He<2
			ch2.Format(t.Mid(stringPos-2,2));
			// ch2 sisältää nyt He
			if (stringPos-3 >= 0)
				{
					// Jos He22 eli numero viimeisen kakkosen edessä, niin 
					if (t.Mid(stringPos-1,1) == _L("0")) { tens = 0; }
					if (t.Mid(stringPos-1,1) == _L("1")) { tens = 10; }
					if (t.Mid(stringPos-1,1) == _L("2")) { tens = 20; }
					if (t.Mid(stringPos-1,1) == _L("3")) { tens = 30; }
					if (t.Mid(stringPos-1,1) == _L("4")) { tens = 40; }
					if (t.Mid(stringPos-1,1) == _L("5")) { tens = 50; }
					if (t.Mid(stringPos-1,1) == _L("6")) { tens = 60; }
					if (t.Mid(stringPos-1,1) == _L("7")) { tens = 70; }
					if (t.Mid(stringPos-1,1) == _L("8")) { tens = 80; }
					if (t.Mid(stringPos-1,1) == _L("9")) { tens = 90; }
					// ch2 sisältää He
					if (tens != 0) { ch2.Format(t.Mid(stringPos-3,2)); }
				}
				a=1;
				do
					{
					if (ch2.Compare(atomName[a])==0)
					{
						// Jos löytyi
						if (bracketOpen == 1) { masBrackets = masBrackets + atomicMass[a]*(charCode-48+tens); }
						else { mas = mas + atomicMass[a]*(charCode-48+tens); }
						
						times.Format(_L("%d"),(charCode-48+tens)*bracketFormulaMultiplier);
						factor = (charCode-48+tens)*bracketFormulaMultiplier;
						do
							{
						firstLine.Append(atomName[a]);
						factor--;
							}while (factor>=1);
						
						//Cl + Cl::
						for (TInt d=0;d<500;d++)
							{
							if (firstLine.Find(atomName[a]) != KErrNotFound)
								{
							kerroin = kerroin + 1;
							//temp.Format(atomName[a]);
//							temp2.Format(atomName[a],_L(" x %d"),kerroin);
							//firstLineDisplay.Append(temp);
							firstLine.Delete(firstLine.Find(atomName[a]),atomName[a].Length());
							}						
							}
						//firstLine.Delete(firstLine.Find(atomName[a]),atomName[a].Length());
						if (kerroin == 1) { temp.Format(_L("M("),kerroin); }
						else { temp.Format(_L("M(%d"),kerroin); }
						firstLineDisplay.Append(temp);
						firstLineDisplay.Append(atomName[a]);
						firstLineDisplay.Append(_L(") + "));
						
						secondLine.Append(times);
						atomicName.Format(_L(" x %f"),atomicMass[a]);
						secondLine.Append(atomicName);
						secondLine.Delete(secondLine.Find(_L("."))+4,secondLine.Length()-secondLine.Find(_L("."))+4);
						secondLine.Replace(secondLine.Find(_L(".")),1,_L(","));
						secondLine.Append(_L(" g/mol + "));
						found = 1;
					}
					a=a+1;
					} while (a<=114);
				//Jos löytyi
				if (found == 1)
					{
					if (tens!= 0) { t.Replace(stringPos-3,4,_L(";;;;")); }
					else { t.Replace(stringPos-2,3,_L(";;;")); }
					ch2.Replace(0,2,_L(";;"));
					found = 0;
					tens=0;
					}
			}
		
			// Sitten yksi merkki taaksepäin
			ch.Format(t.Mid(stringPos-1,1));
			if (stringPos-2 >= 0)
				{
					if (t.Mid(stringPos-1,1) == _L("0")) { tens = 0; }
					if (t.Mid(stringPos-1,1) == _L("1")) { tens = 10; }
					if (t.Mid(stringPos-1,1) == _L("2")) { tens = 20; }
					if (t.Mid(stringPos-1,1) == _L("3")) { tens = 30; }
					if (t.Mid(stringPos-1,1) == _L("4")) { tens = 40; }
					if (t.Mid(stringPos-1,1) == _L("5")) { tens = 50; }
					if (t.Mid(stringPos-1,1) == _L("6")) { tens = 60; }
					if (t.Mid(stringPos-1,1) == _L("7")) { tens = 70; }
					if (t.Mid(stringPos-1,1) == _L("8")) { tens = 80; }
					if (t.Mid(stringPos-1,1) == _L("9")) { tens = 90; }
					// Otetaan kaksi merkkiä taaksepäin
					if (tens != 0) { ch.Format(t.Mid(stringPos-2,1)); }
				}
				a=1;
				do
					{
					if (ch.Compare(atomName[a])==0)
					{
						if (bracketOpen == 1) { masBrackets = masBrackets + atomicMass[a]*(charCode-48+tens); }
						else { mas = mas + atomicMass[a]*(charCode-48+tens); }
						
						times.Format(_L("%d"),(charCode-48+tens)*bracketFormulaMultiplier);
						factor = (charCode-48+tens)*bracketFormulaMultiplier;
						do
							{
						firstLine.Append(atomName[a]);
						factor--;
							}while (factor>=1);
						
						//Cl + Cl::
						for (TInt d=0;d<500;d++)
							{
							if (firstLine.Find(atomName[a]) != KErrNotFound)
								{
							kerroin = kerroin + 1;
							//firstLineDisplay.Append(atomName[a]);
							firstLine.Delete(firstLine.Find(atomName[a]),atomName[a].Length());
							}						
							}

						if (kerroin == 1) { temp.Format(_L("M("),kerroin); }
						else { temp.Format(_L("M(%d"),kerroin); }
						firstLineDisplay.Append(temp);
						firstLineDisplay.Append(atomName[a]);
						firstLineDisplay.Append(_L(") + "));

						secondLine.Append(times);
						atomicName.Format(_L(" x %f"),atomicMass[a]);
						secondLine.Append(atomicName);
						secondLine.Delete(secondLine.Find(_L("."))+4,secondLine.Length()-secondLine.Find(_L("."))+4);
						secondLine.Replace(secondLine.Find(_L(".")),1,_L(","));
						secondLine.Append(_L(" g/mol + "));
						found = 1;
					}
					a=a+1;
					} while (a<=114);
				if (found == 1)
					{
				if (tens!= 0) { t.Replace(stringPos-2,3,_L(";;;")); }
				else { t.Replace(stringPos-1,2,_L(";;")); }
				ch.Replace(0,1,_L(";"));
				found = 0;
				tens = 0;
					}
				charCode = 0;
				
			}
		// a - z
		if (charCode>=97 && charCode<=122)
			{
			ch.Format(t.Mid(stringPos-1,2));
			a=1;
				do
					{
					if (ch.Compare(atomName[a])==0)
						{
					if (bracketOpen == 1) { masBrackets = masBrackets + atomicMass[a]; factor = bracketFormulaMultiplier; }
					else { mas = mas + atomicMass[a]; factor = 1; }
					
					do
						{
					firstLine.Append(atomName[a]);
					factor--;
						}while (factor>=1);
					
					//Cl + Cl::
					for (TInt d=0;d<500;d++)
						{
						if (firstLine.Find(atomName[a]) != KErrNotFound)
							{
						kerroin = kerroin + 1;
						//firstLineDisplay.Append(atomName[a]);
						firstLine.Delete(firstLine.Find(atomName[a]),atomName[a].Length());
						}						
						}
						
					if (kerroin == 1) { temp.Format(_L("M("),kerroin); }
					else { temp.Format(_L("M(%d"),kerroin); }
					firstLineDisplay.Append(temp);
					firstLineDisplay.Append(atomName[a]);
					firstLineDisplay.Append(_L(") + "));

					//secondLine.Append(kerroin);
					if (kerroin == 1) { atomicName.Format(_L("%f"),atomicMass[a]); }
					else { atomicName.Format(_L("%d x %f"),kerroin,atomicMass[a]); }
					secondLine.Append(atomicName);
					secondLine.Delete(secondLine.Find(_L("."))+4,secondLine.Length()-secondLine.Find(_L("."))+4);
					secondLine.Replace(secondLine.Find(_L(".")),1,_L(","));
					secondLine.Append(_L(" g/mol + "));
						}
					a=a+1;
					} while (a<=114);
				t.Replace(stringPos-1,2,_L(";;"));
				ch.Replace(0,2,_L(";;"));
				charCode = 0;
				
			}
		// A - Z
		if (charCode >=65 && charCode<=90)
			{
			ch.Format(t.Mid(stringPos,1));
			a=1;
			do
				{
				if (ch.Compare(atomName[a])==0)
					{
				if (bracketOpen == 1) { masBrackets = masBrackets + atomicMass[a]; factor = bracketFormulaMultiplier; }
				else { mas = mas + atomicMass[a]; factor = 1; }
				
				
				//times.Format(_L("%d"),(charCode-48+tens)*bracketFormulaMultiplier);
				do
					{
				firstLine.Append(atomName[a]);
				firstLine.Append(_L(" + ")); 
				factor--;
					}while (factor>=1);
				//Cl + Cl
				for (TInt d=0;d<500;d++)
					{
					if (firstLine.Find(atomName[a]) != KErrNotFound)
						{
					kerroin = kerroin + 1;
					//firstLineDisplay.Append(atomName[a]);
					firstLine.Delete(firstLine.Find(atomName[a]),atomName[a].Length());
					}						
					}
				if (kerroin == 1) { temp.Format(_L("M("),kerroin); }
				else { temp.Format(_L("M(%d"),kerroin); }
				firstLineDisplay.Append(temp);
				firstLineDisplay.Append(atomName[a]);
				firstLineDisplay.Append(_L(") + "));

				//secondLine.Append(kerroin);
				if (kerroin == 1) { atomicName.Format(_L("%f"),atomicMass[a]); }
				else { atomicName.Format(_L("%d x %f"),kerroin,atomicMass[a]); }
				secondLine.Append(atomicName);
				secondLine.Delete(secondLine.Find(_L("."))+4,secondLine.Length()-secondLine.Find(_L("."))+4);
				secondLine.Replace(secondLine.Find(_L(".")),1,_L(","));
				secondLine.Append(_L(" g/mol + "));
					}
				a=a+1;
				} while (a<=114);
			
			t.Replace(stringPos,1,_L(";"));
			ch.Replace(0,1,_L(";"));
			charCode = 0;
			}
		

		} while (stringPos!=0);
		}
	
	mas = masBrackets + mas + dotMass;
	
	
	molarMass.Format(_L("M: %f"),mas);
	molarMass.Replace(molarMass.Find(_L(".")),1,_L(","));
	molarMass.Delete(molarMass.Find(_L(","))+4,molarMass.Length()-molarMass.Find(_L(","))+4);
	molarMass.Append(_L(" g/mol"));

	firstLineDisplay.Replace(firstLineDisplay.Length()-2,1,_L("="));
	secondLine.Replace(secondLine.Length()-2,1,_L("="));
	
	
	return 0;
	}

void CMolMContainer::setm()
	{

	atomicMass[0]=0;
	atomicMass[1] = 1.008;
	atomicMass[2] = 4.0026022;
	atomicMass[3] = 6.94;
	atomicMass[4] = 9.01218315;
	atomicMass[5] = 10.81;
	atomicMass[6] = 12.011;
	atomicMass[7] = 14.007;
	atomicMass[8] = 15.999;
	atomicMass[9] = 18.9984031636;
	atomicMass[10] = 20.17976;
	atomicMass[11] = 22.989769282;
	atomicMass[12] = 24.305;
	atomicMass[13] = 26.98153857;
	atomicMass[14] = 28.085;
	atomicMass[15] = 30.9737619985;
	atomicMass[16] = 32.06;
	atomicMass[17] = 35.45;
	atomicMass[18] = 39.9481;
	atomicMass[19] = 39.09831;
	atomicMass[20] = 40.0784;
	atomicMass[21] = 44.9559085;
	atomicMass[22] = 47.8671;
	atomicMass[23] = 50.94151;
	atomicMass[24] = 51.99616;
	atomicMass[25] = 54.9380443;
	atomicMass[26] = 55.8452;
	atomicMass[27] = 58.9331944;
	atomicMass[28] = 58.69344;
	atomicMass[29] = 63.5463;
	atomicMass[30] = 65.382;
	atomicMass[31] = 69.7231;
	atomicMass[32] = 72.6308;
	atomicMass[33] = 74.9215956;
	atomicMass[34] = 78.9718;
	atomicMass[35] = 79.904;
	atomicMass[36] = 83.7982;
	atomicMass[37] = 85.46783;
	atomicMass[38] = 87.621;
	atomicMass[39] = 88.905842;
	atomicMass[40] = 91.2242;
	atomicMass[41] = 92.906372;
	atomicMass[42] = 95.951;
	atomicMass[43] = 97;
	atomicMass[44] = 101.072;
	atomicMass[45] = 102.905502;
	atomicMass[46] = 106.421;
	atomicMass[47] = 107.86822;
	atomicMass[48] = 112.4144;
	atomicMass[49] = 114.8181;
	atomicMass[50] = 118.7107;
	atomicMass[51] = 121.7601;
	atomicMass[52] = 127.603;
	atomicMass[53] = 126.904473;
	atomicMass[54] = 131.2936;
	atomicMass[55] = 132.905451966;
	atomicMass[56] = 137.3277;
	atomicMass[57] = 138.905477;
	atomicMass[58] = 140.1161;
	atomicMass[59] = 140.907662;
	atomicMass[60] = 144.2423;
	atomicMass[61] = 145;
	atomicMass[62] = 150.362;
	atomicMass[63] = 151.9641;
	atomicMass[64] = 157.253;
	atomicMass[65] = 158.925352;
	atomicMass[66] = 162.5001;
	atomicMass[67] = 164.930332;
	atomicMass[68] = 167.2593;
	atomicMass[69] = 168.934222;
	atomicMass[70] = 173.0545;
	atomicMass[71] = 174.96681;
	atomicMass[72] = 178.492;
	atomicMass[73] = 180.947882;
	atomicMass[74] = 183.841;
	atomicMass[75] = 186.2071;
	atomicMass[76] = 190.233;
	atomicMass[77] = 192.2173;
	atomicMass[78] = 195.0849;
	atomicMass[79] = 196.9665695;
	atomicMass[80] = 200.5923;
	atomicMass[81] = 204.38;
	atomicMass[82] = 207.21;
	atomicMass[83] = 208.980401;
	atomicMass[84] = 209;
	atomicMass[85] = 210;
	atomicMass[86] = 222;
	atomicMass[87] = 223;
	atomicMass[88] = 226;
	atomicMass[89] = 227;
	atomicMass[90] = 232.03774;
	atomicMass[91] = 231.035882;
	atomicMass[92] = 238.028913;
	atomicMass[93] = 237;
	atomicMass[94] = 244;
	atomicMass[95] = 243;
	atomicMass[96] = 247;
	atomicMass[97] = 247;
	atomicMass[98] = 251;
	atomicMass[99] = 252;
	atomicMass[100] = 257;
	atomicMass[101] = 258;
	atomicMass[102] = 259;
	atomicMass[103] = 262;
	atomicMass[104] = 267;
	atomicMass[105] = 270;
	atomicMass[106] = 271;
	atomicMass[107] = 270;
	atomicMass[108] = 277;
	atomicMass[109] = 276;
	atomicMass[110] = 281;
	atomicMass[111] = 282;
	atomicMass[112] = 285;
	atomicMass[113] = 289;
	atomicMass[114] = 293;
	for (TInt rounder=0;rounder<115;rounder++)
		{
		Math::Round(atomicMass[rounder],atomicMass[rounder],3);
		}
	atomName[0]=_L("!!");
	atomName[1]=_L("H");
	atomName[2]=_L("He");
	atomName[3]=_L("Li");
	atomName[4]=_L("Be");
	atomName[5]=_L("B");
	atomName[6]=_L("C");
	atomName[7]=_L("N");
	atomName[8]=_L("O");
	atomName[9]=_L("F");
	atomName[10]=_L("Ne");
	atomName[11]=_L("Na");
	atomName[12]=_L("Mg");
	atomName[13]=_L("Al");
	atomName[14]=_L("Si");
	atomName[15]=_L("P");
	atomName[16]=_L("S");
	atomName[17]=_L("Cl");
	atomName[18]=_L("Ar");
	atomName[19]=_L("K");
	atomName[20]=_L("Ca");
	atomName[21]=_L("Sc");
	atomName[22]=_L("Ti");
	atomName[23]=_L("V");
	atomName[24]=_L("Cr");
	atomName[25]=_L("Mn");
	atomName[26]=_L("Fe");
	atomName[27]=_L("Co");
	atomName[28]=_L("Ni");
	atomName[29]=_L("Cu");
	atomName[30]=_L("Zn");
	atomName[31]=_L("Ga");
	atomName[32]=_L("Ge");
	atomName[33]=_L("As");
	atomName[34]=_L("Se");
	atomName[35]=_L("Br");
	atomName[36]=_L("Kr");
	atomName[37]=_L("Rb");
	atomName[38]=_L("Sr");
	atomName[39]=_L("Y");
	atomName[40]=_L("Zr");
	atomName[41]=_L("Nb");
	atomName[42]=_L("Mo");
	atomName[43]=_L("Tc");
	atomName[44]=_L("Ru");
	atomName[45]=_L("Ro");
	atomName[46]=_L("Pd");
	atomName[47]=_L("Ag");
	atomName[48]=_L("Cd");
	atomName[49]=_L("In");
	atomName[50]=_L("Sn");
	atomName[51]=_L("Sb");
	atomName[52]=_L("Te");
	atomName[53]=_L("I");
	atomName[54]=_L("Xe");
	atomName[55]=_L("Cs");
	atomName[56]=_L("Ba");
	atomName[57]=_L("La");
	atomName[58]=_L("Ce");
	atomName[59]=_L("Pr");
	atomName[60]=_L("Nd");
	atomName[61]=_L("Pm");
	atomName[62]=_L("Sm");
	atomName[63]=_L("Eu");
	atomName[64]=_L("Gd");
	atomName[65]=_L("Tb");
	atomName[66]=_L("Dy");
	atomName[67]=_L("Ho");
	atomName[68]=_L("Er");
	atomName[69]=_L("Tm");
	atomName[70]=_L("Yb");
	atomName[71]=_L("Lu");
	atomName[72]=_L("Hf");
	atomName[73]=_L("Ta");
	atomName[74]=_L("W");
	atomName[75]=_L("Re");
	atomName[76]=_L("Os");
	atomName[77]=_L("Ir");
	atomName[78]=_L("Pt");
	atomName[79]=_L("Au");
	atomName[80]=_L("Hg");
	atomName[81]=_L("Tl");
	atomName[82]=_L("Pb");
	atomName[83]=_L("Bi");
	atomName[84]=_L("Po");
	atomName[85]=_L("At");
	atomName[86]=_L("Rn");
	atomName[87]=_L("Fr");
	atomName[88]=_L("Ra");
	atomName[89]=_L("Ac");
	atomName[90]=_L("Th");
	atomName[91]=_L("Pa");
	atomName[92]=_L("U");
	atomName[93]=_L("Np");
	atomName[94]=_L("Pu");
	atomName[95]=_L("Am");
	atomName[96]=_L("Cm");
	atomName[97]=_L("Bk");
	atomName[98]=_L("Cf");
	atomName[99]=_L("Es");
	atomName[100]=_L("Fm");
	atomName[101]=_L("Md");
	atomName[102]=_L("No");
	atomName[103]=_L("Lr");
	atomName[104]=_L("Rf");
	atomName[105]=_L("Db");
	atomName[106]=_L("Sg");
	atomName[107]=_L("Bh");
	atomName[108]=_L("Hs");
	atomName[109]=_L("Mt");
	atomName[110]=_L("Ds");
	atomName[111]=_L("Rg");
	atomName[112]=_L("Cn");
	atomName[113]=_L("Fl");
	atomName[114]=_L("Lv");
	}
