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

#ifndef __TrackerbirdSDK__TBApp__
#define __TrackerbirdSDK__TBApp__

#include <iostream>
#include "TBConfig.h"
#include "TBMessageResult.h"
#include "TBLicenseResult.h"
#include "TBVersionResult.h"

using namespace std;

namespace TrackerbirdSDK
{
    typedef enum
    {
        TBResultStatusUnknown = 0,
        TBResultStatusOK = 1,
        TBResultStatusFunctionNotAvailable,
        TBResultStatusConnectionError,
        TBResultStatusAuthenticationFailure,
        TBResultStatusServerError,
        TBResultStatusConfigurationNotLoaded,
        TBResultStatusConfigurationNotInitialized
    }
    TBResultStatus;
    
    typedef enum
    {
        TBPrivacyModeOff = 0, //Collects both architecture and usage data (default).
        TBPrivacyModeLow, //Collect only architecture data but NOT usage data.
        TBPrivacyModeHigh //Does not collect any architecture or usage data.
    }
    TBPrivacyMode;
    
    /**
     
     Once the required configuration is initialized (explained in the SDK Configuration page) and set according to the needs of your application, you may inform the SDK that the application has started. This will allow you to use further methods which expect the application to be running such as @link keyCheck @endlink and @link messageCheck @endlink .
     
     All completion functions are optional, meaning that you can safely pass `NULL` if you dont require callbacks.
     
     All completion functions are dispatched on the main thread.
     
     However it is recommended to allways dispatch the execution of completion blocks on a desired thread, using GCD's `dispatch_async` or similar method.
     
     ###Caching and Synchronizing
     
     The Trackerbird SDK was designed to minimize network traffic and load on the end user’s machine. In order to do this, all the collected architecture info and runtime tracking data is cached locally and then compressed and sent to the Trackerbird server in batches, at various intervals whenever appropriate. Log data is usually sent at least once for every runtime session (during @link stop @endlink ), however this may vary based on the type of application and usage activity.
     
     All data is sent over HTTP (port 80) using a proprietary Trackerbird protocol. Using HTTP port 80 is crucial for callhome requests not to be blocked by gateway firewalls especially when running in corporate networks which are sometimes configured to block HTTPS and other unknown traffic. Only a minor portion of traffic (containing authentication IDs) is encrypted by the protocol. Log data is stored in plaintext and transferred unencrypted. This was designed purposely for the sake of transparency so that security-conscious users can freely sniff whatever is being sent out of their machine so they can confirm that no user-identifiable information is being collected or transmitted.
     
     
     
     ###Forced Synchronization
     
     Under normal conditions, you do not need to instruct the Trackerbird SDK when to synchronize with the cloud server, since this happens automatically at various intervals, and is triggered by your interaction with the API. In a typical runtime session, the SDK will always attempt to synchronize with the server at least once whenever your application calls @link stop @endlink.
     
     In order to cater for custom requirements, the API also provides you with the option to forcefully request the SDK to sync all cached data. This is done by calling the `[TBApp sync:]` method. In the case where your application runs as a background service or as a webserver where @link stop @endlink is rarely called due to the always-on nature of the application, you may opt to use @link startAutoSync @endlink and @link stopAutoSync @endlink which launch a background process that will call @link sync @endlink on a regular schedule.
     
     
     
     ###Feature / Event Tracking
     
     Through event tracking, Trackerbird allows you keep track of how your clients are interacting with the various features within your application, potentially identifying how often every single feature is being used by various user groups. Apart from monitoring feature usage, you can also keep track of how often an event happens - such as how often an “auto save” has been made on average for every hour your application was running. Futher to that, you may also keep a numeric value every time an event is reported. This can be used for example to keep the length of time it took to save a file, or the file size that was saved, etc. These events can be recorded using the event tracking methods.
     
     Once event-related data has been collected, you will be able to identify trends of which features are most used during evaluation and whether this trend changes once users switch to a freeware or purchased license or once they update to a different version/product build. You will also be able to compare whether any UI tweaks in a particular version or build number had any effect on exposing a particular feature or whether changes in the actual functionality make a feature more or less popular with users. This tool provides excellent insight for A/B testing whereas you can compare the outcome from different builds to improve the end user expierence.
     
     Optionally, events can be categorised into groups. In order to do this, use the method overloads which accept the “group” parameter. This group name then shows up in the reports, making the data more readable and easier to work with.
     
     Note: Event Tracking should NOT be used to track the occurrence of exceptions since there is another specific API call for this purpose. If you need to track exceptions, refer to `Exception Tracking`.
     
     Note on Event Naming Conventions: Whatever event and group names you use as a parameter will be visible in the analytics reports. Therefore we recommend you use a meaningful and structured naming convention to make it easier for you to identify the feature/event in the analytics reports.
     
     Naming restrictions: Event names are limited to 40 characters and cannot contain the semicolon ”;” and vertical bar “|” characters. Longer event names will be truncated and restricted characters will be replaced by “_”. If group names are used, the total combined length of the group name and the event name should not exceed 40 characters.
     
     
     
     ###Exception Tracking
     
     Trackerbird is able to collect runtime exceptions from your application and then produce reports on the exceptions that were collected. Once an exception is tracked, Trackerbird will also save a snapshot of the current machine architecture so that you can later (through the online exception browser within the customer area) investigate the exception details and pinpoint any specific OS or architecture related specs which are the cause of common exceptions. Collection of exception data is done through the exception tracking methods.
     
     
     
     ###ReachOut™ direct-to-desktop messaging service
     
     From the online customer area you can create ReachOut™ messaging campaigns which are used to deliver messages or surveys directly to the desktop of users who are running your software. You may choose a specific target audience for your message by defining a set of delivery filters so that each message will be delivered only to those users who match the specified criteria (such as geographical region, edition, version, build, language, OS, license status, runtime duration, days since install, etc.)
     
     When building a ReachOut™ campaign you can choose between 2 message delivery options.
     
     * Automated HTML popup messages (which is handled entirely by the Trackerbird library and requires absolutely NO coding.
     * Manually retrieving the message (plaintext or URL) through code by using the `Manual Message Retrieval` methods.
     
     ####Manual Message Retrieval
     
     When you want full control on when and where in your application to display a ReachOut™ message to your users, you can define ReachOut™ messages of the type plain text or URL. Then from within your application you can call one of the below functions to check with the Trackerbird server whether there are any pending messages (of this type) waiting to be delivered.
     
     You may choose to display plaintext messages anywhere in your application such as in a status bar or information box. For the URL type messages you can either open the URL in a browser or else render it in some HTML previewer embedded within your application.
     
     To use this functionality, the @link messageCheck @endlink or the @link messageCheckWithType @endlink method should be used. The difference between them is that one does not take messageType parameter and fills it with the type of message that is sent by the server, while in the other, the message type is specified by the developer, and the server would then only send messages of that type.
     
     The message type (plain text or URL) can be one of the types from the following enum:
     
     public enum MessageType
     {
     AllMessageType=0,
     TextMessageType=1,
     URLMessageType=2
     }
     
     
     ###License Management
     
     Trackerbird allows you to maintain your own license key register on the Trackerbird server. At the time of writing (September 2012), the license key register only accepts Blacklisted keys. However, support for other key types will be added soon. For more information see @link keyCheck @endlink and @link keyChange @endlink
     
     
     ###Checking for Software Updates
     
     Trackerbird offers a service to manage updates for your software.
     By logging in to the customer area and accessing the Builds Management page you are able to add one or more build numbers that will be tagged as the ‘latest builds’ for your software.
     Then, from within your application you can call @link versionCheck @endlink to confirm whether end users are using the latest build/version of your your application or whether there are any newer builds available for download.
     Every latest build can apply to either a specific edition/versions/build or else apply to all installations.
     Therefore when the server matches the latest build numbers for your application it will also take into consideration the current software Edition, Version and build number that were initially submitted when creating the SDK configuration.
     
     @warning You should not perform any kind of "Software Update" if you are going to sumbit your application to the Mac App Store, since Apple forbids any kind of auto updates for applications that resides into the Mac App Store. In such cases you should use this functionality for informative purposes only.
     
     
     @discussion .
     
     ##Enums
     
     ###TBResultStatus
     
         typedef enum
         {
             TBResultStatusUnknown = 0,
             TBResultStatusOK = 1,
             TBResultStatusFunctionNotAvailable,
             TBResultStatusConnectionError,
             TBResultStatusAuthenticationFailure,
             TBResultStatusServerError,
             TBResultStatusConfigurationNotLoaded,
             TBResultStatusConfigurationNotInitialized
         }
         TBResultStatus;
         
     ###TBPrivacyMode
         
         typedef enum
         {
             TBPrivacyModeOff = 0, //Collects both architecture and usage data (default).
             TBPrivacyModeLow, //Collect only architecture data but NOT usage data.
             TBPrivacyModeHigh //Does not collect any architecture or usage data.
         }
         TBPrivacyMode;
     
     */
    
    
    
