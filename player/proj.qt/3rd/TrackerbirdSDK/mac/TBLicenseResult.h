// ======================================
// *** TRACKERBIRD SOFTWARE ANALYTICS ***  
// ******** www.trackerbird.com  ********
// ======================================
// © 2014 Trackerbird. All rights reserved.
//
// SDK Version: MacOS SDK ver 3.2.0 (C++)
// Release date: 20 Mar 2014
//
// You may get the latest version from: http://docs.trackerbird.com
// For customer support please visit: http://helpdesk.trackerbird.com
// ======================================
//

#ifndef __TrackerbirdSDK__TBLicenseResult__
#define __TrackerbirdSDK__TBLicenseResult__

#include <iostream>

/**
 
 adsadss
 
 */

using namespace std;

namespace TrackerbirdSDK
{    
    typedef enum
    {
        TBLicenseStatusNA = -1,
        TBLicenseStatusFalse = 0,
        TBLicenseStatusTrue = 1
    }
    TBLicenseStatus;
    
    typedef enum
    {
        TBKeyTypeEvaluation = 0,
        TBKeyTypePurchased,
        TBKeyTypeFreeware,
        TBKeyTypeUnknown,
        TBKeyTypeNFR,
        TBKeyTypeCustom1,
        TBKeyTypeCustom2,
        TBKeyTypeCustom3
    }
    TBKeyType;
    
    /**
     
     This class represents a response from the `License Management` methods in `TBApp`.
     
     ##Enums
     
     ###TBLicenseStatus
     
         typedef enum
         {
             TBLicenseStatusNA = -1,
             TBLicenseStatusFalse = 0,
             TBLicenseStatusTrue = 1
         }
         TBLicenseStatus;
     
     ###TBKeyType
     
         typedef enum
         {
             TBKeyTypeNA = -1,
             TBKeyTypeEvaluation = 0,
             TBKeyTypePurchased,
             TBKeyTypeFreeware,
             TBKeyTypeUnknown,
             TBKeyTypeNFR,
             TBKeyTypeCustom1,
             TBKeyTypeCustom2,
             TBKeyTypeCustom3
         }
         TBKeyType;
     
     */
    
    class TBLicenseResult
    {
        
    private:
        
        TBLicenseStatus _whitelistedStatus;
        TBLicenseStatus _expiredStatus;
        TBLicenseStatus _blacklistedStatus;
        TBLicenseStatus _activatedStatus;
        TBKeyType _keyType;
        
    public:
        
        /**
         
         @brief Create an instance of TBLicenseResult class.
         
         @details Accepts all of the four types of key status and the key type as well. For more information check the `Enums` section in Detailed Description.
         
         @param whitelistedStatus The Whitelisted Status of the key.
         @param expiredStatus The Expired Status of the key.
         @param blacklistedStatus The Blacklisted Status of the key.
         @param activatedStatus The Activated Status of the key.
         @param keyType The The Key Type.
         
         */
        TBLicenseResult(TBLicenseStatus whitelistedStatus, TBLicenseStatus expiredStatus, TBLicenseStatus blacklistedStatus, TBLicenseStatus activatedStatus, TBKeyType keyType);
        
        ///Get the Whitelisted Status of the key.
        TBLicenseStatus getWhitelistedStatus() const;
        
        ///Get the Expired Status of the key.
        TBLicenseStatus getExpiredStatus() const;
        
        ///Get the Blacklisted Status of the key.
        TBLicenseStatus getBlacklistedStatus() const;
                
        ///Get the Activated Status of the key.
        TBLicenseStatus getActivatedStatus() const;
        
        ///Get the The Key Type.
        TBKeyType getKeyType() const;
    };
}

#endif /* defined(__TrackerbirdSDK__TBLicenseResult__) */
