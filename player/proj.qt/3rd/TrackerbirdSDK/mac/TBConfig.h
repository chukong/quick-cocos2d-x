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

#ifndef __TrackerbirdSDK__TBConfig__
#define __TrackerbirdSDK__TBConfig__

#include <iostream>

using namespace std;

namespace TrackerbirdSDK
{    
    

    /**
     
     The `TBConfig` class is used to set some basic information about your product as well as some settings for the Trackerbird SDK. 
     
     You should always attempt to fill in as much accurate and specific details as possible inside the `TBConfig` object since this data will then be used by the Trackerbird Analytics Server to generate the relevant reports. 
     
     The more (optional) details you fill in about your product and its licensing state, the more filtering and reporting options will be available to you inside the Trackerbird Analytics portal.
     
     
     
     ##SDK Configuration
     
     Before an application can start reporting usage to the Trackerbird SDK, it must first provide some basic information such as the Product ID and the callhome URL.
     
     You should always attempt to fill in as much accurate and specific details as possible since this data will then be used by the Trackerbird Analytics Server to generate the relevant reports. The more (optional) details you fill in about your product and its licensing state, the more filtering and reporting options will be available to you inside the Trackerbird Analytics portal.
          
     
     
     
     
     */

    class TBConfig
    {
        
    private:
        string _url;
        string _productID;
        string _productVersion;
        string _productBuildNumber;
        bool _multiSessionEnabled;
        string _productEdition;
        string _productLanguage;
        string _filePath;
                        
        void performInitialization();
        
    public:
        
        /**
         
         @brief Create an instance of TBConfig class.
         
        @note The `url` and `productID` input parameters should be provided and should not be `empty string`. If one of these paramaters is `empty string` - an exception is raised.   
        @note The other parameters (`productVersion`, `productBuildNumber`, `productEdition` and `productLanguage`) are optional and may be `empty string`.
         
         
         @param url Callhome URL: Every product registered with Trackerbird has its own unique callhome URL usually in the form ‘http://xxxxx.tbnet1.com’. This URL is generated automatically on account creation and is used by the SDK to communicate with the Trackerbird server. You can get this URL from the Developer Zone once you login to the customer area. If you have a Premium product account you may opt to use your own custom callhome URL (such as http://updates.yourdomain.com) which must be setup as a CNAME DNS entry pointing to your unique Trackerbird URL. Please note that before you can use your own custom URL you must first inform Trackebird support (support@trackerbird.com) to register your domain with the Trackerbird server. If you fail to do this, the server will automatically reject any incoming calls using yourdomain.com as a callhome URL.
         
         @param productID This is a unique 10-digit Product ID number which identifies your product with the Trackerbird server. You can get this ID from the Developer Zone once you login to the customer area.
         
         @param productVersion The version number of the application being run.
         @param productBuildNumber The build number of the application being run.
         @param multiSessionEnabled Whether multiple user sessions can be present in a single application runtime. Refer to Single vs. Multiple session modes.
         
         @param productEdition The edition of your product. An example of this would be when a single product can be licensed/run in different modes such as as “Home” and “Business”.
         
         @param productLanguage The product language in which the client is viewing your product. This is useful for products which have been internationalized, so you can determine how many installations are running your software in a particular language. Please note this is different than the OS language which is collected automatically by the Trackerbird SDK. We suggest that if your product supports only a single language (such as English), then you simply call SetProductLanguage(“English”) rather than leaving this property undefined.
         
         @return An instance of `TBConfig` object.
         
         @see isMultiSessionEnabled
         
         */
        
