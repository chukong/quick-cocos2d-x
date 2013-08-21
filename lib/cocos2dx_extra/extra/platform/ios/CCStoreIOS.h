
#import <StoreKit/StoreKit.h>

#include "store/CCStore.h"
#include "store/CCStoreProductsRequestDelegate.h"

USING_NS_CC_EXTRA;

class CCStoreReceiptVerifyRequestIOS;

@interface CCStoreIOS : NSObject < SKPaymentTransactionObserver, SKProductsRequestDelegate >
{
    CCStoreTransactionObserver *transactionObserver_;
    CCStoreProductsRequestDelegate *productRequestDelegate_;
    NSMutableDictionary *loadedProducts_;
    SKProductsRequest *productRequest_;
}

#pragma mark -
#pragma mark init

+ (CCStoreIOS *)sharedStore;
+ (void)purgeSharedStore;
- (id)init;
- (void)postInitWithTransactionObserver:(CCStoreTransactionObserver *)observer;

#pragma mark -
#pragma mark Making a Purchase

- (BOOL)canMakePurchases;
- (void)purchase:(SKProduct *)product;
- (void)restore;
- (void)finishTransaction:(SKPaymentTransaction *)transaction;

#pragma mark -
#pragma mark Retrieving Product Information

- (void)requestProductData:(NSSet *)productsId andDelegate:(CCStoreProductsRequestDelegate *)delegate;
- (void)cancelRequestProductData;
- (BOOL)isProductLoaded:(NSString *)productId;
- (SKProduct *)getProduct:(NSString *)productId;
- (void)cleanCachedProducts;

- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;
- (void)request:(SKRequest *)request didFailWithError:(NSError *)error;

#pragma mark -
#pragma mark Handling Transactions

- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
- (void)transactionCompleted:(SKPaymentTransaction *)transaction;
- (void)transactionFailed:(SKPaymentTransaction *)transaction;
- (void)transactionRestored:(SKPaymentTransaction *)transaction;

#pragma mark -
#pragma mark helper

- (CCStorePaymentTransaction *)createCCStorePaymentTransaction:(SKPaymentTransaction *)transaction;

@end
