/*
  UMFeedback.h
  Created by ming hua on 2012-03-19.
  Updated by ming hua on 2013-10-10.
  Version 1.4.1
  Copyright (c) 2013年 umeng.com. All rights reserved.
 */

#import <Foundation/Foundation.h>
#define UMFBCheckFinishedNotification @"UMFBCheckFinishedNotification"
#define UMFBWebViewDismissNotification @"UMFBWebViewDismissNotification"

@protocol UMFeedbackDataDelegate <NSObject>
@optional
- (void)getFinishedWithError: (NSError *)error;
- (void)postFinishedWithError:(NSError *)error;
@end

@interface UMFeedback : NSObject
@property(nonatomic, assign) id <UMFeedbackDataDelegate> delegate;
@property(nonatomic, retain) NSMutableArray *newReplies;
@property(nonatomic, retain) NSMutableArray *topicAndReplies;

#pragma Umeng Feedback Setting
+ (void)setLogEnabled:(BOOL)value;
#pragma Umeng Feedback Show Html UI
+ (void)showFeedback:(UIViewController *)viewController withAppkey:(NSString *)appKey;
+ (void)showFeedback:(UIViewController *)viewController withAppkey:(NSString *)appKey dictionary:(NSDictionary *)dictionary;
#pragma Umeng Feedback Data Api
+ (UMFeedback *)sharedInstance;
- (void)setAppkey:(NSString *)appKey delegate:(id<UMFeedbackDataDelegate>)newDelegate;
- (void)get;
- (void)post:(NSDictionary *)feedback_dictionary;
+ (void)checkWithAppkey:(NSString *)appkey;
@end