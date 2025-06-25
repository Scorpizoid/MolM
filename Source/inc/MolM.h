/*
* ============================================================================
*  Name         : MolM.h
*  Part of      : MolM
*  Interface   	: 
*  Description  : Declares main application class.
*  Version      : 
*
*  Copyright (c) 2005-2006 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation.
* ============================================================================
*/

#ifndef MOLM_H
#define MOLM_H

// INCLUDES
#include <aknapp.h>

// CONSTANTS
// UID of the application
const TUid KUidMolM = { 0x2002AA25 };

// CLASS DECLARATION

/**
* CMolM application class.
* Provides the factory to create a concrete document object.
* 
*/
class CMolM : public CAknApplication
    {
    
    public: // Functions from base classes
        /**
        * From CApaApplication, overridden to enable INI file support.
        * @return CDictionaryStore*, A pointer to the dictionary store
        */
        CDictionaryStore* OpenIniFileLC(RFs& aFs) const;
    private:

        /**
        * From CApaApplication, creates CMolMDocument document object.
        * @return CApaDocument*, A pointer to the created document object.
        */
        CApaDocument* CreateDocumentL();
        
        /**
        * From CApaApplication, returns application's UID (KUidMolM).
        * @return TUid, The value of KUidMolM.
        */
        TUid AppDllUid() const;
    };

#endif

// End of File