    class TBApp
    {
        
    public:
        
        
        ///---------------------------------------
        /// @name Basic SDK Control
        ///---------------------------------------
        
        /**
         
         @brief This is the entry point of the SDK.
         @details This method must be called before utilizing any of the other functionality of the Trackerbird SDK. This method requires an object of type `TBConfig` which contains the SDK configuration. For further detail, refer to the SDK Configuration page. This call do sync and receives a reachout.
         
         @param config An `TBConfig` instance.
         @param completionFunction A pointer to a function, which is called when the SDK completes the start. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         @see TBConfig
         @see stop
         
         @note For Cocoa Applications, the best place to put the @link start @endlink call is in `-applicationDidFinishLaunching:` of your `NSApplicationDelegate` implemetation.
         
         */
        static void start(TrackerbirdSDK::TBConfig config, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief This is the entry point of the SDK.
         @details This method must be called before utilizing any of the other functionality of the Trackerbird SDK. This method requires an object of type `TBConfig` which contains the SDK configuration. For further detail, refer to the SDK Configuration page.
         
         @param config An `TBConfig` instance.
         @param completionFunction A pointer to a function, which is called when the SDK completes the start. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         @param doSync A bool value which determeni wherever to do a sync after the start.
         @param receiveReachout A bool value which determine wherever to receive reachout during a sync. This value is ignored if `doSync` is false.
         
         
         @see TBConfig
         @see stop
         
         @note For Cocoa Applications, the best place to put the @link start @endlink call is in `-applicationDidFinishLaunching:` of your `NSApplicationDelegate` implemetation.
         
         */
        static void start(TrackerbirdSDK::TBConfig config, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status), bool doSync, bool receiveReachout);
        
