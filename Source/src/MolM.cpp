/*
* ============================================================================
*  Name         : MolM.cpp
*  Part of      : MolM
*  Interface    : Browser Control API
*  Description  : Implements the main application class.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. 
* ============================================================================
*/

// INCLUDE FILES
#include "MolM.h"
#include "MolMDocument.h"
#include <eikstart.h>

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CMolM::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CMolM::AppDllUid() const
    {
    return KUidMolM;
    }

// ---------------------------------------------------------
// CDictionaryStore* CMolM::OpenIniFileLC(RFs& aFs) const
// overrides CAknApplication::OpenIniFileLC to enable INI file support
// ---------------------------------------------------------
//
CDictionaryStore* CMolM::OpenIniFileLC(RFs& aFs) const
{
    return CEikApplication::OpenIniFileLC(aFs);
}
   
// ---------------------------------------------------------
// CMolM::CreateDocumentL()
// Creates CMolMDocument object
// ---------------------------------------------------------
//
CApaDocument* CMolM::CreateDocumentL()
    {
    return CMolMDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============
//
// ---------------------------------------------------------
// NewApplication() 
// Constructs CMolM
// Returns: created application object
// ---------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication( )
	{
    return new CMolM;
    }
    

// ---------------------------------------------------------
//    E32Main
//    Main function for Symbian OS v9 EXE application
//    Returns: TInt
// ---------------------------------------------------------
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File  

