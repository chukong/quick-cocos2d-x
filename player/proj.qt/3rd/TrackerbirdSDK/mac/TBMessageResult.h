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

#ifndef __TrackerbirdSDK__TBMessageResult__
#define __TrackerbirdSDK__TBMessageResult__

#include <iostream>

using namespace std;

namespace TrackerbirdSDK
{
    typedef enum
    {
        TBMessageTypeAll = 0,
        TBMessageTypeText = 1,
        TBMessageTypeURL = 2
    }
    TBMessageType;
    
    /**
     
     This class represents a response from the `Manual Message Retrieval` methods in `TBApp`.
     
     ##Enums
     
     ###TBMessageType
     
         typedef enum
         {
             TBMessageTypeAll = 0,
             TBMessageTypeText = 1,
             TBMessageTypeURL = 2
         }
         TBMessageType;
     
     */
    
    class TBMessageResult
    {
        
    private:
        unsigned int _messagesCount;
        TBMessageType _messageType;
        string _message;
        
    public:
        
        /**
         
         @brief Creates an instance of TBMessageResult class.
         
         @param messagesCount The number of remaining messages on the server.
         @param messageType The type of the received message.
         @param message The message itself.
         
         */
        TBMessageResult(unsigned int messagesCount, TBMessageType messageType, string message);
        
        ///Get The number of remaining messages on the server.
        unsigned int getMessagesCount() const;
        
        ///Get The type of the received message.
        TBMessageType getMessageType() const;
        
        ///Get The message itself.
        string getMessage() const;
        
    };
}

#endif /* defined(__TrackerbirdSDK__TBMessageResult__) */
