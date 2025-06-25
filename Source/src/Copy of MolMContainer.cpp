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
#include <eikenv.h>


// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CMolMContainer::ConstructL(const TRect& aRect)
// EPOC two phased constructor
// ---------------------------------------------------------
//
void CMolMContainer::ConstructL(const TRect& aRect)
    {
	
	
    x = 12;
	y = 4;
	firstrun = 1;
/*	bitmap = new (ELeave) CFbsBitmap(); 

	
	_LIT(KMBMbg,"C:\\private\\2002AA25\\background.mbm");
	CleanupStack::PushL(bitmap); 
	User::LeaveIfError(bitmap->Load(KMBMbg, 0));
	CleanupStack::Pop(1);
*/
//	iExampleText = HBufC::NewL(40);
//	_LIT(KHydrogen,""); 
//	*iExampleText = KHydrogen;

	//SetMass();
	
	
	CreateWindowL();
    SetRect(aRect);
    ActivateL();
    
    mass();

    iCommandBase = TBrCtlDefs::ECommandIdBase;
    }

// Destructor
CMolMContainer::~CMolMContainer() 
    {
    if (iBrCtlInterface)
        {
			delete iBrCtlInterface;
        }

/*	delete bitmap;
	delete bitmapCursor;
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
/*	
			// draw the background
	TPoint pos(0,0);//6,15); 
	gc.BitBlt(pos, bitmap);
	
	
	
	
	// Load the cursor mask 
	// Calculate rectangle for the whole bitmap 
	TRect bmpPieceRect(TPoint(0,0),bitmapCursor->SizeInPixels()); 
	
	gc.BitBltMasked(TPoint(x,y),bitmapCursor,bmpPieceRect,maskBitmap,ETrue); 
	
	
	*/
	
	
	const CFont*     titleFont;
	titleFont = iEikonEnv->TitleFont();
	gc.UseFont(titleFont);

	TChar aChar(keyCode);
	TInt width = titleFont->CharWidthInPixels(aChar);
	
	
     
     
    // *iExampleText.Format(KFormat1,8);
	
	TRect textRect(0,10,640,88);
	
	gc.SetPenColor(KRgbBlack);  
			   // Draw the text in the middle of the rectangle.
	TInt   titleBaselineOffset=25;//drawRect.Height() - fontUsed->HeightInPixels())/2; 
	gc.DrawText(formula,textRect,titleBaselineOffset,CGraphicsContext::ELeft, 20);
	gc.DrawText(molarMass,textRect,65,CGraphicsContext::ELeft, 20);
/*	TInt   titleBaselineOffset2=45;//drawRect.Height() - fontUsed->HeightInPixels())/2; 
	gc.DrawText(molarMass,textRect,titleBaselineOffset2,CGraphicsContext::ECenter, 0);*/
			   // Finished using the font
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
/*
void CMolMContainer::SetMass()
	{
	massH = 1.008;
	massHe = 4.003;
	massLi = 6.941;
	massBe = 9.012;
	massB = 10.81;
	massC = 12.011;
	massN = 14.007;
	massO = 15.999;
	massF = 18.998;
	massNe = 20.180;
	massNa = 22.990;
	massMg = 24.305;
	massAl = 26.982;
	massSi = 28.085;
	massP = 30.974;
	massS = 32.06;
	massCl = 35.453;
	massAr = 39.948;
	massK = 39.098;
	massCa = 40.078;
	massSc = 44.956;
	massTi = 47.867;
	massV = 50.942;
	massCr = 51.996;
	massMn = 54.938;
	massFe = 55.85;
	massCo = 58.93;
	massNi = 58.70;
	massCu = 63.55;
	massZn = 65.38;
	massGa = 69.72;
	massGe = 72.59;
	massAs = 74.92;
	massSe = 78.96;
	massBr = 79.9;
	massKr = 83.8;
	massRb = 85.47;
	massSr = 87.62;
	massY = 88.91;
	massZr = 91.22;
	massNb = 92.91;
	massMo = 95.94;
	massTc = 97;
	massRu = 101.07;
	massRo = 102.91;
	massPd = 106.4;
	massAg = 107.87;
	massCd = 112.41;
	massIn = 114.82;
	massSn = 118.69;
	massSb = 121.75;
	massTe = 127.6;
	massI = 126.9;
	massXe = 131.3;
	massCs = 132.91;
	massBa = 137.33;
	massLa = 138.91;
	massCe = 140.12;
	massPr = 140.91;
	massNd = 144.24;
	massPm = 145;
	massSm = 150.4;
	massEu = 151.96;
	massGd = 157.25;
	massTb = 158.93;
	massDy = 162.5;
	massHo = 164.93;
	massEr = 167.26;
	massTm = 168.93;
	massYb = 173.04;
	massLu = 147.97;
	massHf = 178.49;
	massTa = 180.95;
	massW = 183.85;
	massRe = 186.2;
	massOs = 190.2;
	massIr = 192.2;
	massPt = 195.1;
	massAu = 196.97;
	massHg = 200.59;
	massTl = 204.37;
	massPb = 207.2;
	massBi = 208.98;
	massPo = 209;
	massAt = 210;
	massRn = 222;
	massFr = 223;
	massRa = 226.05;
	massAc = 227.028;
	massTh = 232.038;
	massPa = 231.036;
	massU = 238.029;
	massNp = 237.048;
	massPu = 244;
	massAm = 243;
	massCm = 247;
	massBk = 247;
	massCf = 251;
	massEs = 254;
	massFm = 257;
	massMd = 258;
	massNo = 259;
	massLr = 260;
	massRf = 261;
	massDb = 262;
	massSg = 269;
	massBh = 270;
	massHs = 269;
	massMt = 278;
	massDs = 281;
	massRg = 281;
	massCn = 285;
	massFl = 289;
	massLv = 293;
	}

*/

TInt CMolMContainer::mass()
	{
	TInt f;
	TInt ekf;
	TInt nkf;
	TInt nfl;
	TInt smallLetter;
	
	TInt a;
	TInt stringPos;
	TReal c;
	//TReal s;
	TInt num;
	TBuf<2> stringHandler;
	TBuf<2> smallLetterStringHandler;
	TBuf<2> el[51];
	TInt d;
	TInt g;
 	TReal m[51];
 	TInt fa[51];
	TInt gf[51];
	
	setm();
	
	t.Format(_L("H"));
	//t.Append(_L("   "));
	stringPos=t.Length();
	a=0;
	do {
		bi[a].Format(_L("")); // bi$(a)=""
		bim[a]=0;
		bic[a]=0;
		a=a+1;
	} while (a<=50);
	a=0;
	mas=0;
	d=0;
	f=1;
	ekf=1;
	nkf=1;
	smallLetter=0;
	nfl = -1;
	num=0;
	if (t.Length() == 0) { return 0; }
	//stringPos=stringPos+1;
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
		if (t.Mid(stringPos,1) == _L(".")) { charCode = 46; }
		if (t.Mid(stringPos,1) == _L(",")) { charCode = 44; }
		if (t.Mid(stringPos,1) == _L("-")) { charCode = 45; }
		if (t.Mid(stringPos,1) == _L("+")) { charCode = 43; }
		if (t.Mid(stringPos,1) == _L("==")) { charCode = 61; }
		if (t.Mid(stringPos,1) == _L("!")) { charCode = 33; }
#if defined WINS
if (t.Mid(stringPos,1) == _L("(")) { charCode = 40; }
if (t.Mid(stringPos,1) == _L(")")) { charCode = 41; }
#endif
#if defined GCCE
if (t.Mid(stringPos,1) == _L("(")) { charCode = 41; }
if (t.Mid(stringPos,1) == _L(")")) { charCode = 42; }
#endif
		if (t.Mid(stringPos,1) == _L(":")) { charCode = 58; }
		if (t.Mid(stringPos,1) == _L(";")) { charCode = 59; }
		if (t.Mid(stringPos,1) == _L("_")) { charCode = 95; }
		if (t.Mid(stringPos,1) == _L("?")) { charCode = 63; }
		if (t.Mid(stringPos,1) == _L("[")) { charCode = 91; }
		if (t.Mid(stringPos,1) == _L("]")) { charCode = 93; }

		// a - z
		if (charCode>=97 && charCode<=122)
			{
			smallLetter=charCode;
			nfl=-1;
			f=num;
			num=0;
			if (f==0)
			{
				f=1;
			}
			}
		
		//Numerot
		if (charCode>=48 && charCode<=57)
			{
			nfl=nfl+1;
			TReal arg;
			Math::Pow10(arg,nfl);
			num=num+(charCode-48)*(arg);
			}
		
		//Hakasulku kiinni
		if (charCode==93)
			{
			nfl=-1;
			ekf=num;
			num=0;
			if (ekf==0) { ekf=1; }
			}
		
		// Hakasulku auki
			if (charCode==91)
				{
			ekf=1;
			}
		
		//Sulku kiinni
			if (charCode==41)
				{
			nfl=-1;
			nkf=num;
			num=0;
			if (nkf==0)
				{
				nkf=1;
				}
			}
		
		//Piste
		if (charCode == 46)
			{
			nfl=-1;
			g=num;
			num=0;
			d=d+1;
			el[d].Format(_L("::"));
			}
		
		//Sulku auki
		if (charCode == 40)
			{
		nkf=1;
			}
		
		//A - Z
		if (charCode >=65 && charCode<=90)
		{
		molarMass.Format(_L("%d"),charCode);
/*		if (smallLetter == 65) { smallLettersa.Format(_L("A")); }
		if (smallLetter == 66) { smallLettersa.Format(_L("B")); }
		if (smallLetter == 67) { smallLettersa.Format(_L("C")); }
		if (smallLetter == 68) { smallLettersa.Format(_L("D")); }
		if (smallLetter == 69) { smallLettersa.Format(_L("E")); }
		if (smallLetter == 70) { smallLettersa.Format(_L("F")); }
		if (smallLetter == 71) { smallLettersa.Format(_L("G")); }
		if (smallLetter == 72) { smallLettersa.Format(_L("H")); }
		if (smallLetter == 73) { smallLettersa.Format(_L("I")); }
		if (smallLetter == 74) { smallLettersa.Format(_L("J")); }
		if (smallLetter == 75) { smallLettersa.Format(_L("K")); }
		if (smallLetter == 76) { smallLettersa.Format(_L("L")); }
		if (smallLetter == 77) { smallLettersa.Format(_L("M")); }
		if (smallLetter == 78) { smallLettersa.Format(_L("N")); }
		if (smallLetter == 79) { smallLettersa.Format(_L("O")); }
		if (smallLetter == 80) { smallLettersa.Format(_L("P")); }
		if (smallLetter == 81) { smallLettersa.Format(_L("Q")); }
		if (smallLetter == 82) { smallLettersa.Format(_L("R")); }
		if (smallLetter == 83) { smallLettersa.Format(_L("S")); }
		if (smallLetter == 84) { smallLettersa.Format(_L("T")); }
		if (smallLetter == 85) { smallLettersa.Format(_L("U")); }
		if (smallLetter == 86) { smallLettersa.Format(_L("V")); }
		if (smallLetter == 87) { smallLettersa.Format(_L("W")); }
		if (smallLetter == 88) { smallLettersa.Format(_L("X")); }
		if (smallLetter == 89) { smallLettersa.Format(_L("Y")); }*/

			if (smallLetter == 0)
				{
				if (charCode == 65) { stringHandler.Format(_L("A")); }
				if (charCode == 66) { stringHandler.Format(_L("B")); }
				if (charCode == 67) { stringHandler.Format(_L("C")); }
				if (charCode == 68) { stringHandler.Format(_L("D")); }
				if (charCode == 69) { stringHandler.Format(_L("E")); }
				if (charCode == 70) { stringHandler.Format(_L("F")); }
				if (charCode == 71) { stringHandler.Format(_L("G")); }
				if (charCode == 72) { stringHandler.Format(_L("H")); }
				if (charCode == 73) { stringHandler.Format(_L("I")); }
				if (charCode == 74) { stringHandler.Format(_L("J")); }
				if (charCode == 75) { stringHandler.Format(_L("K")); }
				if (charCode == 76) { stringHandler.Format(_L("L")); }
				if (charCode == 77) { stringHandler.Format(_L("M")); }
				if (charCode == 78) { stringHandler.Format(_L("N")); }
				if (charCode == 79) { stringHandler.Format(_L("O")); }
				if (charCode == 80) { stringHandler.Format(_L("P")); }
				if (charCode == 81) { stringHandler.Format(_L("Q")); }
				if (charCode == 82) { stringHandler.Format(_L("R")); }
				if (charCode == 83) { stringHandler.Format(_L("S")); }
				if (charCode == 84) { stringHandler.Format(_L("T")); }
				if (charCode == 85) { stringHandler.Format(_L("U")); }
				if (charCode == 86) { stringHandler.Format(_L("V")); }
				if (charCode == 87) { stringHandler.Format(_L("W")); }
				if (charCode == 88) { stringHandler.Format(_L("X")); }
				if (charCode == 89) { stringHandler.Format(_L("Y")); }
				if (charCode == 90) { stringHandler.Format(_L("Z")); }
				nfl=-1;
				f=num;
				num=0;
				if (f==0)
				{
					f=1;
				}
			}
			else
				{
				if (charCode == 65) { stringHandler.Format(_L("A")); }
				if (charCode == 66) { stringHandler.Format(_L("B")); }
				if (charCode == 67) { stringHandler.Format(_L("C")); }
				if (charCode == 68) { stringHandler.Format(_L("D")); }
				if (charCode == 69) { stringHandler.Format(_L("E")); }
				if (charCode == 70) { stringHandler.Format(_L("F")); }
				if (charCode == 71) { stringHandler.Format(_L("G")); }
				if (charCode == 72) { stringHandler.Format(_L("H")); }
				if (charCode == 73) { stringHandler.Format(_L("I")); }
				if (charCode == 74) { stringHandler.Format(_L("J")); }
				if (charCode == 75) { stringHandler.Format(_L("K")); }
				if (charCode == 76) { stringHandler.Format(_L("L")); }
				if (charCode == 77) { stringHandler.Format(_L("M")); }
				if (charCode == 78) { stringHandler.Format(_L("N")); }
				if (charCode == 79) { stringHandler.Format(_L("O")); }
				if (charCode == 80) { stringHandler.Format(_L("P")); }
				if (charCode == 81) { stringHandler.Format(_L("Q")); }
				if (charCode == 82) { stringHandler.Format(_L("R")); }
				if (charCode == 83) { stringHandler.Format(_L("S")); }
				if (charCode == 84) { stringHandler.Format(_L("T")); }
				if (charCode == 85) { stringHandler.Format(_L("U")); }
				if (charCode == 86) { stringHandler.Format(_L("V")); }
				if (charCode == 87) { stringHandler.Format(_L("W")); }
				if (charCode == 88) { stringHandler.Format(_L("X")); }
				if (charCode == 89) { stringHandler.Format(_L("Y")); }
				if (charCode == 90) { stringHandler.Format(_L("Z")); }
				stringHandler.Append(smallLetterStringHandler);
					smallLetter=0;
			}
			a=0;
			c=0;
			do
				{
				if (stringHandler.Compare(atomName[a])==0)
					{
					c=atomicMass[a];
				}
				a=a+1;
			}
			while (a<=105);
			molarMass.Format(_L("%f"),c);
			
			if (c!=0)
				{
				el[d].Format(stringHandler);
				m[d]=c;
				if (g==0)
					{
					g=1;
				}
				gf[d]=g;
				fa[d]=f*ekf*nkf;
				f=1;
				d=d+1;
				}
		}
		} while (stringPos!=0);
	if (d == 0)
		{
	//molarMass.Format(_L("Ei sisalla tunnettuja alkuaineita"));
	return 0;
		}
	ch.Format(t);
	a=0;
	stringPos=0;
	do
		{
		if (el[a].Compare(_L("::"))==0)
			{
			pf=1;
			pfl=gf[a+1];
			do
				{
				gf[stringPos]=pfl;
				stringPos=stringPos+1;
			}
			while (stringPos!=a-1);
			stringPos=a;
			}
		if (pf)
			{
			gf[a]=1;
			}
		a=a+1;
		}
	while (a!=d);
	if (stringPos!=0)
		{
		a=stringPos;
		do
			{
			el[a].Format(el[a+1]);
			fa[a]=fa[a+1];
			gf[a]=gf[a+1];
			m[a]=m[a+1];
			a=a+1;
		}
		while (a!=d);
		d=d-1;
		}
	a=0;
	do
		{
		stringHandler.Format(el[a]);
		f=fa[a]*gf[a];
		stringPos=a;
		do
			{
			if (stringPos<=d && stringHandler.Compare(el[stringPos])==0)
				{
				f=f+fa[stringPos]*gf[stringPos];
				m[stringPos]=0;
				el[stringPos].Format(_L(""));
				gf[stringPos]=0;
				fa[stringPos]=0;
			}
			stringPos=stringPos+1;
			}
		while (stringPos<d);
		fa[a]=f;
		gf[a]=1;
		a=a+1;
		}
	while (a!=d);
	a=0;
	stringPos=0;
	do
		{
		if (el[a].Compare(_L(""))!=0)
		{
			stringPos=stringPos+1;
			bi[stringPos].Format(el[a]);
			bim[stringPos]=m[a];
			bic[stringPos]=fa[a];
		}
		a=a+1;
		}
	while (a!=d);
	a=1;
	//do
		//{
				mas=mas+bim[a]*bic[a];
				a=a+1;
		//}
	//while (a!=stringPos);
	TReal H = 1.008;
	TInt A = 1;
	
	molarMass.Format(_L("%f"),mas);
	return 0;
	}

