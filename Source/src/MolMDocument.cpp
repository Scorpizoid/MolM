/*
* ============================================================================
*  Name         : MolMDocument.h
*  Part of      : MolM
*  Interface   	: Browser Control API 
*  Description  : Implements the document for application.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

// INCLUDE FILES
#include "MolMDocument.h"
#include "MolMUi.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CMolMDocument::CMolMDocument(CEikApplication& aApp)
: CAknDocument(aApp)    
    {
    }

// destructor
CMolMDocument::~CMolMDocument()
    {
    }

// EPOC default constructor can leave.
void CMolMDocument::ConstructL()
    {
    }

// Two-phased constructor.
CMolMDocument* CMolMDocument::NewL(
        CEikApplication& aApp)     // CMolM reference
    {
    CMolMDocument* self = new (ELeave) CMolMDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
    }
    
// ----------------------------------------------------
// CMolMDocument::CreateAppUiL()
// constructs CMolMUi
// ----------------------------------------------------
//
CEikAppUi* CMolMDocument::CreateAppUiL()
    {
    return new (ELeave) CMolMUi;
    }

// End of File  