        /**
         
         @brief This is the end point of the SDK.
         @note This method should always be called on the exit point of your application.
         @details This will help the Trackerbird server keep track of when your application was closed to accurately calculate session runtime duration and provide you with reports based on application usage statistics.
         Calling @link stop` before your application terminates will also tell the Trackerbird server that your application was terminated gracefully without any unhandled exceptions.
         
         Unlike most functions in the SDK, this function is synchronous, which means it returns only once finished. Due to this fact, it is recommended to close/hide the application UI before calling this function. By default, during this function, the SDK syncs all data with the server, and this is what might take a bit long during.
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the stop. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @note For Cocoa Applications, the best place to put the @link stop` call is in `-applicationWillTerminate:` of your `NSApplicationDelegate` implemetation.
         
         @see start
         
         */
        
        static void stop(void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Start new user session.
         @note This method, in conjunction with @link sessionStop @endlink should be called only if `multiSessionEnabled` in the `TBConfig` constructor has been set to `true`.
         
         When a new user session is started, the Trackerbird SDK needs to be informed so that events that happen within this session can be logged.
         The time when this method is called is also used to calculate the session duration.
         
         @param sessionID This parameter should contain a unique ID that refers to the user session that is being started. This same ID should later be used for event tracking.
         @param completionFunction A pointer to a function, which is called when the SDK completes the session start. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         @see sessionStop
         
         
         */
        
        static void sessionStart(string sessionID, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief End user session.
         @note This method, in conjunction with @link sessionStart @endlink should be called only if `multiSessionEnabled` in the `TBConfig` constructor has been set to `true`.
         
         When a user session has been closed, this method should be called so that Trackerbird can calulcate the duration of the user session. In case this method is never called, eventually this session will be considered as “timed-out”, and the time of the last recorded event will be assumed to be the time when the session was closed.
         
         When a new user session is started, the Trackerbird SDK needs to be informed so that events that happen within this session can be logged.
         The time when this method is called is also used to calculate the session duration.
         
         @param sessionID This parameter should contain a unique ID that refers to the user session that is being stopped. This must be the same same ID that was used earlier when calling @link sessionStop @endlink.
         @param completionFunction A pointer to a function, which is called when the SDK completes the session stop. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @see TBConfig
         @see TBConfig::TBConfig
         @see stop
         
         
         */
        
        static void sessionStop(string sessionID, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        
        
        
        
        ///---------------------------------------
        /// @name Synchronization
        ///---------------------------------------
        
        /**
         
         @brief Perform SDK Sync.
         @details This function will forcefully synchronize all cached data from the client machine with the Trackerbird server. The method has no return value and has no parameters. It runs asynchronously so there is no need to place this method inside of a separate thread . This call receives reachout.
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the sync. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @note This method is not required and in fact should be avoided. Both the SDK and the server can reject a sync request from occuring even if this is forced by the developer. This is done to prevent abuse and unnecessary server load if @link sync @endlink is called too frequently.
         
         @see startAutoSync
         @see stopAutoSync
         
         
         */
        
        static void sync(void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Perform SDK Sync.
         @details This function will forcefully synchronize all cached data from the client machine with the Trackerbird server. The method has no return value and has no parameters. It runs asynchronously so there is no need to place this method inside of a separate thread .
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the sync. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         @param receiveReachout A bool value which determine wherever to receive reachout.
         
         @note This method is not required and in fact should be avoided. Both the SDK and the server can reject a sync request from occuring even if this is forced by the developer. This is done to prevent abuse and unnecessary server load if @link sync @endlink is called too frequently.
         
         @see startAutoSync
         @see stopAutoSync
         
         
         */
        
        static void sync(void(*completionFunction)(TrackerbirdSDK::TBResultStatus status), bool receiveReachout);
        
        /**
         
         @brief Starts automatic synchronization.
         @details The Trackerbird SDK gives you the option to launch a separate thread that will perform an automatic sync with the server at a regular intervals. This is usually only required for applications running as background services or web services whose running cycle (session runtime duration) spans over 6 hours. Before using this method please make sure you read the section on `Caching and Synchronizing`. This call receives reachout.
         
         @note Once you call @link startAutoSync @endlink you may use @link stopAutoSync @endlink to stop the automatic synchronization process.
         
         @see sync
         @see stopAutoSync
         
         
         */
        
        static void startAutoSync();
        
        /**
         
         @brief Starts automatic synchronization.
         @details The Trackerbird SDK gives you the option to launch a separate thread that will perform an automatic sync with the server at a regular intervals. This is usually only required for applications running as background services or web services whose running cycle (session runtime duration) spans over 6 hours. Before using this method please make sure you read the section on `Caching and Synchronizing`.
         
         @param receiveReachout A bool value which determine wherever to receive reachout.
         
         @note Once you call @link startAutoSync @endlink you may use @link stopAutoSync @endlink to stop the automatic synchronization process.
         
         @see sync
         @see stopAutoSync
         
         
         */
        
        static void startAutoSync(bool receiveReachout);
        
        /**
         
         @brief Stop automatic synchronization.
         @details Use this method to stop the automatic synchronization with the server which can be started by calling on the @link startAutoSync @endlink method.
         
         @see sync
         @see startAutoSync
         
         
         */
        
        static void stopAutoSync();
        
        
        ///---------------------------------------
        /// @name Event Tracking
        ///---------------------------------------

        
        /**
         
         @brief Track an event with custom numeric value in single session mode.
         
         @param name The name of the event to be tracked.
         @param value A double value that can contain data related to an event such as how long a function took to execute or how much disk space it used to store its output.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         */
        
        static void eventTrack(string name, double value, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an event with custom numeric value and a session ID in multi session mode.
         
         @param name The name of the event to be tracked.
         @param value A double value that can contain data related to an event such as how long a function took to execute or how much disk space it used to store its output.
         @param sessionID If multiple user sessions are supported within the application, this should contain the unique ID that refers to the user session in which the event occurred.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         */
        
        static void eventTrack(string name, double value, string sessionID, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an event with custom text value in single session mode.
         
         @param name The name of the event to be tracked.
         @param value A string value that can contain custom text related to the event.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         */
        
        static void eventTrack(string name, string value, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an event with custom text value and a session ID in multi session mode.
         
         @param name The name of the event to be tracked.
         @param value A string value that can contain custom text related to the event.
         @param sessionID If multiple user sessions are supported within the application, this should contain the unique ID that refers to the user session in which the event occurred.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         */
        
        static void eventTrack(string name, string value, string sessionID, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an event with category and custom numeric value in single session mode.
         
         @param name The name of the event to be tracked.
         @param category The name of the group/category that this event forms part of.
         @param value A double value that can contain data related to an event such as how long a function took to execute or how much disk space it used to store its output.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         */
        
        static void eventTrack(string category, string name, double value, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an event with category and custom numeric value and a session ID in multi session mode.
         
         @param name The name of the event to be tracked.
         @param category The name of the group/category that this event forms part of.
         @param value A double value that can contain data related to an event such as how long a function took to execute or how much disk space it used to store its output.
         @param sessionID If multiple user sessions are supported within the application, this should contain the unique ID that refers to the user session in which the event occurred.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         
         */
        
        static void eventTrack(string category, string name, double value, string sessionID, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an event with category and custom text value in single session mode.
         
         @param name The name of the event to be tracked.
         @param category The name of the group/category that this event forms part of.
         @param value A string value that can contain data related to an event such as how long a function took to execute or how much disk space it used to store its output.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         @param overload This parameter is declared only for overloading purpose. It is not used and can safely pass NULL.
         
         */
        
        static void eventTrack(string category, string name, string value, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status), void *overload);
        
        /**
         
         @brief Track an event with category and custom text value and a session ID in multi session mode.
         
         @param name The name of the event to be tracked.
         @param category The name of the group/category that this event forms part of.
         @param value A string value that can contain data related to an event such as how long a function took to execute or how much disk space it used to store its output.
         @param sessionID If multiple user sessions are supported within the application, this should contain the unique ID that refers to the user session in which the event occurred.
         @param completionFunction A pointer to a function, which is called when the SDK completes the event track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         */
        
        static void eventTrack(string category, string name, string value, string sessionID, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        
        
        ///---------------------------------------
        /// @name Exception Tracking
        ///---------------------------------------

        /**
         
         @brief Track an exception based on provided custom `name`, `method name` and `message`.
         @details This is the core method of the exception tracking. All other methods in that group are provided for easier usage, depending on the needs, since at the end they call this one.
         
         @param className The name of the class, which catched the exception.
         @param methodName The name of the method, where the exception is catched.
         @param message A message, describing the exception.
         @param completionFunction A pointer to a function, which is called when the SDK completes the exception track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         */
        
        static void exceptionTrack(string className, string methodName, string message, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Track an exception based on provided custom `name`, `method name`, `message` and `stackTrace`.
         @details This is the core method of the exception tracking. All other methods in that group are provided for easier usage, depending on the needs, since at the end they call this one.
         
         @param className The name of the class, which catched the exception.
         @param methodName The name of the method, where the exception is catched.
         @param message A message, describing the exception.
         @param stackTrace A stackTrace of the exception.
         @param completionFunction A pointer to a function, which is called when the SDK completes the exception track. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         */
        
        static void exceptionTrack(string className, string methodName, string message, string stackTrace, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        ///---------------------------------------
        /// @name Manual Message Retrieval
        ///---------------------------------------
        
        /**
         
         @brief Request new messages from the server.
         @details Requests a manual ReachOut™ message from the server. This can be either a plain text message or a URL, depending on what messages are waiting on the server.
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the message check. This function receives two prameters: messageResult and status
         @param messageResult An instance of `TBMessageResult`.
         @param status A value from `TBResultStatus` enum.
         
         @code Code Example:
         
         void completionFunction(TrackerbirdSDK::TBMessageResult messageResult, TrackerbirdSDK::TBResultStatus status)
         {
             if(status == TrackerbirdSDK::TBResultStatusOK)
             {
                 if(messageResult.getMessagesCount() > 0)
                 {
                     std::cout << "This is your message " << messageResult.getMessage();
                 }
                 else
                 {
                     std::cout << "No message.";
                 }
             }
         }
         
         void doSomeStuff()
         {
            void (*completionFunctionPointer)(TrackerbirdSDK::TBMessageResult, TrackerbirdSDK::TBResultStatus) = completionFunction;
         
            TrackerbirdSDK::TBApp::messageCheck(completionFunctionPointer);
         }

         @endcode
         
         
         @see TBMessageResult
         
         */
        
        static void messageCheck(void(*completionFunction)(TrackerbirdSDK::TBMessageResult messageResult, TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Request new messages from the server.
         @details Requests a manual ReachOut™ message from the server. This can be either a plain text message or a URL, depending on what messages are waiting on the server.
         
         @param messageType The message type needed is to be sent in the messageType parameter, and can be one of the `TBMessageType` enum values, declared in `TBMessageResult`.
         @param completionFunction A pointer to a function, which is called when the SDK completes the message check. This function receives two prameters: messageResult and status
         @param messageResult An instance of `TBMessageResult`.
         @param status A value from `TBResultStatus` enum.
         
         @code Code Example:
         
         void completionFunction(TrackerbirdSDK::TBMessageResult messageResult, TrackerbirdSDK::TBResultStatus status)
         {
             if(status == TrackerbirdSDK::TBResultStatusOK)
             {
                 if(messageResult.getMessagesCount() > 0)
                 {
                     std::cout << "This is your message " << messageResult.getMessage();
                 }
                 else
                 {
                     std::cout << "No message.";
                 }
             }
         }
         
         void doSomeStuff()
         {
             void (*completionFunctionPointer)(TrackerbirdSDK::TBMessageResult, TrackerbirdSDK::TBResultStatus) = completionFunction;
             
             TrackerbirdSDK::TBApp::messageCheck(TrackerbirdSDK::TBMessageTypeAll, completionFunctionPointer);
         }
         
         @endcode
         
         
         @see TBMessageResult
         
         */
        
        static void messageCheck(TrackerbirdSDK::TBMessageType messageType, void(*completionFunction)(TrackerbirdSDK::TBMessageResult messageResult, TrackerbirdSDK::TBResultStatus status));
        
        ///---------------------------------------
        /// @name Checking for Software Updates
        ///---------------------------------------
        
        
        /**
         
         @brief This method is used to implement a check for updates system for your software.
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the version check. This function receives two prameters: versionResult and status.
         @param versionResult An instance of `TBVersionResult`.
         @param status A value from `TBResultStatus` enum.
         
         @see TBVersionResult
         
         @warning You should not perform any kind of "Software Update" if you are going to sumbit your application to the Mac App Store, since Apple forbids any kind of auto updates for applications that resides into the Mac App Store. In such cases you should use this functionality for informative purposes only.
         
         */
        
        static void versionCheck(void(*completionFunction)(TrackerbirdSDK::TBVersionResult versionResult, TrackerbirdSDK::TBResultStatus status));
        
        ///---------------------------------------
        /// @name License Management
        ///---------------------------------------
        
        
        /**
         
         @brief By using this method, your software can validate a license key (entered by your client) with the blacklist stored on the Trackerbird server.
         
         @param key The license key to be tested.
         @param completionFunction A pointer to a function, which is called when the SDK completes the version check. This function receives two prameters: licenseResult and status.
         @param licenseResult An instance of `TBLicenseResult`.
         @param status A value from `TBResultStatus` enum.
         
         @code Code Example:
         
         
         void completionFunction(TrackerbirdSDK::TBLicenseResult licenseResult, TrackerbirdSDK::TBResultStatus status)
         {
             if(status = TBResultStatusOK)
             {
                 //check the blacklisted status
                 switch(licenseResult.getBlacklistedStatus())
                 {
                     case TrackerbirdSDK::TBLicenseStatusNA:
                         std::cout << "Status not available";
                     break;
                     
                     case TrackerbirdSDK::TBLicenseStatusFalse:
                         std::cout << "Key is NOT blacklisted";
                     break;
                     
                     case TrackerbirdSDK::TBLicenseStatusTrue:
                         std::cout << "Key is blacklisted";
                     break;
                 }
                     
                 //check the other statuses ...
             }
             else
             {
                 std::cout << "Failed to invoke the method";
             }
         }
         
         void doSomeStuff()
         {
             void (*completionFunctionPointer)(TrackerbirdSDK::TBLicenseResult, TrackerbirdSDK::TBResultStatus) = completionFunction;
             
             TrackerbirdSDK::TBApp::keyCheck("<Your product key>", completionFunctionPointer);
         }
         
         @endcode
         
        
         @see TBLicenseResult
         @see keyChange
         
         */

        static void keyCheck(string key, void(*completionFunction)(TrackerbirdSDK::TBLicenseResult licenseResult, TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Change the current license of your application.
         @details This method should be called when an end user is trying to enter a new license key into your application and you would like to confirm that the key is in fact valid (i.e. not blacklisted). The method is very similar to the @link keyCheck @endlink method, however rather than just being a passive license check, it also registers the new key with the server and associates it with this particular client installation.
         
         @param key The license key to be tested.
         @param completionFunction A pointer to a function, which is called when the SDK completes the version check. This function receives two prameters: licenseResult and status.
         @param licenseResult An instance of `TBLicenseResult`.
         @param status A value from `TBResultStatus` enum.
         
         @code Code Example:
         
         void completionFunction(TrackerbirdSDK::TBLicenseResult licenseResult, TrackerbirdSDK::TBResultStatus status)
         {
             if(status = TBResultStatusOK)
             {
                 //check the blacklisted status
                 switch(licenseResult.getBlacklistedStatus())
                 {
                     case TrackerbirdSDK::TBLicenseStatusNA:
                         std::cout << "Status not available";
                     break;
                     
                     case TrackerbirdSDK::TBLicenseStatusFalse:
                         std::cout << "Key is NOT blacklisted";
                     break;
                     
                     case TrackerbirdSDK::TBLicenseStatusTrue:
                         std::cout << "Key is blacklisted";
                     break;
                 }
                     
                 //check the other statuses ...
             }
             else
             {
                 std::cout << "Failed to invoke the method";
             }
         }
         
         void doSomeStuff()
         {
             void (*completionFunctionPointer)(TrackerbirdSDK::TBLicenseResult, TrackerbirdSDK::TBResultStatus) = completionFunction;
             
             TrackerbirdSDK::TBApp::keyChange("<Your product key>", completionFunctionPointer);
         }
         
         @endcode
         
         
         @see TBLicenseResult
         @see keyCheck
         
         */
        
        static void keyChange(string key, void(*completionFunction)(TrackerbirdSDK::TBLicenseResult licenseResult, TrackerbirdSDK::TBResultStatus status));
        
        /**
         @brief Set The Product's License Information.
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the license info update. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @note This method accepts `TBKeyType` and `TBLicenseStatus` types as parameters. For more information about they values - see `TBLicenseResult`.
         
         @see `TBLicenseResult`
         */
        static void setLicenseInfo(TrackerbirdSDK::TBKeyType keyType, TrackerbirdSDK::TBLicenseStatus whitelistedStatus, TrackerbirdSDK::TBLicenseStatus expiredStatus, TrackerbirdSDK::TBLicenseStatus blacklistedStatus, TrackerbirdSDK::TBLicenseStatus activatedStatus, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         @brief Set The Product's License Information (Key Type only).
         
         @param completionFunction A pointer to a function, which is called when the SDK completes the license info update. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @note This method will update only the key type.
         
         @see `TBLicenseResult`
         */
        
        static void setLicenseInfo(TrackerbirdSDK::TBKeyType keyType, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        
        ///---------------------------------------
        /// @name SDK Status Checks
        ///---------------------------------------
        
        
        /**
         
         @brief Test the connection to the Trackerbird server.
         @details This method allows you to test your application’s connectivity with the Trackerbird server and to confirm that your callhome URL is active and operational (for debugging purposes when using a custom callhome URL). You do NOT need to call this method before other API calls since this would cause unnecessary traffic on your clients’ machines. Instead, you should check the return types by each API call since every API call which requires server communication does it’s own connection status check and returns any connection errors as part of it’s return type.
         
         @param url The URL against which to test connectivity (usually your callhome URL)
         @param completionFunction A pointer to a function, which is called when the SDK completes the connection check. This function receives one prameter: status.
         @param status A value from `TBResultStatus` enum.
         
         
         
         */
        static void connectionCheck(string url, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        ///---------------------------------------
        /// @name Privacy Settings
        ///---------------------------------------
        
        /**
         
         @brief Get the level of privacy.
         
         @param completionFunction A pointer to a function, which is called in order to return the privacy mode. This function receives two prameters: privacyMode and status.
         @param privacyMode The privacy mode over which the SDK currently operate.
         @param status A value from `TBResultStatus` enum.
         
         @details The Trackerbird SDK supports 3 different Privacy settings that give you control on what type of anonymous data should be collected form the end user’s machine, based on whether the user opted in or out of your Customer Experience Improvement. To read more about privacy and what data is collected by each privacy level, please refer to this Kbase article: http://helpdesk.trackerbird.com/knowledgebase.php?article=1
         
         The Default Value is `TBPrivacyModeOff`
         
         */
        static void getPrivacyMode(void(*completionFunction)(TrackerbirdSDK::TBPrivacyMode privacyMode, TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief Set the level of privacy.
         
         @param privacyMode One of the privacy modes from the `TBPrivacyMode` declared in `TBConfig`.
         @param completionFunction A pointer to a function, which is called when the SDK completes the privacy mode update. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @details The Trackerbird SDK supports 3 different Privacy settings that give you control on what type of anonymous data should be collected form the end user’s machine, based on whether the user opted in or out of your Customer Experience Improvement. To read more about privacy and what data is collected by each privacy level, please refer to this Kbase article: http://helpdesk.trackerbird.com/knowledgebase.php?article=1
         
         The Default Value is `TBPrivacyModeOff`
         
         */
        
        static void setPrivacyMode(TrackerbirdSDK::TBPrivacyMode privacyMode, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        ///---------------------------------------
        /// @name Custom Filters
        ///---------------------------------------
        
        /**
         
         @brief This method sets a value of a custom filter propery at specified index;
         
         @param property The namame of the property.
         @param index The index of the property. This value must be from 1 ot 20.
         @param completionFunction A pointer to a function, which is called when the SDK completes the custom property update. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         */
        static void setCustomProperty(string property, unsigned int index, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        /**
         
         @brief This method removes the value of a custom filter propery at specified index;
         
         @param index The index of the property. This value must be from 1 ot 20.
         @param completionFunction A pointer to a function, which is called when the SDK completes the custom property update. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         */
        
        static void removeCustomProperty(unsigned int index, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        ///---------------------------------------
        /// @name Other
        ///---------------------------------------
        
        /**
         
         @brief This method updates the current configuration over which the SDK operate.
         @details The update reflects only the optional parameters - `productVersion`, `productBuildNumber`, `productEdition` and `productLanguage` of `TBConfig`
         
         @param config An Instace of `TBConfig`.
         @param completionFunction A pointer to a function, which is called when the SDK completes the config update. This function receives one prameter: status
         @param status A value from `TBResultStatus` enum.
         
         @see TBConfig
         
         */
        static void updateConfig(TrackerbirdSDK::TBConfig config, void(*completionFunction)(TrackerbirdSDK::TBResultStatus status));
        
        
        
        
        
        
    };
}

#endif /* defined(__TrackerbirdSDK__TBApp__) */