void CMolMContainer::setm()
	{

	atomicMass[0]=0;
	atomicMass[1]=1.008;
	atomicMass[2]=4.003;
	atomicMass[3]=6.941;
	atomicMass[4]=9.012;
	atomicMass[5]=10.81;
	atomicMass[6]=12.011;
	atomicMass[7]=14.007;
	atomicMass[8]=15.999;
	atomicMass[9]=18.998;
	atomicMass[10]=20.180;
	atomicMass[11]=22.990;
	atomicMass[12]=24.305;
	atomicMass[13]=26.982;
	atomicMass[14]=28.085;
	atomicMass[15]=30.974;
	atomicMass[16]=32.06;
	atomicMass[17]=35.453;
	atomicMass[18]=39.948;
	atomicMass[19]=39.098;
	atomicMass[20]=40.078;
	atomicMass[21]=44.956;
	atomicMass[22]=47.867;
	atomicMass[23]=50.942;
	atomicMass[24]=51.996;
	atomicMass[25]=54.938;
	atomicMass[26]=55.85;
	atomicMass[27]=58.93;
	atomicMass[28]=58.70;
	atomicMass[29]=63.55;
	atomicMass[30]=65.38;
	atomicMass[31]=69.72;
	atomicMass[32]=72.59;
	atomicMass[33]=74.92;
	atomicMass[34]=78.96;
	atomicMass[35]=79.9;
	atomicMass[36]=83.8;
	atomicMass[37]=85.47;
	atomicMass[38]=87.62;
	atomicMass[39]=88.91;
	atomicMass[40]=91.22;
	atomicMass[41]=92.91;
	atomicMass[42]=95.94;
	atomicMass[43]=97;
	atomicMass[44]=101.07;
	atomicMass[45]=102.91;
	atomicMass[46]=106.4;
	atomicMass[47]=107.87;
	atomicMass[48]=112.41;
	atomicMass[49]=114.82;
	atomicMass[50]=118.69;
	atomicMass[51]=121.75;
	atomicMass[52]=127.6;
	atomicMass[53]=126.9;
	atomicMass[54]=131.3;
	atomicMass[55]=132.91;
	atomicMass[56]=137.33;
	atomicMass[57]=138.91;
	atomicMass[58]=140.12;
	atomicMass[59]=140.91;
	atomicMass[60]=144.24;
	atomicMass[61]=145;
	atomicMass[62]=150.4;
	atomicMass[63]=151.96;
	atomicMass[64]=157.25;
	atomicMass[65]=158.93;
	atomicMass[66]=162.5;
	atomicMass[67]=164.93;
	atomicMass[68]=167.26;
	atomicMass[69]=168.93;
	atomicMass[70]=173.04;
	atomicMass[71]=147.97;
	atomicMass[72]=178.49;
	atomicMass[73]=180.95;
	atomicMass[74]=183.85;
	atomicMass[75]=186.2;
	atomicMass[76]=190.2;
	atomicMass[77]=192.2;
	atomicMass[78]=195.1;
	atomicMass[79]=196.97;
	atomicMass[80]=200.59;
	atomicMass[81]=204.37;
	atomicMass[82]=207.2;
	atomicMass[83]=208.98;
	atomicMass[84]=209;
	atomicMass[85]=210;
	atomicMass[86]=222;
	atomicMass[87]=223;
	atomicMass[88]=226.05;
	atomicMass[89]=227.028;
	atomicMass[90]=232.038;
	atomicMass[91]=231.036;
	atomicMass[92]=238.029;
	atomicMass[93]=237.048;
	atomicMass[94]=244;
	atomicMass[95]=243;
	atomicMass[96]=247;
	atomicMass[97]=247;
	atomicMass[98]=251;
	atomicMass[99]=254;
	atomicMass[100]=257;
	atomicMass[101]=258;
	atomicMass[102]=259;
	atomicMass[103]=260;
	atomicMass[104]=261;
	atomicMass[105]=262;
	atomName[0]=_L("Ei");
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
	}