        TBConfig(string url, string productID, string productVersion, string productBuildNumber, bool multiSessionEnabled, string productEdition, string productLanguage);
        
        
        /**
         
         @brief Create an instance of TBConfig class.
         
         @note The `url` and `productID` input parameters should be provided and should not be `empty string`. If one of these paramaters is `empty string` - an exception is raised.   
         @note The other parameters (`productVersion`, `productBuildNumber`, `productEdition` and `productLanguage`) are optional and may be `empty string`.
         
         
         @param url Callhome URL: Every product registered with Trackerbird has its own unique callhome URL usually in the form ‘http://xxxxx.tbnet1.com’. This URL is generated automatically on account creation and is used by the SDK to communicate with the Trackerbird server. You can get this URL from the Developer Zone once you login to the customer area. If you have a Premium product account you may opt to use your own custom callhome URL (such as http://updates.yourdomain.com) which must be setup as a CNAME DNS entry pointing to your unique Trackerbird URL. Please note that before you can use your own custom URL you must first inform Trackebird support (support@trackerbird.com) to register your domain with the Trackerbird server. If you fail to do this, the server will automatically reject any incoming calls using yourdomain.com as a callhome URL.
         
         @param productID This is a unique 10-digit Product ID number which identifies your product with the Trackerbird server. You can get this ID from the Developer Zone once you login to the customer area.
         
         @param productVersion The version number of the application being run.
         @param productBuildNumber The build number of the application being run.
         @param multiSessionEnabled Whether multiple user sessions can be present in a single application runtime. Refer to Single vs. Multiple session modes.
         
         @param productEdition The edition of your product. An example of this would be when a single product can be licensed/run in different modes such as as “Home” and “Business”.
         
         @param productLanguage The product language in which the client is viewing your product. This is useful for products which have been internationalized, so you can determine how many installations are running your software in a particular language. Please note this is different than the OS language which is collected automatically by the Trackerbird SDK. We suggest that if your product supports only a single language (such as English), then you simply call SetProductLanguage(“English”) rather than leaving this property undefined.
         
         @param filePath The location where to create and save the Trackerbird SDK working files. 
         
         @note The file path where the Trackerbird SDK will create and save its working files. It is important to remember that the calling process should have read/write accessibility to the location.
         
         @note The default location is as following:
         
         @note * For non-sandboxed apps: `~/Library/Application Support/`
         @note * For sandboxed apps: `~/Library/Containers/<Bundle Identifier>/Data/Library/Application Support/`
         
         @note The SDK will create and keep its working files within the following direcotry structure: `<filePath>/TrackerbirdSDK/<PorductID Hash>/`
         
         @note If you wish to share the SDK functionality between multiple apps, you have to make sure that they are using the exact same `filePath` and `productID`.
         
         
         @return An instance of `TBConfig` object.
         
         @see isMultiSessionEnabled
         
         */
        
        TBConfig(string url, string productID, string productVersion, string productBuildNumber, bool multiSessionEnabled, string productEdition, string productLanguage, string filePath);
        
        ///Get The Callhome URL.
        string getURL();
        
        ///Get The Product ID.
        string getProductID();
        
        ///Get The Product Version.
        string getProductVersion();
        
        ///Get The Product Build Number.
        string getProductBuildNumber();
        
        /**
         @brief Flag indicating of the multisession mode is enabled or not.
         
         @details In desktop software, a single application instance would normally have only one single user session. This means that only such an application would only show one window (or set of windows) to a single user and interaction is done with that single user. If the user would like to use 2 different sessions, 2 instances of the application would have to be loaded which would not affect each other. In such cases, you should use the single session mode, which handles user sessions automatically and assumes that 1 process (instance) means 1 user session.
         
         The multiple session mode needs to be used in multi-user applications, especially applications that have web interfaces. In such applications, a number of users might be using the same application process simultaneously. In such cases, you need to manually tell Trackerbird SDK when user sessions start and stop, and also how to link events (see Feature / Event Tracking) to user sessions. To do this, when starting or stopping a user session, the methods @link TBApp::sessionStart @endlink and @link TBApp::sessionStop @endlink of TBApp should be used, and when tracking events, a session ID needs to be passed as a parameter.
         */
        bool isMultiSessionEnabled();
        
        ///Get The Product Edition.
        string getProductEdition();
        
        ///Get The Product Language.
        string getProductLanguage();
        
        ///Get The file path.
        string getFilePath();
        
    };

}

#endif /* defined(__TrackerbirdSDK__TBConfig__) */




