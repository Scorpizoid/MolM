/*
* ============================================================================
*  Name        : MolMUi.cpp
*  Part of     : MolM
*  Interface   : Browser Control API
*  Description : The Ui class for the Browser Control Sample Application
*  Version     : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

// INCLUDE FILES
#include "MolMUi.h"
#include "MolMContainer.h" 
#include <MolM.rsg>
#include "MolM.hrh"

#include <avkon.hrh>


// ================= MEMBER FUNCTIONS =======================
//
// ----------------------------------------------------------
// CMolMUi::ConstructL()
// ?implementation_description
// ----------------------------------------------------------
//
void CMolMUi::ConstructL()
    {
    BaseConstructL(CAknAppUi::EAknEnableSkin);
    iAppContainer = new (ELeave) CMolMContainer;
    iAppContainer->SetMopParent(this);
    iAppContainer->ConstructL( ClientRect() );
    AddToStackL( iAppContainer );
    }

// ----------------------------------------------------
// CMolMUi::~CMolMUi()
// Destructor
// Frees reserved resources
// ----------------------------------------------------
//
CMolMUi::~CMolMUi()
    {
    if (iAppContainer)
        {
        RemoveFromStack( iAppContainer );
        delete iAppContainer;
        }

   }

// ------------------------------------------------------------------------------
// CMolMUi::::DynInitMenuPaneL(TInt aResourceId,CEikMenuPane* aMenuPane)
//  This function is called by the EIKON framework just before it displays
//  a menu pane. Its default implementation is empty, and by overriding it,
//  the application can set the state of menu items dynamically according
//  to the state of application data.
// ------------------------------------------------------------------------------
//
void CMolMUi::DynInitMenuPaneL(
    TInt aResourceId,CEikMenuPane* aMenuPane)
    {
    iAppContainer->DynInitMenuPaneL(aResourceId, aMenuPane);
    }

// ----------------------------------------------------
// CMolMUi::HandleKeyEventL(
//     const TKeyEvent& aKeyEvent,TEventCode /*aType*/)
// ?implementation_description
// ----------------------------------------------------
//
TKeyResponse CMolMUi::HandleKeyEventL(
    const TKeyEvent& aKeyEvent,TEventCode aType)
    {
    return iAppContainer->HandleKeyEventL(aKeyEvent, aType);;
    }

// ----------------------------------------------------
// CMolMUi::HandleCommandL(TInt aCommand)
// ?implementation_description
// ----------------------------------------------------
//
void CMolMUi::HandleCommandL(TInt aCommand)
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            {
            Exit();
            break;
            }

      default:
            iAppContainer->HandleCommandL(aCommand);
            break;      
        }
    }

// End of File  

