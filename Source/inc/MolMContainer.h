/*
* ============================================================================
*  Name         : MolMContainer.h
*  Part of      : MolM
*  Interface    : Browser Control API
*  Description  : Declares container control for Browser Control Sample application.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

#ifndef MOLMCONTAINER_H
#define MOLMCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <akndef.h>
#include <fbs.h>
#include <e32math.h>
#include <BITSTD.H>
#include "BrCtlInterface.h"
/*
// FORWARD DECLARATIONS
class CMolMSpecialLoadObserver;
class CMolMLayoutObserver;
class CMolMSoftkeysObserver;
class CMolMLoadEventObserver;
class CMolMLinkResolver;
class CMolMStateChangeObserver;
class CMolMDialogsProvider;
*/
// CLASS DECLARATION

/**
*  CMolMContainer class.
*  This is the container control class.
*/
class CMolMContainer : public CCoeControl, MCoeControlObserver, MBrCtlDataLoadSupplier
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        ~CMolMContainer();

    public: // New functions

        /**
        * Pass a command to the Browser Control
        * @since 2.8
        * @param aCommand The command that the Browser Control should process
        * @return void
        */
        void HandleCommandL(TInt aCommand);

        /**
        * Dynamically initialises a menu pane. The Uikon framework calls this 
        *   function, if it is implemented in a menu’s observer, immediately before 
        *   the menu pane is activated. 
        * @since 2.8
        * @param aResourceId Resource ID identifying the menu pane to initialise
        * @param aMenuPane The in-memory representation of the menu pane.
        * @return void
        */
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

        /**
        * Handles key events
        * @since 2.8
        * @param aKeyEvent The key event that occurred.
        * @param aType The window server event type that is being handled
        * @return TKeyResponse Value indicates whether or not the key event was consumed by the control. The default implementation simply returns EKeyWasNotConsumed.
        */
        TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        /**
        * Accessor method for iText
        * @since 2.8
        * @param void
        * @return TDesc& The descriptor of the text
        */
//        inline const TDesC& Text() const {return iText;}
       
        /**
        * Setter method for iText
        * @since 2.8
        * @param aText The descriptor for the text you wish to display
        * @return void
        */
        void SetText( const TDesC& aText );
        
        /**
        * Setter method for iPoint
        * @since 2.8
        * @param aPoint The point at which you want to display the text
        * @return void
        */
        void SetPoint( const TPoint& aPoint );
        
        /**
        * Accessor method iBrCtlInterface
        * @since 2.8
        * @param void
        * @return CBrCtlInterface* A pointer to the browser control interface as a convenience to the observers
        */
        inline CBrCtlInterface* BrCtlInterface() const {return iBrCtlInterface;}

    private: // Functions from base classes

        /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

        /**
        * From CoeControl,CountComponentControls.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl,ComponentControl.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * From CCoeControl,Draw.
        */
        void Draw(const TRect& aRect) const;

        /**
        * Handle key events.
        */
       TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * From MBrCtlDataLoadSupplier, Cancel an on-going load
        */
        void CancelLoad();

        /**
        * Create a Basic Browser Control that does not have observers with scrolling
        * and HTTP framework capabilities
        */
        //void CreateBasicBrowserControlL();

        /**
        * Create Browser Control with observers with the given capabilities
        */
       // void CreateBrowserControlWithObserversL(TUint aCapabilities);

	    /**
        * Read the file.
        */
        HBufC8* ReadFileLC(const TDesC& aFileName);

        /**
        * Handles an event from an observed control.
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
        /**
        * The following methods are used to demonstrate the functionality of 
        * the browser control API
        */
        void BasicBrowserControlL(TInt x, TInt y);
        void OpenAboutBoxL();/*
        void BrowserControlWithObserversL();
        void LoadingContentWithFileHandleL();
        void LoadingContentWithBufferL();
        void IncrementalLoadingL();
        void SpecialLoadRequestsL();
        void CustomizedDialogsL();
        void CustomizedSoftKeysL();
        void ResolvingEmbeddedLinksL();
        void CustomizedScrollBarsL();
        void HandleStateChangedL();
        void ChangeSizeExtentsL();
        void PageInfoL();
        void ContentSizeImageCountL();*/
        TInt keyCode;
        TBuf<256> formula;
        TBuf<256> molarMass;
        TReal molarMassValue;
       // void Parse();
    	TInt position;
    	TInt alaindeksi;
    	TInt shift;
    	TInt lastWasADot;
    	TInt numberAfterDot;
    	TBuf<256> character;
        TBuf<1> displayFormula[200];
        TBuf<1> displayNumber[200];
        TBuf<1> displayDot[200];
        TBuf<255> firstLine;
        TBuf<255> firstLineDisplay;
        TBuf<255> secondLine;
        TInt Pos[200];
        TInt dotPos[200];
   	
    	    	TReal atomicMass[115];
    	    	TBuf<2> atomName[115];
    	    	TInt charCode;
    	    	TInt inputLength;
    	    	TReal m;
    	    	TInt pf;
    	    	TBuf<2> bi[51];
    	    	TReal bim[51];
    	    	TInt get;
    	    	TInt quit;
    	     	TBuf<256> t;
    	     	TBuf<1> s;
    	     	TInt ekfl;
    	     	TInt nkfl;
    	     	TReal mas;
    	     	TReal masBrackets;
    	     	TInt pfl;
    	     	TInt bic[51];
    	     	TBuf<255> ch;
    	     	TBuf<255> ch2;
    	     	TBuf<255> ch3;
    	    	TInt afstatus;
    	    	TInt multiplier;
    	    	TInt bracketOpen;
    	     	TBuf<255> bracketFormula;
    	     	TInt bracketFormulaMultiplier;
    	     	TInt dot;
    	     	TInt dotMultiplier;
    	     	TInt number;
    	     	TReal dotMass;
    	    	void setm();
    	    	TInt mass();
    	    	
    	    	

    	    	
    	    	
    	//void SetMass();
    	
    private: //data 
        // Pointer to the browser control interface
        CBrCtlInterface* iBrCtlInterface;
        // Desired capabilities of the browser control
        TUint iBrCtlCapabilities;
        // Command Base
        TInt iCommandBase;/*
        // Special Load Observer
        CMolMSpecialLoadObserver* iMolMSpecialLoadObserver;
        // Layout Observer
        CMolMLayoutObserver* iMolMLayoutObserver;
        // Softkeys Observer
        CMolMSoftkeysObserver* iMolMSoftkeysObserver;
        // Load Event Observer
        CMolMLoadEventObserver* iMolMLoadEventObserver;
        // Link Resolver
        CMolMLinkResolver* iMolMLinkResolver;
        // State Change Observer
        CMolMStateChangeObserver* iMolMStateChangeObserver;
        // Dialogs Provider
        CMolMDialogsProvider* iMolMDialogsProvider;*/
        // Informs whether or not CancelLoad has been called
        TBool iCancelInitDataLoad;
        // A graphics device to which a bitmap managed by the font and bitmap server can be drawn
 /*       CFbsScreenDevice* iFbsScrDev;
        // Abstract font interface
        CFont* iFont;
        // Text to display to the screen if desired
        TPtrC iText;
        // Point at which to display text
        TPoint iPoint;
        */
       
        //Modi
     	// The cursor coordinates
     	TInt x;
     	TInt y;
     	// Is it running the first time?
     	TUint8 firstrun;
     	CFbsBitmap* bitmap; 
    };

#endif

// End of File

