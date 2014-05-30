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

#ifndef __TrackerbirdSDK__TBVersionResult__
#define __TrackerbirdSDK__TBVersionResult__

#include <iostream>

using namespace std;

namespace TrackerbirdSDK
{
    typedef enum
    {
        TBVersionStatusNA = -1,
        TBVersionStatusNew = 1,
        TBVersionStatusNoNew = 0
    }
    TBVersionStatus;
    
    /**
     
     This class represents a response from the `Checking for Software Updates` method in `TBApp`.
     
     ##Enums
     
     ###TBVersionStatus
     
         typedef enum
         {
             TBVersionStatusNA = -1,
             TBVersionStatusNew = 1,
             TBVersionStatusNoNew = 0
         }
         TBVersionStatus;
     
     @warning You should not perform any kind of "Software Update" if you are going to sumbit your application to the Mac App Store, since Apple forbids any kind of auto updates for applications that resides into the Mac App Store. In such cases you should use this functionality for informative purposes only.
     
     */
    
    class TBVersionResult
    {
    private:
        
        TBVersionStatus _versionStatus;
        string _internalVersion;
        string _version;
        string _downloadURL;
        string _changelogURL;
        
    public:
        
        /**
         
         @brief Creates an instance of TBVersionResult class.
         
         @param versionStatus The status of the version check, refering to Not Avaialbe, New Version or No New Version.
         @param internalVersion Version number used internally (not shown to the user). Max length: 45
         @param version Friendly version number to be shown to the user. Max length: 45
         @param downloadURL The URL from where the new version can be downloaded. Max length: 100
         @param changelogURL The URL from where the user can see the change log. Max length: 100
         
         */
        TBVersionResult(TBVersionStatus versionStatus, string internalVersion, string version, string downloadURL, string changelogURL);
        
        ///Get The status of the version check
        TBVersionStatus getVersionStatus() const;
        
        ///Get Version number used internally
        string getInternalVersion() const;
        
        ///Get Friendly version number
        string getVersion() const;
        
        ///Get The download URL
        string getDownloadURL() const;
        
        ///Get The changelog URL
        string getChangelogURL() const;
        
    };
}



#endif /* defined(__TrackerbirdSDK__TBVersionResult__) */
